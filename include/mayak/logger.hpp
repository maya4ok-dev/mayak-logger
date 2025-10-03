/// @file logger.hpp
/// @brief High-performance, header-only, and extremely flexible C++ logging library
/// @author Maya4ok (https://github.com/maya4ok-dev)

#pragma once

#include "logger/core/level.hpp"
#include "logger/core/sinks.hpp"
#include "logger/core/state.hpp"
#include "logger/core/stream.hpp"
#include "logger/core/proxy.hpp"
#include "logger/stream.hpp"

#ifndef MAYAK_LOGGER_CORE_ONLY
namespace mayak {

/// @brief Entry point for logging messages.
/// @param lvl Logging level (priority and label).
/// @return LoggerProxy object for streaming values with `<<`.
///
/// @details
/// Example:
/// @code
/// mayak::log(info) << "Hello, Mayak!";
/// @endcode
inline logger::core::LoggerProxy log(logger::core::Level lvl) {
    static logger::NoOpStream noop;
    thread_local logger::LoggerStream stream(lvl);

    if (lvl.priority < logger::core::minLevelPriority() || !logger::core::enabled())
        return logger::core::LoggerProxy{noop};
    
    return logger::core::LoggerProxy(stream);
}
}
#endif
