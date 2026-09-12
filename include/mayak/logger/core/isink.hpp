/// @file logger/core/isink.hpp
/// @brief Provides a sink interface.
/// @author Maya4ok (https://github.com/maya4ok-dev)

#pragma once

#include <string>

namespace mayak::logger::core {

/// @class Sink
/// @brief A sink interface
/// @details
/// Defines the abstract sink interface used to send messages to an I/O.
/// It is a polymorphic structure to provide a persistent runtime state.
///
/// A "sink" is the final destination of a log message (e.g. console, file,
/// syslog, custom handler).
///
/// Example of a custom sink:
/// @code
/// struct ConsoleSink : mayak::logger::core::Sink {
///     void log(const std::string& msg) override {
///         std::cout << msg << std::endl;
///     }
/// };
/// @endcode
struct Sink {
    virtual ~Sink() = default;

    /// @brief Write a message to an I/O.
    /// @param msg The message to write.
    virtual void log(const std::string& msg) = 0;
};

}
