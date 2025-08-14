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

template<typename T>
class BoundedQueue
{

public:

    BoundedQueue(size_t capacity) : capacity(capacity) {}

    // blocking call
    void pop(T& out)
    {
        {
            std::unique_lock<std::mutex> lock(mutex)
            not_empty.wait(lock, [this]() {return !queue.empty()});
            // if (queue.empty()) {return false;}
            out = std::move(queue.front());
            queue.pop();
        }
        not_full.notify_one();
    }

    bool try_pop(T& out)
    {
        {
            std::unique_lock<std::mutex> lock(mutex)
            if (queue.empty()) {return false;}
            out = std::move(queue.front());
            queue.pop();
        }
        not_full.notify_one();
        return true;
    }

    // blocking call
    void push(const T& val)
    {
        {
            std::unique_lock<std::mutex> lock(mutex)
            not_full.wait(lock, [this]() {return queue.size() < capacity});
            // if (queue.size() >= capacity) {return false;}
            queue.push(val);
        }
        not_empty.notify_one();
    }

private:
    size_t capacity;
    std::mutex mutex;
    std::condition_variable not_full;
    std::condition_variable not_empty;
    std::queue<T> queue;

};