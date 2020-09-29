add_library(thread_poll src/thread_poll.cpp)
target_include_directories(thread_poll PUBLIC include)
target_link_libraries(thread_poll PUBLIC pthread notify_queue)
