add_library(notify_queue INTERFACE)
target_include_directories(notify_queue INTERFACE include)
target_link_libraries(notify_queue INTERFACE pthread)
