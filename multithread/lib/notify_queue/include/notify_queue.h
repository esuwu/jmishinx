//
// Created by kira on 28.09.2020.
//

#ifndef CPP_CPP_MULTITHREAD_LIB_NOTIFY_QUEUE_INCLUDE_NOTIFY_QUEUE_H_
#define CPP_CPP_MULTITHREAD_LIB_NOTIFY_QUEUE_INCLUDE_NOTIFY_QUEUE_H_

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace notify_queue {
template<class T>
class NotifyQueue {
 public:
    NotifyQueue() = default;

    void push(T &&item) {
        {
            std::lock_guard lock{_mutex};
            _queue.push(item);
        }
        _cv.notify_one();
    }

    void push(const T &item) {
        {
            std::unique_lock lock{_mutex};
            _queue.push(item);
        }
        _cv.notify_one();
    }

    T pop() {
        std::unique_lock lock{_mutex};
        while (_queue.empty()) {
            _cv.wait(lock);
        }
        T item{_queue.front()};
        _queue.pop();
        return item;
    }

    [[nodiscard]] bool empty() const {
        std::lock_guard lock{_mutex};
        return _queue.empty();
    }

    void clear() {
        std::lock_guard lock{_mutex};
        std::queue<T> empty{};
        _queue.swap(empty);
    }

 private:
    std::queue<T> _queue;
    mutable std::mutex _mutex;
    std::condition_variable _cv;
};
}  // namespace notify_queue

#endif //CPP_CPP_MULTITHREAD_LIB_NOTIFY_QUEUE_INCLUDE_NOTIFY_QUEUE_H_
