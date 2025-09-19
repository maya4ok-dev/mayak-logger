/// @file mayak/core/logger/stream.hpp
/// @brief Logger's stream interface and minimal default implementations.
/// @author Maya4ok (https://github.com/maya4ok-dev)
/// @license MIT
///
/// @details
/// Defines the base stream interface (`ILoggerStream`) and two minimal
/// implementations:
/// - `LoggerStream` - active logging stream bound to a log level.
/// - `NoOpStream` - no-op strean for disabled or filtered logs.

#pragma once

#include <sstream>
#include <string>
#include <type_traits>

#include "level.hpp"
#include "sinks.hpp"

namespace mayak::logger::core {

struct ILoggerStream {
    virtual ~ILoggerStream() { flush(); }

    template<typename T>
    ILoggerStream& operator<<(const T& val) {
        append(val);
        return *this;
    }

    virtual void flush() {}

protected:
    virtual void append(const std::string& msg) = 0;
    
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

#ifndef MAYAK_LOGGER_CORE_ONLY

struct LoggerStream : ILoggerStream {
    LoggerStream(Level lvl) : _lvl(lvl.label) {} 

    void setLevel(Level& lvl) { _lvl = lvl.label; }

    void flush() override {
        auto msg = oss.str();
        if (msg.empty()) return;
        Sink::logAll("[" + _lvl + "] " + msg);
        Sink::flushAll();
        oss.clear();
    }

protected:
    void append(const std::string& msg) override {
        oss << msg;
    }

private:
    std::ostringstream oss;
    std::string _lvl;
};

struct NoOpStream : ILoggerStream {
    void flush() override {}
protected:
    void append(const std::string&) override {}
};

#endif

}

