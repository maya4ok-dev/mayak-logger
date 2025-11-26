#include <catch2/catch_test_macros.hpp>
#include "mayak/logger/core/ilogger.hpp"

using namespace mayak::logger::core;

struct TestLogger : ILogger {
    std::vector<std::string> messages;

    void flush() override {
        messages.clear();
    }

    void append(const std::string& msg) override {
        messages.push_back(msg);
    }
};

TEST_CASE("Append and flush messages to logger stream", "[core][stream]") {
    TestLogger stream;

    stream.append("Hello");
    stream.append("World");

    REQUIRE(stream.messages.size() == 2);
    REQUIRE(stream.messages[0] == "Hello");
    REQUIRE(stream.messages[1] == "World");

    stream.flush();
    REQUIRE(stream.messages.empty());
}
