include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.10.0
)

FetchContent_MakeAvailable(catch2)

add_executable(tests
    test_core_level.cpp
    test_core_proxy.cpp
    test_core_sinks.cpp
    test_core_state.cpp
    test_core_stream.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain mayak_logger_core)

