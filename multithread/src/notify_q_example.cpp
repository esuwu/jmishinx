//
// Created by kira on 28.09.2020.
//

#include "notify_queue.h"

#include <iostream>
#include <sstream>
#include <chrono>

using namespace std::chrono_literals;

int main() {
    notify_queue::NotifyQueue<int> q{};

    std::thread t1{
        [&q] {
            for (int i = 0; i < 10; ++i) {
                q.push(i);
                std::this_thread::sleep_for(1s);
            }
        }
    };

    std::thread t2{
        [&q] {
            std::stringstream ss;
            for (int i = 0; i < 5; ++i) {
                ss << "t2: " << q.pop() << std::endl;
            }
            std::cout << ss.str();
        }
    };
    std::thread t3{
        [&q] {
            std::stringstream ss;
            for (int i = 0; i < 5; ++i) {
                ss << "t3: " << q.pop() << std::endl;
            }
            std::cout << ss.str();
        }
    };

    t1.join();
    t2.join();
    t3.join();
    q.clear();
    return 0;
}
