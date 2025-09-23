/// @example custom_sink.cpp
/// @brief Example of creating a custom logger sink
/// @details
/// This example demonstrates how to create a custom sink
/// and use it for logging.
///
/// Steps:
/// 1. Define a sink class where:
///   * `void log(const std::string& msg)` - writes a message to the buffer.
///   * `void flush()` - sends the buffered message to the output.
/// 2. Register a sink with `Sink::createSink<T>(Args &&args...)`
/// 
/// Expected output (file):
/// @code
/// [INFO] Hello, Project Mayak!
/// @endcode

#include <mayak/core/logger.hpp>
#include <fstream>

using namespace mayak::logger::core;

struct FileSink : Sink {
    std::ofstream ofs;

    // Opens the file with the given filename in append mode.
    FileSink(const std::string& filename) {
        ofs.open(filename, std::ios::app);
        if (!ofs.is_open())
            throw std::runtime_error("FileSink: Cannot open log file: " + filename);
    }

    // Writes a message directly to the file.
    void log(const std::string& msg) override {
        ofs << msg;
    }

    // Flushes the file stream to ensure the message is written.
    void flush() override {
        ofs << std::endl;
        ofs.flush();
    }
};

int main() {
    // Standard logger routine.
    Level info("INFO", 40);
    Sink::createSink<FileSink>("mylog.txt");

    // Message will appear in `mylog.txt`, but not in stdout.
    mayak::log(info) << "Hello, Project Mayak!";

    return 0;
}
