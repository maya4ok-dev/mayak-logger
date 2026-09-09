/// @file logger/core/ilogger.hpp
/// @brief Logger interface.
/// @author Maya4ok (https://github.com/maya4ok-dev)

#pragma once

#include <sstream>
#include <string>
#include <memory>
#include <vector>

#include "isink.hpp"
#include "level.hpp"

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
