include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.10.0
)

FetchContent_MakeAvailable(catch2)

add_executable(tests
    test_core_ilogger.cpp
    test_core_isink.cpp
    test_core_level.cpp
    test_core_state.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain mayak_logger_core)

# ctest integration
include(CTest)
include(Catch)
catch_discover_tests(tests)
