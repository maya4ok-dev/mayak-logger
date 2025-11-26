/// @ingroup Logger
/// @example custom_logger.cpp
/// @brief Example of creating a custom logger object
/// @details
/// This example demonstrates how to create a custom logger
/// object and use it for logging.
///
/// Steps:
/// 1. Define a stream class where:
///   * `void flush()` sends the buffered message to the sink.
///   * `void append()` adds a message to the buffer.
/// 2. Define a `log()` function that serves as a logger factory.
/// 3. Use the custom `log()` function to log messages.
///
/// Expected output:
/// @code
/// [INFO] Hello, Project Mayak!
/// @endcode

#include <mayak/logger.hpp>

#include <sstream>
#include <string>
#include <iostream>

namespace logger = mayak::logger::core;

/// @brief A custom logger object
struct CustomLogger : logger::ILogger {
    // Use setters to modify any data.
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

logger::LoggerStream log(logger::Level lvl) {
    // `thread_local` ensures the object has static storage duration within each thread.
    thread_local CustomLogger stream; 

    // Set level to stream.
    stream.setLevel(lvl);

    // LoggerStream is a stream wrapper separates the logger, defines a user-friendly API,
    // and allows to return different loggers (for example, no-op) in the same factory
    return logger::LoggerStream(stream);
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
