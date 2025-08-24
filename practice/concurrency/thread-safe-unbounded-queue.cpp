#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <vector>
#include <utility>
#include <numeric>  // required for std::accumulate
#include <string>
#include <unordered_set>
#include <deque>
#include <queue>
#include <optional>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <future>

class ThreadSafeQueue {

public:
    ThreadSafeQueue() : closed(false) {}

    // blocking call
    bool pop(std::function<void()>& out_task) 
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            not_empty.wait(lock, [this]() {return !queue.empty() || closed == true; });
            if (closed == true && queue.empty())
            {
                return false; // close & drain queue
            }
            out_task = std::move(queue.front());
            queue.pop();
        }
        return true;
    }

    // push
    bool push(std::function<void()> task)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            if (closed == true) return  false;
            queue.push(std::move(task));
        }
        not_empty.notify_one();
        return true;
    }

    void close()
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            closed = true;
        }
        not_empty.notify_all();
    }

private:

    bool closed;
    std::mutex mutex;
    std::condition_variable not_empty;
    std::queue<std::function<void()>> queue;

};

class ThreadPool 
{
public:
    ThreadPool(size_t threads)
    {
        threads_vec = std::vector<std::thread>(threads); // move constructor should be used here

        for (auto& thread : threads_vec)
        {
            thread = std::thread([this]() {
                while(1)
                {
                    std::function<void()> task;
                    if (queue.pop(task))
                    {
                        task();
                    }
                    else
                    {
                        // closed & drained
                        break;
                    }
                }
            });
        }
    }

    template<class F, class... Args>
    std::future<std::invoke_result_t<F, Args...>> submit(F&& f, Args&&... args)
    {
        using T = std::invoke_result_t<F, Args...>;
        // wrap in packaged_task to be able to get a future from function executed asynchronously
        // make it a shared_ptr so it can survive outside the scope of this called function and you can call 'get_future'
        auto task = std::packaged_task<T()>( std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto task_ptr = std::make_shared<decltype(task)>(std::move(task));
        bool did_submit = queue.push([task_ptr]() {
            (*task_ptr)();
        });

        if (!did_submit)
        {
            throw std::runtime_error("thread pool is closed");
        }

        return task_ptr->get_future();
    }

    ~ThreadPool()
    {
        queue.close();
        for (auto& thread : threads_vec)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }
private:

    std::vector<std::thread> threads_vec;
    ThreadSafeQueue queue;

};

int main(int argc, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    return 0; 
}