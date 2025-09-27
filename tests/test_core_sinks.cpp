#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "mayak/logger/core/sinks.hpp"

struct TestSink : mayak::logger::core::Sink {
    std::vector<std::string> messages;

    void log(const std::string& msg) override {
        messages.push_back(msg);
    }

    void flush() override {
        messages.clear();
    }
};

TEST_CASE("Sink logs and flushes messages", "[core][sink]") {
    auto sink = mayak::logger::core::Sink::createSink<TestSink>();

    mayak::logger::core::Sink::logAll("Hello, World!");
    mayak::logger::core::Sink::logAll("1234567890");

    REQUIRE(sink->messages.size() == 2);
    REQUIRE(sink->messages[0] == "Hello, World!");
    REQUIRE(sink->messages[1] == "1234567890");

    mayak::logger::core::Sink::flushAll();

    REQUIRE(sink->messages.empty());
}
