//
// Created by kira on 29.09.2020.
//

#include "thread_poll.h"

#include <iostream>


int main() {
    thread_poll::ThreadPoll poll{};

    for (int i = 0; i < 100; ++i) {
        poll.q().push([i, &poll]{
            std::lock_guard _{poll.mutex()};
            std::cout << "# " << i << std::endl;
        });
    }

    poll.wait_until_all_complete();
    return 0;
}
