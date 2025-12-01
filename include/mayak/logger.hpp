/// @file logger.hpp
/// @brief High-performance, header-only, and extremely flexible C++ logging library
/// @author Maya4ok (https://github.com/maya4ok-dev)

#pragma once

#include "logger/core/level.hpp"
#include "logger/core/isink.hpp"
#include "logger/core/state.hpp"
#include "logger/core/ilogger.hpp"
#include "logger/core/stream.hpp"
#include "logger/stream.hpp"

#ifndef MAYAK_LOGGER_CORE_ONLY
namespace mayak {

/// @brief Entry point for logging messages.
/// @param lvl Logging level (priority and label).
/// @return LoggerStream used to stream values with `<<`.
///
/// @details
/// Example:
/// @code
/// mayak::log(info) << "Hello, Mayak!";
/// @endcode
inline logger::core::LoggerStream log(logger::core::Level lvl) {
    static logger::NoOpLogger noop;
    thread_local logger::Logger stream(lvl);

    if (lvl.priority < logger::core::minLevelPriority() || !logger::core::enabled())
        return logger::core::LoggerStream{noop};
    
    return logger::core::LoggerStream{stream};
}
}
#endif
