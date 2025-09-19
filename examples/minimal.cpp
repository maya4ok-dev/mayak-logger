#include <mayak/core/logger.hpp>
#include <iostream>
#include <string>

struct ConsoleSink : mayak::logger::core::Sink {
    void log(const std::string& msg) override {
        std::cout << msg;
    }
    void flush() override {
        std::cout << std::endl;
    }
};

int main() {
    mayak::logger::core::Level info("INFO", 40);
    mayak::logger::core::Level debug("DEBUG", 10);
    mayak::logger::core::minLevelPriority(30);
    mayak::logger::core::Sink::createSink<ConsoleSink>();
    mayak::log(info) << "Hello, World!";
    mayak::log(debug) << "This won't appear";
}
