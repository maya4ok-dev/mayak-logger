/// @ingroup Logger
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

// 1. Include the main header.
#include <mayak/logger.hpp>

// 2. Make aliases for types to simplify the code so you don't have to type long namespaces.
using Level = mayak::logger::core::Level;
using mayak::logger::core::flush;

int main() {
    // 3. Create a logger
    mayak::logger::core::Logger ml;

    // 4. Add a sink
    ml.addSink<mayak::logger::ConsoleSink>();

    // Set a log level if needed
    // Default level is INFO with priority 40
    // Level debug("DEBUG", 10);
    // ml.setLevel(debug);

    // 5. Done! Now log messages using DSL
    ml << "Hello, Project Mayak!" << flush;
    ml << "Number: " << (123 + 456) << flush;

    return 0;
}
