#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "mayak/logger/core/proxy.hpp"
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

TEST_CASE("Append and flush messages to logger stream using proxy", "[core][proxy]") {
    TestStream stream;
    
    {
        LoggerProxy proxy(stream);
        proxy << "Hello" << "World";

        REQUIRE(stream.messages.size() == 2);
        REQUIRE(stream.messages[0] == "Hello");
        REQUIRE(stream.messages[1] == "World");
    }
    
    REQUIRE(stream.messages.empty());
}
