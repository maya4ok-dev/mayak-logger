/// @file logger/stream.hpp
/// @brief A logger streams implementation.
/// @author Maya4ok (https://github.com/maya4ok-dev)
/// 
/// @details
/// Defines the logger stream implementation based on `logger::core::ILoggerStream`:
/// - `LoggerStream` - active logging stream bound to a log level.
/// - `NoOpStream` - no-op stream for disabled or filtered logs.

#pragma once

#include "mayak/logger/core/ilogger.hpp"
#include "mayak/logger/core/level.hpp"
#include "mayak/logger/core/isink.hpp"

namespace mayak::logger {

/// @struct LoggerStream
/// @brief A logger stream implementation.
///
/// @details
/// Collects messages with `<<` stream and sends them to all registered sinks.
struct Logger : core::ILogger {
    /// @brief A logger stream constructor.
    /// @param lvl A log level.
    /// @todo `core::Level` -> `const core::Level&`
    Logger(core::Level lvl) : _lvl(lvl.label) {} 

    /// @brief Sets the logger stream level.
    /// @param lvl A reference to the log level to set.
    /// @todo `core::Level&` -> `const core::Level&`
    void setLevel(core::Level& lvl) { _lvl = lvl.label; }

    /// @brief Flushes the messages to all registered sinks.
    /// @details
    /// Overrides `core::ILoggerStream::flush`.
    /// This method performs the following steps:
    /// - Formats the message,
    /// - Sends it to all registered sinks,
    /// - Flushes all registered sinks,
    /// - Clears the internal buffer.
    ///
    /// @note
    /// For now, log messages formats in `flush()` method. It's really recommended
    /// to separate the formatting of messages from this method.
    void flush() override {
        auto msg = oss.str();
        if (msg.empty()) return;
        core::Sink::logAll("[" + _lvl + "] " + msg);
        core::Sink::flushAll();
        oss.clear();
    }

    /// @brief Appends the message from operator `<<` to internal buffer.
    /// @details
    /// Overrides `core::ILoggerStream::append`.
    /// @param msg A const reference to the message string to append.
    void append(const std::string& msg) override {
        oss << msg;
    }

private:
    std::ostringstream oss; ///< Internal buffer for stream messages.
    std::string _lvl;       ///< Current log level label.
};

/// @struct NoOpStream
/// @brief A no-operation logger stream implementation
/// @details
/// A no-operation (noop) zero-cost stream for disabled logs.
/// Doesn't collects or logs messages.
struct NoOpLogger : core::ILogger {
    /// @brief Appends messages (does nothing)
    void append(const std::string&) override {}
    void flush() override {}
};

} // namespace mayak::logger

