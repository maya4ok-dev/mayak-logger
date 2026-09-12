/// @ingroup Logger
/// @example minimal.cpp
/// @brief Minimal example of using mayak::logger.
/// @details
/// This example demonstrates how to log a simple "Hello, Project Mayak!" message
///
/// Steps:
/// 1. Create a logger instance
/// 2. Add a provided console sink
/// 3. Log some messages using mayak::logger!
///
/// Expected output:
/// @code
/// [INFO] Hello, Project Mayak!
/// [INFO] Number: 579
/// @endcode

#include <mayak/logger.hpp>

// It's recommended to avoid typing a long namespace
using mayak::logger::core::flush;

int main() {
    // Create a logger
    mayak::logger::core::Logger ml;

    // Add a sink
    ml.addSink<mayak::logger::ConsoleSink>();

    // Set a log level if needed
    // Default level is INFO with priority 40
    // Level debug("DEBUG", 10);
    // ml.level(debug);

    // Done! Now log messages using DSL
    ml << "Hello, Project Mayak!" << flush;
    ml << "Number: " << (123 + 456) << flush;

    return 0;
}
