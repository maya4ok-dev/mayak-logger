/// @example minimal.cpp
/// @brief Minimal example of using mayak::logger core.
/// @details
/// This example demonstrates how to set up a custom console sink
/// and log a simple "Hello, Project Mayak!" message.
///
/// Steps:
/// 1. Define a sink (destination for log messages).
/// 2. Register the sink with `Sink::createSink`.
/// 3. Use `mayak::log(level)` with stream syntax `<<`.
///
/// Expected output:
/// @code
/// [INFO] Hello, Project Mayak!
/// @endcode

#include <mayak/core/logger.hpp>
#include <iostream>
#include <string>

// Or you can use mayak::logger::core::Level directly for safety
using Level = mayak::logger::core::Level;
using Sink = mayak::logger::core::Sink;

/// @brief Example sink that outputs logs to the console.
struct ConsoleSink : Sink {
    void log(const std::string& msg) override {
        std::cout << msg;
    }
    void flush() override {
        std::cout << std::endl;
    }
};

int main() {
    // Create a log level.
    Level info("INFO", 40);
    // Register the sink.
    Sink::createSink<ConsoleSink>();
    // Log the message. 
    mayak::log(info) << "Hello, Project Mayak!";

    return 0;
}

