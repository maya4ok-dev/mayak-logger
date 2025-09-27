cmake_minimum_required(VERSION 3.10)
project(mayak_logger_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(mayak_logger_core INTERFACE)

target_include_directories(mayak_logger_core INTERFACE include)

add_subdirectory(examples)
add_subdirectory(tests)
