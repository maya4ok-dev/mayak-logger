/// @file mayak/core/logger.hpp
/// @brief

#pragma once

#include "logger/level.hpp"
#include "logger/sinks.hpp"
#include "logger/state.hpp"
#include "logger/stream.hpp"
#include "logger/proxy.hpp"

#ifndef MAYAK_LOGGER_CORE_ONLY
namespace mayak {
inline logger::core::LoggerProxy log(logger::core::Level lvl) {
    static logger::core::NoOpStream noop;
    thread_local logger::core::LoggerStream stream(lvl);

    if (lvl.priority < logger::core::minLevelPriority() || !logger::core::enabled())
        return logger::core::LoggerProxy(noop);
    
    return logger::core::LoggerProxy(stream);
}
}
#endif
