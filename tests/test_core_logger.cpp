#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <mayak/logger.hpp>
#include <vector>
#include <string>

std::vector<std::string> buffer;

struct Sink : mayak::logger::core::Sink {
    void log(const std::string& msg) override {
        buffer.push_back(msg);
    }
};

TEST_CASE("(core) testing the logger itself") {
    mayak::logger::core::Logger logger;
    logger.addSink<Sink>();

    logger << "Hello" << "World";
    CHECK(buffer.empty());

    logger << mayak::logger::core::flush;
    CHECK(buffer.size() == 1);
    CHECK(buffer[0] == "[INFO] HelloWorld");
}
