add_library(epoll STATIC
        src/epoll_server.cpp
        src/epoll_base.cpp
        )
target_include_directories(epoll PUBLIC include)
target_link_libraries(epoll file_descriptor base_exception tcp thread_poll)
