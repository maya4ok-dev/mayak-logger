cmake_minimum_required(VERSION 3.27)

project(mayak_logger_core LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Library ---
add_library(mayak_logger_core INTERFACE)
target_include_directories(mayak_logger_core INTERFACE include)

# --- Subdirectories ---

option(MAYAK_LOGGER_BUILD_EXAMPLES "Build usage examples" OFF)

if(MAYAK_LOGGER_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

option(MAYAK_LOGGER_BUILD_TESTS "Build tests" OFF)

if(MAYAK_LOGGER_BUILD_TESTS)
    include(cmake/gen_tests.cmake)
endif()

option(MAYAK_LOGGER_GENERATE_DOCS "Generate Doxygen documentation" OFF)

if(MAYAK_LOGGER_GENERATE_DOCS)
    include(cmake/gen_docs.cmake)
endif()
