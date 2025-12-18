cmake_minimum_required(VERSION 3.27)

project(mayak_logger_core LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Library ---
add_library(mayak_logger_core INTERFACE)
target_include_directories(mayak_logger_core INTERFACE include)

# --- Subdirectories ---
add_subdirectory(examples)
add_subdirectory(tests)
include(cmake/gen_docs.cmake)
