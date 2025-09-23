/// @example custom_stream.cpp
/// @brief Example of creating a custom logger stream
/// @details
/// This example demonstrates how to create a custom logger
/// stream and use it for logging.
///
/// Steps:
/// 1. Define a stream class where:
///   * `void flush()` sends the buffered message to the sink.
///   * `void append()` adds a message to the buffer.
/// 2. Define a `log()` function that serves as a factory for creating logger streams.
/// 3. Use the custom `log()` function to log messages.
///
/// Expected output:
/// @code
/// [INFO] Hello, Project Mayak!
/// @endcode

#include <mayak/core/logger.hpp>

#include <sstream>
#include <string>
#include <iostream>

namespace logger = mayak::logger::core;

/// @brief A custom logger stream
struct CustomLoggerStream : logger::ILoggerStream {
    // Level setter is needed because the stream object is created only once
    // for the entire logger.
    void setLevel(logger::Level level) { _lvl = level.label; }

    // Flushes the buffered message to all registered sinks when destroyed.
    void flush() override {
        auto msg = oss.str();
        if (msg.empty())
          return;
        logger::Sink::logAll("[" + _lvl + "] " + msg);
        logger::Sink::flushAll();
    }

protected:
    // Append a message from << operator to the internal buffer.
    void append(const std::string& msg) override {
        oss << msg;
    }

private:
    std::ostringstream oss;
    std::string _lvl;
};

logger::LoggerProxy log(logger::Level lvl) {
    // `thread_local` ensures the object has static storage duration within each thread.
    thread_local CustomLoggerStream stream; 

    // Set level to stream.
    stream.setLevel(lvl);

    // Return stream wrapped in proxy.
    // `LoggerProxy` is a wrapper around a concrete ILoggerStream implementation.
    return logger::LoggerProxy(stream);
}

struct ConsoleSink : logger::Sink {
    void log(const std::string& msg) override {
        std::cout << msg;
    }
    void flush() override {
        std::cout << std::endl;
    }
};

int main() {
    // Standard logger routine.
    logger::Level info("INFO", 40);
    logger::Sink::createSink<ConsoleSink>();

    // Now use custom factory instead of the default logger.
    log(info) << "Hello, Project Mayak!";

    return 0;
}
