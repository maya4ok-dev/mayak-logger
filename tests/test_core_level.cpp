#include <catch2/catch_test_macros.hpp>
#include "mayak/logger/core/level.hpp"

using namespace mayak::logger::core;

TEST_CASE("Level struct basic properties", "[level]") {
    Level info("INFO", 40);
    Level debug("DEBUG", 10);

    REQUIRE(info.label == "INFO");
    REQUIRE(info.priority == 40);

    REQUIRE(debug.label == "DEBUG");
    REQUIRE(debug.priority == 10);
}
