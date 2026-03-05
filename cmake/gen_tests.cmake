file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)
find_package(doctest)
if (doctest_FOUND)
    add_executable(tests ${TEST_SOURCES})
    set_target_properties(tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
    target_link_libraries(tests PRIVATE mayak_logger_core doctest::doctest)
endif()
