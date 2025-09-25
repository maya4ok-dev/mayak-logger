#include "mayak/logger/core/stream.hpp"
#include "mayak/logger/core/level.hpp"
#include "mayak/logger/core/sinks.hpp"

namespace mayak::logger {

struct LoggerStream : core::ILoggerStream {
    LoggerStream(core::Level lvl) : _lvl(lvl.label) {} 

    void setLevel(core::Level& lvl) { _lvl = lvl.label; }

    void flush() override {
        auto msg = oss.str();
        if (msg.empty()) return;
        core::Sink::logAll("[" + _lvl + "] " + msg);
        core::Sink::flushAll();
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

struct NoOpStream : core::ILoggerStream {
    void flush() override {}
protected:
    void append(const std::string&) override {}
};

} // namespace mayak::logger


