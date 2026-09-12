/// @ingroup Logger
/// @example custom_sink.cpp
/// @brief Example of creating a custom logger sink
/// @details
/// This example demonstrates how to create a custom sink
/// and use it for logging.
///
/// Steps:
///
/// - 1. Implement a sink class:
/// @code{.cpp}
/// void log(const std::string& msg) override {
///     ofs << msg << std::endl;
/// }
/// @endcode
///
/// - 2. Add it:
/// @code{.cpp}
/// logger.addSink<FileSink>("mylog.txt");
/// @endcode
/// 
/// Expected output (file):
/// @code
/// [INFO] Hello, Project Mayak!
/// @endcode

#include <mayak/logger.hpp>
#include <fstream>

using mayak::logger::core::flush;

struct FileSink : mayak::logger::core::Sink {
    std::ofstream ofs;

    // Opens the file with the given filename in append mode.
    FileSink(const std::string& filename) {
        ofs.open(filename, std::ios::app);
        if (!ofs.is_open())
            throw std::runtime_error("FileSink: Cannot open log file: " + filename);
    }

    // Writes a message directly to the file.
    void log(const std::string& msg) override {
        ofs << msg << std::endl;
    }
};

int main() {
    // Create a logger object
    mayak::logger::core::Logger ml;

    // Register our sink
    ml.addSink<FileSink>("mylog.txt");

    // Message will appear in `mylog.txt`, (not in stdout).
    ml << "Hello, Project Mayak!" << flush;
    return 0;
}
