add_executable(minimal minimal.cpp)
target_link_libraries(minimal PRIVATE mayak_logger_core)

add_executable(custom_sink custom_sink.cpp)
target_link_libraries(custom_sink PRIVATE mayak_logger_core)

