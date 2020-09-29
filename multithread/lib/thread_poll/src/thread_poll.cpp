//
// Created by kira on 29.09.2020.
//

#include "thread_poll.h"

#include <chrono>
#include <iostream>
#include <sstream>

using namespace std::chrono_literals;

namespace thread_poll {
ThreadPoll::ThreadPoll(size_t num_threads) {
    initialize(num_threads);
}
ThreadPoll::ThreadPoll(ThreadPoll &&other) noexcept {
    stop_plz();
    initialize(other._poll.size());
    _run = true;
}
ThreadPoll &ThreadPoll::operator=(ThreadPoll &&other) noexcept {
    stop_plz();
    initialize(other._poll.size());
    _run = true;
    return *this;
}
ThreadPoll::~ThreadPoll() {
    stop_plz();
}
notify_queue::NotifyQueue<std::function<void()>> &ThreadPoll::q() {
    return _q;
}
void ThreadPoll::wait_until_all_complete() {
    std::condition_variable cv;
    std::unique_lock lock{_mutex};
    while (not _q.empty()) {
        cv.wait_for(lock, 100ms);
    }
}
std::mutex &ThreadPoll::mutex() {
    return _mutex;
}
void ThreadPoll::initialize(size_t num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
        _poll.emplace_back(
            [this, i] {
                while (_run) {
                    {
                        std::stringstream ss;
                        std::lock_guard _{_mutex};
                        ss << "---------------------------------------\n" << "thread # " << i << "\n";
                        std::cout << ss.str();
                    }
                    _q.pop()();
                }
            }
        );
    }
}
void ThreadPoll::stop_plz() {
    _run = false;
    _q.clear();
    for (size_t i = 0; i < _poll.size(); ++i) {
        _q.push([] {});
    }

    for (auto &job: _poll) {
        job.join();
    }
}
}  // namespace thread_poll
