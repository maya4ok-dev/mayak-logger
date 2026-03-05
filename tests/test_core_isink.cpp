#include <doctest/doctest.h>
#include <vector>
#include "mayak/logger/core/isink.hpp"

struct TestSink : mayak::logger::core::Sink {
    std::vector<std::string> messages;

    void log(const std::string& msg) override {
        messages.push_back(msg);
    }

    void flush() override {
        messages.clear();
    }
};

TEST_CASE("Sink logs and flushes messages") {
    TestSink sink;

    sink.log("Hello, World!");
    sink.log("1234567890");

    CHECK(sink.messages.size() == 2);
    CHECK(sink.messages[0] == "Hello, World!");
    CHECK(sink.messages[1] == "1234567890");

    sink.flush();

    CHECK(sink.messages.empty());
}
