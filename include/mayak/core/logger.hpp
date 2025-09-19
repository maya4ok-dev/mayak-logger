/// @file mayak/core/logger.hpp
/// @brief High-performance, header-only, and extremely flexible C++ logging library
/// @author Maya4ok (https://github.com/maya4ok-dev)
/// @license MIT

#pragma once

#include "logger/level.hpp"
#include "logger/sinks.hpp"
#include "logger/state.hpp"
#include "logger/stream.hpp"
#include "logger/proxy.hpp"

#ifndef MAYAK_LOGGER_CORE_ONLY
namespace mayak {

/// @brief Entry point for logging messages.
/// @param lvl Logging level (severity and label).
/// @return LoggerProxy object for streaming values with `<<`.
///
/// @details
/// Example:
/// @code
/// mayak::log(info) << "Hello, Mayak!";
/// @endcode
inline logger::core::LoggerProxy log(logger::core::Level lvl) {
    static logger::core::NoOpStream noop;
    thread_local logger::core::LoggerStream stream(lvl);

    if (lvl.priority < logger::core::minLevelPriority() || !logger::core::enabled())
        return logger::core::LoggerProxy{noop};
    
    return logger::core::LoggerProxy(stream);
}
}
#endif
