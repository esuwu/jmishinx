//
// Created by kira on 29.09.2020.
//

#ifndef CPP_CPP_MULTITHREAD_LIB_THREAD_POLL_INCLUDE_THREAD_POLL_H_
#define CPP_CPP_MULTITHREAD_LIB_THREAD_POLL_INCLUDE_THREAD_POLL_H_

#include "notify_queue.h"

#include <thread>
#include <functional>
#include <atomic>

namespace thread_poll {
class ThreadPoll {
 public:
    explicit ThreadPoll(size_t num_threads = std::thread::hardware_concurrency());

    ThreadPoll(ThreadPoll &&other) noexcept;
    ThreadPoll &operator=(ThreadPoll &&other) noexcept;

    ~ThreadPoll();

    notify_queue::NotifyQueue<std::function<void()>> &q();
    std::mutex &mutex();
    void wait_until_all_complete();

 private:
    void initialize(size_t num_threads);
    void stop_plz();

    notify_queue::NotifyQueue<std::function<void()>> _q{};
    std::mutex _mutex;
    std::vector<std::thread> _poll{};
    std::atomic<bool> _run{true};
};
}  // namespace thread_poll

#endif //CPP_CPP_MULTITHREAD_LIB_THREAD_POLL_INCLUDE_THREAD_POLL_H_
