Gotcha—here’s a clean, reusable **in‑process thread‑safe queue** using `std::mutex` + `std::condition_variable`. It’s **multi‑producer / multi‑consumer**, supports optional **bounded capacity**, graceful **close()**, and both blocking and non‑blocking pops.

```cpp
// blocking_queue.hpp (C++17)
#pragma once
#include <condition_variable>
#include <deque>
#include <limits>
#include <mutex>
#include <optional>

template <typename T>
class BlockingQueue {
public:
    explicit BlockingQueue(std::size_t capacity = std::numeric_limits<std::size_t>::max())
        : capacity_(capacity) {}

    // Disable copy; allow move if you want (careful with condvars)
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;

    // Enqueue (blocking if the queue is full). Returns false if queue is closed.
    bool push(const T& value) {
        std::unique_lock<std::mutex> lk(m_);
        not_full_.wait(lk, [&]{ return closed_ || q_.size() < capacity_; });
        if (closed_) return false;
        q_.push_back(value);
        lk.unlock();
        not_empty_.notify_one();
        return true;
    }

    bool push(T&& value) {
        std::unique_lock<std::mutex> lk(m_);
        not_full_.wait(lk, [&]{ return closed_ || q_.size() < capacity_; });
        if (closed_) return false;
        q_.push_back(std::move(value));
        lk.unlock();
        not_empty_.notify_one();
        return true;
    }

    template <class... Args>
    bool emplace(Args&&... args) {
        std::unique_lock<std::mutex> lk(m_);
        not_full_.wait(lk, [&]{ return closed_ || q_.size() < capacity_; });
        if (closed_) return false;
        q_.emplace_back(std::forward<Args>(args)...);
        lk.unlock();
        not_empty_.notify_one();
        return true;
    }

    // Blocking pop: returns empty optional when closed AND drained.
    std::optional<T> wait_pop() {
        std::unique_lock<std::mutex> lk(m_);
        not_empty_.wait(lk, [&]{ return closed_ || !q_.empty(); });
        if (q_.empty()) return std::nullopt; // closed & drained
        T val = std::move(q_.front());
        q_.pop_front();
        lk.unlock();
        not_full_.notify_one();
        return val;
    }

    // Non-blocking try_pop: returns false if empty
    bool try_pop(T& out) {
        std::lock_guard<std::mutex> lk(m_);
        if (q_.empty()) return false;
        out = std::move(q_.front());
        q_.pop_front();
        not_full_.notify_one();
        return true;
    }

    // Timed pop: waits up to 'dur'. Returns false on timeout; true on success.
    template <class Rep, class Period>
    bool pop_for(T& out, const std::chrono::duration<Rep,Period>& dur) {
        std::unique_lock<std::mutex> lk(m_);
        if (!not_empty_.wait_for(lk, dur, [&]{ return closed_ || !q_.empty(); }))
            return false; // timeout
        if (q_.empty()) return false; // closed & drained
        out = std::move(q_.front());
        q_.pop_front();
        lk.unlock();
        not_full_.notify_one();
        return true;
    }

    // Close: no new pushes, wake all waiters. Consumers can drain remaining items.
    void close() {
        std::lock_guard<std::mutex> lk(m_);
        closed_ = true;
        not_empty_.notify_all();
        not_full_.notify_all();
    }

    bool closed() const {
        std::lock_guard<std::mutex> lk(m_);
        return closed_;
    }

    std::size_t size() const {
        std::lock_guard<std::mutex> lk(m_);
        return q_.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(m_);
        return q_.empty();
    }

private:
    const std::size_t capacity_;
    mutable std::mutex m_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    std::deque<T> q_;
    bool closed_{false};
};
```

### Minimal example with several threads

```cpp
#include "blocking_queue.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <functional>

int main() {
    BlockingQueue<int> q(8); // bounded buffer of 8

    // Producers
    std::vector<std::thread> producers;
    for (int p = 0; p < 3; ++p) {
        producers.emplace_back([p,&q]{
            for (int i = 0; i < 10; ++i) {
                q.push(p*100 + i);
            }
        });
    }

    // Consumers
    std::vector<std::thread> consumers;
    for (int c = 0; c < 2; ++c) {
        consumers.emplace_back([c,&q]{
            while (true) {
                auto item = q.wait_pop();
                if (!item) break; // closed & drained
                std::cout << "C" << c << " got " << *item << "\n";
            }
        });
    }

    for (auto& t : producers) t.join();
    q.close();                 // signal no more items
    for (auto& t : consumers) t.join();
}
```

### Notes & tips

* Works for any `T` (including `std::function<void()>` for a quick worker queue).
* **Predicates** in `wait` handle spurious wakeups.
* **close()** lets all waiting threads exit cleanly—important when using multiple consumers.
* For heavy items, prefer `emplace` or `push(T&&)` to avoid extra copies.

If you want, I can also add a **`capacity()` setter**, **interrupt flags**, or a **RAII “queue guard”** to automatically call `close()` when exiting a scope.

Awesome—here’s a tiny, reusable **RAII guard** that automatically calls `close()` on your `BlockingQueue<T>` when the scope ends (even if an exception is thrown). It’s movable (single owner), non‑copyable, and you can `dismiss()` if you don’t want it to close on destruction.

```cpp
// queue_guard.hpp
#pragma once

template <class Queue>
class QueueGuard {
public:
    explicit QueueGuard(Queue& q) noexcept : q_(&q) {}

    // non-copyable, movable (single owner)
    QueueGuard(const QueueGuard&) = delete;
    QueueGuard& operator=(const QueueGuard&) = delete;

    QueueGuard(QueueGuard&& other) noexcept : q_(other.q_) { other.q_ = nullptr; }
    QueueGuard& operator=(QueueGuard&& other) noexcept {
        if (this != &other) {
            if (q_) q_->close();
            q_ = other.q_;
            other.q_ = nullptr;
        }
        return *this;
    }

    // Prevent closing at destruction (e.g., you’ll close manually)
    void dismiss() noexcept { q_ = nullptr; }

    ~QueueGuard() {
        if (q_) q_->close();
    }

private:
    Queue* q_;
};
```

### How to use with your `BlockingQueue<T>` (from earlier)

```cpp
#include "blocking_queue.hpp"
#include "queue_guard.hpp"
#include <iostream>
#include <thread>
#include <vector>

int main() {
    BlockingQueue<int> q(/*capacity=*/8);

    // RAII guard: ensures q.close() when leaving this scope
    QueueGuard<BlockingQueue<int>> guard(q);

    std::vector<std::thread> consumers;
    for (int c = 0; c < 2; ++c) {
        consumers.emplace_back([c, &q]{
            while (true) {
                auto item = q.wait_pop();
                if (!item) break;                // closed & drained
                std::cout << "C" << c << " -> " << *item << "\n";
            }
        });
    }

    std::vector<std::thread> producers;
    for (int p = 0; p < 3; ++p) {
        producers.emplace_back([p, &q]{
            for (int i = 0; i < 10; ++i) q.push(p*100 + i);
        });
    }

    for (auto& t : producers) t.join();

    // No need to call q.close(); guard will close on scope exit.
    // If you *do* want to close earlier, just:
    // q.close(); guard.dismiss();

    for (auto& t : consumers) t.join();
}
```

### Why this helps

* **Exception-safe**: if something throws before you close, the guard still shuts the queue down so consumers exit.
* **Single‑owner semantics**: move it into the scope that “owns” shutdown. No accidental double closes.
* **Explicit control**: call `dismiss()` if you close manually (or want the queue to stay open past the guard’s lifetime).

Want a variant that also **joins** a set of worker threads in its destructor? I can add a `ThreadPoolGuard` that owns both the queue guard and a span of `std::thread*` to join on teardown.
