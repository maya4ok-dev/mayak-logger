/// @file logger/core/level.hpp
/// @brief Defines logging levels used to categorize log messages.
/// @author Maya4ok (https://github.com/maya4ok-dev)
///
/// @details
/// The `Level` struct represents a logging level with a textual label
/// and a numeric priority. The priority is used to filter log messages:
/// messages with a lower priority than the current minimum will be ignored.
///
/// Example usage:
/// @code
/// mayak::logger::core::Level info("INFO", 40);
/// mayak::logger::core::Level debug("DEBUG", 10);
/// mayak::log(info) << "Hello, Mayak!";
/// @endcode

#pragma once

#include <string>

namespace mayak::logger::core {

/// @struct Level
/// @brief A log level structure.
struct Level {
    std::string label; ///< A level label for visual purposes.
    int priority; ///< A level priority, higher = more severe.

    /// @brief A log level constructor
    /// @param label A level label for visual purposes.
    /// @param priority The integer priority of this log level (higher = more severe).
    Level(std::string label, int priority) : label(label), priority(priority) {}
};

}
