#include <catch2/catch_test_macros.hpp>
#include "mayak/logger/core/state.hpp"

using namespace mayak::logger::core;

TEST_CASE("Set and get logger state", "[core][state]") {
    enabled(false);
    REQUIRE_FALSE(enabled());

    minLevelPriority(40);
    REQUIRE(minLevelPriority() == 40);
}
