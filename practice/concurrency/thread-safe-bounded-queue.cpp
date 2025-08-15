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

template<typename T>
class BoundedQueue
{

public:

    BoundedQueue(size_t capacity) : capacity(capacity), closed(false) {}
    // blocking call
    bool pop(T& out)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            not_empty.wait(lock, [this]() {return !queue.empty() || closed == true});
            if (queue.empty()) {return false;}
            out = std::move(queue.front());
            queue.pop();
        }
        not_full.notify_one();
        return true;
    }

    bool try_pop(T& out)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            if (queue.empty()) {return false;}
            out = std::move(queue.front());
            queue.pop();
        }
        not_full.notify_one();
        return true;
    }

    // blocking call
    bool push(const T& val)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            not_full.wait(lock, [this]() {return queue.size() < capacity || closed == true});
            if (closed == true) {return false;}
            queue.push(val);
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
        not_full.notify_all();
        not_empty.notify_all();
    }

private:
    size_t capacity;
    std::mutex mutex;
    bool closed;
    std::condition_variable not_full;
    std::condition_variable not_empty;
    std::queue<T> queue;

};