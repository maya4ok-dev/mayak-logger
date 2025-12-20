/// @file logger/core/ilogger.hpp
/// @brief Logger interface.
/// @author Maya4ok (https://github.com/maya4ok-dev)

#pragma once

#include <sstream>
#include <string>
#include <type_traits>

namespace mayak::logger::core {

/// @struct ILogger
/// @brief A logger interface.
struct ILogger {
    /// @brief A logger stream destructor.
    virtual ~ILogger() = default;

    /// @brief Flushes the messages from the buffer.
    virtual void flush() = 0;

    /// @brief Appends the message to the buffer.
    /// @param msg The message to append.
    virtual void append(const std::string& msg) = 0;
    
    /// @brief A template method to append values.
    /// @tparam T Type value to append.
    /// @param val Value to append.
    /// @todo use CPO + ADL to format to string.
    template<typename T>
    void append(const T& val) {
        if constexpr(std::is_arithmetic_v<T>) {
            append(std::to_string(val));
        } else {
            std::ostringstream tmp;
            tmp << val;
            append(tmp.str());
        }
    }
};

}

