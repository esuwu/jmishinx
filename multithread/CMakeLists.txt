add_subdirectory(lib)

include_directories(include)

add_executable(derivative src/derivative.cpp)

add_executable(allocator src/allocator.cpp)

add_executable(tcp_server_example src/tcp_server_example.cpp)
add_executable(tcp_client_example src/tcp_client_example.cpp)
target_link_libraries(tcp_server_example PUBLIC tcp)
target_link_libraries(tcp_client_example PUBLIC tcp)

add_executable(epoll_client_example src/epoll_client_example.cpp)
add_executable(epoll_server_example src/epoll_server_example.cpp)
target_link_libraries(epoll_client_example PUBLIC epoll)
target_link_libraries(epoll_server_example PUBLIC epoll)

add_executable(notify_q_example src/notify_q_example.cpp)
target_link_libraries(notify_q_example notify_queue)

add_executable(thread_poll_example src/thread_poll_example.cpp)
target_link_libraries(thread_poll_example thread_poll)