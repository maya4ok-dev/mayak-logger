#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "mayak/logger/core/stream.hpp"

using namespace mayak::logger::core;

struct TestStream : ILoggerStream {
    std::vector<std::string> messages;

    void flush() override {
        messages.clear();
    }

protected:
    void append(const std::string& msg) override {
        messages.push_back(msg);
    }
};

TEST_CASE("Append and flush messages to logger stream", "[core][stream]") {
    TestStream stream;

    stream << "Hello" << "World";
    stream << "!";

    REQUIRE(stream.messages.size() == 3);
    REQUIRE(stream.messages[0] == "Hello");
    REQUIRE(stream.messages[1] == "World");
    REQUIRE(stream.messages[2] == "!");

    stream.flush();
    REQUIRE(stream.messages.empty());
}
