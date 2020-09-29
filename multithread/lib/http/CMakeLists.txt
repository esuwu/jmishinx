add_library(http
        src/http_request.cpp
        src/http_response.cpp)
target_include_directories(http PUBLIC include)
target_link_libraries(http PUBLIC epoll base_exception)
