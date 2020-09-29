add_library(tcp STATIC
        src/tcp_server.cpp
        src/tcp_connection.cpp
        src/socket_properties.cpp
        )
target_include_directories(tcp PUBLIC include)
target_link_libraries(tcp file_descriptor base_exception)
