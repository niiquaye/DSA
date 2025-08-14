Awesome ask—here are two solid, reusable templates:

1. a **thread-safe in‑process work queue + thread pool** that takes `std::function<void()>` tasks and runs them on N worker threads, and
2. a **cross‑process bounded queue** (ring buffer in POSIX shared memory) using a `pthread_mutex` + `pthread_cond` configured for interprocess use.

I’ll end with a quick refresher on producer/consumer & condvars.

---

# 1) In‑process thread‑safe queue + thread pool (C++17)

```cpp
// thread_pool.hpp
#pragma once
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <mutex>
#include <optional>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

class ThreadSafeQueue {
public:
    using Task = std::function<void()>;

    void push(Task t) {
        {
            std::lock_guard<std::mutex> lk(m_);
            if (closed_) throw std::runtime_error("Queue closed");
            q_.emplace_back(std::move(t));
        }
        cv_.notify_one();
    }

    // Blocks until a task is available or the queue is closed+empty.
    // Returns empty optional when closed and drained.
    std::optional<Task> wait_pop() {
        std::unique_lock<std::mutex> lk(m_);
        cv_.wait(lk, [&]{ return closed_ || !q_.empty(); });
        if (q_.empty()) return std::nullopt;      // closed and drained
        Task t = std::move(q_.front());
        q_.pop_front();
        return t;
    }

    // Non-blocking try_pop
    bool try_pop(Task& out) {
        std::lock_guard<std::mutex> lk(m_);
        if (q_.empty()) return false;
        out = std::move(q_.front());
        q_.pop_front();
        return true;
    }

    // Prevent new pushes; wake all waiters. Remaining tasks will run.
    void close() {
        {
            std::lock_guard<std::mutex> lk(m_);
            closed_ = true;
        }
        cv_.notify_all();
    }

    bool closed() const {
        std::lock_guard<std::mutex> lk(m_);
        return closed_;
    }

private:
    mutable std::mutex m_;
    std::condition_variable cv_;
    std::deque<Task> q_;
    bool closed_{false};
};

class ThreadPool {
public:
    explicit ThreadPool(std::size_t n_threads = std::thread::hardware_concurrency())
    : workers_(n_threads ? n_threads : 1)
    {
        for (auto& t : workers_) {
            t = std::thread([this]{
                for (;;) {
                    auto opt = queue_.wait_pop();
                    if (!opt) break;   // queue closed and drained
                    (*opt)();
                }
            });
        }
    }

    // Submit any callable; returns a future for its result.
    template<class F, class... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<std::invoke_result_t<F, Args...>>
    {
        using R = std::invoke_result_t<F, Args...>;
        auto task_ptr = std::make_shared<std::packaged_task<R()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        auto fut = task_ptr->get_future();
        queue_.push([task_ptr]{ (*task_ptr)(); });
        return fut;
    }

    // No more tasks; let workers finish.
    void shutdown() {
        queue_.close();
        join_all();
    }

    ~ThreadPool() {
        shutdown();
    }

private:
    void join_all() {
        for (auto& t : workers_) if (t.joinable()) t.join();
    }

    ThreadSafeQueue queue_;
    std::vector<std::thread> workers_;
};
```

Usage:

```cpp
// main.cpp
#include "thread_pool.hpp"
#include <iostream>

int main() {
    ThreadPool pool(4);
    auto f = pool.submit([](int x){ return x*x; }, 12);
    auto g = pool.submit([](){ std::cout << "hello from worker\n"; });
    std::cout << "square: " << f.get() << "\n";
    g.get(); // wait for print
    // pool destructor calls shutdown()
}
```

---

# 2) Cross‑process thread‑safe queue (POSIX shared memory + PTHREAD\_PROCESS\_SHARED)

This is a fixed‑size message queue (bounded buffer, ring) for arbitrary byte payloads up to `MaxMsgBytes`. Two or more **independent processes** can open the same shared memory object by name. One can produce, another consume (or both).

> Requires: Linux/macOS with POSIX APIs. Link with `-pthread -lrt` (where needed). Run once to `create`, then other processes `open_only`.

```cpp
// ipc_queue.hpp
#pragma once
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdint>
#include <new>

template<std::size_t Capacity, std::size_t MaxMsgBytes>
class IPCQueue {
    static_assert(Capacity >= 1, "Capacity must be >= 1");
public:
    enum class OpenMode { create_or_truncate, open_only };

    IPCQueue(const std::string& shm_name, OpenMode mode)
    : name_(shm_name)
    {
        const int oflag = (mode == OpenMode::create_or_truncate)
                        ? (O_CREAT | O_RDWR)
                        : O_RDWR;
        int fd = shm_open(name_.c_str(), oflag, 0600);
        if (fd == -1) throw std::runtime_error("shm_open: " + std::string(strerror(errno)));

        std::size_t total_size = sizeof(Header) + Capacity * MaxMsgBytes;
        if (mode == OpenMode::create_or_truncate) {
            if (ftruncate(fd, total_size) == -1) {
                int e = errno; close(fd); shm_unlink(name_.c_str());
                throw std::runtime_error("ftruncate: " + std::string(strerror(e)));
            }
        }

        void* base = mmap(nullptr, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        close(fd);
        if (base == MAP_FAILED) {
            throw std::runtime_error("mmap: " + std::string(strerror(errno)));
        }

        mem_ = static_cast<std::byte*>(base);
        hdr_ = reinterpret_cast<Header*>(mem_);
        buf_ = mem_ + sizeof(Header);
        size_ = total_size;

        if (mode == OpenMode::create_or_truncate) {
            init_header();
        } else {
            // sanity check
            if (hdr_->magic != kMagic) {
                munmap(mem_, size_);
                throw std::runtime_error("IPCQueue: wrong magic (not initialized?)");
            }
        }
    }

    ~IPCQueue() {
        if (mem_) munmap(mem_, size_);
    }

    // Optional: remove shared memory object (call when no one else needs it).
    static void unlink(const std::string& shm_name) {
        shm_unlink(shm_name.c_str());
    }

    // Blocking push: copies `n` bytes from src into the ring. Throws if closed.
    void push(const void* src, std::size_t n) {
        if (n > MaxMsgBytes) throw std::runtime_error("message too large");
        std::unique_lock<pthread_mutex_t> lk(hdr_->mtx, adopt_lock);
        // adopt_lock requires mutex already locked; so lock it manually:
        lk.release(); // cancel adopt
        pthread_mutex_lock(&hdr_->mtx); // RAII is messy with pthreads—manage manually

        while (!hdr_->closed && hdr_->count == Capacity) {
            pthread_cond_wait(&hdr_->not_full, &hdr_->mtx);
        }
        if (hdr_->closed) { pthread_mutex_unlock(&hdr_->mtx); throw std::runtime_error("queue closed"); }

        std::byte* slot = buf_ + ((hdr_->tail % Capacity) * MaxMsgBytes);
        // write size header (first 8 bytes) then payload
        std::memcpy(slot, &n, sizeof(std::size_t));
        std::memcpy(slot + sizeof(std::size_t), src, n);
        hdr_->tail = (hdr_->tail + 1) % Capacity;
        hdr_->count++;

        pthread_cond_signal(&hdr_->not_empty);
        pthread_mutex_unlock(&hdr_->mtx);
    }

    // Blocking pop: returns payload into out. Returns false when closed and drained.
    bool pop(std::vector<std::uint8_t>& out) {
        pthread_mutex_lock(&hdr_->mtx);
        while (!hdr_->closed && hdr_->count == 0) {
            pthread_cond_wait(&hdr_->not_empty, &hdr_->mtx);
        }
        if (hdr_->count == 0) { // closed + empty
            pthread_mutex_unlock(&hdr_->mtx);
            return false;
        }
        std::byte* slot = buf_ + ((hdr_->head % Capacity) * MaxMsgBytes);
        std::size_t n{};
        std::memcpy(&n, slot, sizeof(std::size_t));
        out.resize(n);
        std::memcpy(out.data(), slot + sizeof(std::size_t), n);

        hdr_->head = (hdr_->head + 1) % Capacity;
        hdr_->count--;

        pthread_cond_signal(&hdr_->not_full);
        pthread_mutex_unlock(&hdr_->mtx);
        return true;
    }

    // Close queue for new pushes; wake all waiters. Consumers can drain remaining items.
    void close() {
        pthread_mutex_lock(&hdr_->mtx);
        hdr_->closed = true;
        pthread_cond_broadcast(&hdr_->not_full);
        pthread_cond_broadcast(&hdr_->not_empty);
        pthread_mutex_unlock(&hdr_->mtx);
    }

private:
    struct Header {
        // IMPORTANT: these must be placed in shared memory and set PTHREAD_PROCESS_SHARED
        pthread_mutex_t mtx;
        pthread_cond_t  not_empty;
        pthread_cond_t  not_full;

        std::size_t head{0}, tail{0}, count{0};
        bool closed{false};
        std::uint64_t magic{0};
    };

    static constexpr std::uint64_t kMagic = 0x5155455545495043ULL; // "QUEUEIPC"

    void init_header() {
        // Init mutex/cond with PROCESS_SHARED
        pthread_mutexattr_t mtx_attr; pthread_mutexattr_init(&mtx_attr);
        pthread_mutexattr_setpshared(&mtx_attr, PTHREAD_PROCESS_SHARED);
        pthread_mutex_init(&hdr_->mtx, &mtx_attr);
        pthread_mutexattr_destroy(&mtx_attr);

        pthread_condattr_t cv_attr; pthread_condattr_init(&cv_attr);
        pthread_condattr_setpshared(&cv_attr, PTHREAD_PROCESS_SHARED);
        pthread_cond_init(&hdr_->not_empty, &cv_attr);
        pthread_cond_init(&hdr_->not_full,  &cv_attr);
        pthread_condattr_destroy(&cv_attr);

        hdr_->head = hdr_->tail = hdr_->count = 0;
        hdr_->closed = false;
        hdr_->magic = kMagic;
    }

    std::string name_;
    std::byte* mem_{nullptr};
    Header* hdr_{nullptr};
    std::byte* buf_{nullptr};
    std::size_t size_{0};
};
```

Minimal usage (two separate processes):

```cpp
// producer.cpp
#include "ipc_queue.hpp"
#include <string>

int main() {
    IPCQueue<256 /*slots*/, 1024 /*bytes per msg*/> q("/my_ipc_queue", IPCQueue<256,1024>::OpenMode::create_or_truncate);
    std::string msg = "hello from producer";
    q.push(msg.data(), msg.size());
    q.close(); // signal done
}
```

```cpp
// consumer.cpp
#include "ipc_queue.hpp"
#include <iostream>
#include <vector>

int main() {
    IPCQueue<256,1024> q("/my_ipc_queue", IPCQueue<256,1024>::OpenMode::open_only);
    std::vector<uint8_t> payload;
    while (q.pop(payload)) {
        std::cout.write(reinterpret_cast<char*>(payload.data()), payload.size());
        std::cout << "\n";
    }
    // Optionally remove the shared memory object when everyone is done:
    IPCQueue<256,1024>::unlink("/my_ipc_queue");
}
```

**Notes**

* All processes must agree on `Capacity` and `MaxMsgBytes`.
* Messages are copied (not zero‑copy). For large objects, consider shared-memory blobs + passing handles/offsets.
* If you prefer less boilerplate, `boost::interprocess::message_queue` is a good alternative.

---

# Quick refresher: Producer/Consumer + Condition Variables

* **Producer/Consumer (bounded buffer):** Producers insert items into a finite queue; consumers remove them. When the queue is **full**, producers must wait; when it’s **empty**, consumers wait. This prevents busy‑spinning and coordinates throughput.

* **Condition variables (condvars):** Let a thread **sleep while holding a predicate false** and wake when another thread changes state and calls `notify_one()/notify_all()`. Always pair `wait()` with a **predicate** checked under a mutex (the classic pattern):

  ```cpp
  std::unique_lock<std::mutex> lk(m);
  cv.wait(lk, [&]{ return state_changed_condition; });
  ```

  This guards against **spurious wakeups** and ensures correctness.

* **Best practices**

  * Use a **stop/closed flag** so waiters can exit cleanly (both templates do this).
  * Prefer **`notify_one`** for single-waiter scenarios; **`notify_all`** when multiple waiters need to re-check predicates (e.g., shutdown).
  * Avoid holding locks while executing arbitrary user code (the thread pool runs tasks after popping, outside the lock).
  * For interprocess: initialize `pthread_mutex_t`/`pthread_cond_t` with `PTHREAD_PROCESS_SHARED` and place them in shared memory.

If you want, I can tailor these to your exact platform (Linux/macOS/Windows), switch the IPC version to named POSIX message queues, or add **timeout** variants (`wait_for`) for pop/push.
