/// @file logger/core/ilogger.hpp
/// @brief Logger interface.
/// @author Maya4ok (https://github.com/maya4ok-dev)

#pragma once

#include <sstream>
#include <string>
#include <type_traits>
#include <memory>
#include <vector>

#include "isink.hpp"
#include "level.hpp"

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

namespace mayak::logger::core {

struct Flush {};
inline Flush flush;

class Logger {
    std::vector<std::unique_ptr<Sink>> sinks;
    std::stringstream buffer;
    Level level;

    void flush() {
        auto msg = buffer.str();
        if (msg.empty() || sinks.empty()) return;
        for (auto& sink : sinks) {
            sink->log("[" + level.label + "] " + msg);
            sink->flush();
        }
        buffer.str("");
        buffer.clear();
    }
public:

    Logger() : level("INFO", 40) {}

    template<typename T>
    Logger& operator<<(const T& val) {
        buffer << val;
        return *this;
    }

    template<typename SinkType, typename... Args>
    Logger& addSink(Args&&... args) {
        sinks.push_back(std::make_unique<SinkType>(std::forward<Args>(args)...));
        return *this;
    }

    Logger& setLevel(Level lvl) {
        level = lvl;
        return *this;
    }

    Logger& operator<<(Flush) {
        flush();
        return *this;
    }

    ~Logger() { flush(); }

};

}
