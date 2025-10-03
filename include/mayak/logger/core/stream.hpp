/// @file logger/core/stream.hpp
/// @brief Logger's stream interface.
/// @author Maya4ok (https://github.com/maya4ok-dev)

#pragma once

#include <sstream>
#include <string>
#include <type_traits>

namespace mayak::logger::core {

/// @struct ILoggerStream
/// @brief A logger stream interface.
struct ILoggerStream {
    /// @brief A logger stream destructor.
    /// @todo `flush()` is redudant; RAII proxy already handles flushing.
    virtual ~ILoggerStream() { flush(); }

    /// @brief template operator to append any values to the stream.
    /// @tparam T Type of the value to append.
    /// @param val Value to append.
    /// @return Reference to this ILoggerStream.
    /// @todo Remove this operator; RAII proxy handles streaming.
    template<typename T>
    ILoggerStream& operator<<(const T& val) {
        append(val);
        return *this;
    }

    /// @brief Flushes the messages from the buffer.
    /// @note This method may not be overriden, no-op by default.
    virtual void flush() {}

protected:
    /// @brief Appends the message to the buffer.
    /// @param msg The message to append.
    virtual void append(const std::string& msg) = 0;
    
    /// @brief A template method to append values.
    /// @tparam T Type value to append.
    /// @param val Value to append.
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

