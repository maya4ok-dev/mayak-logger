/// @file logger/core/state.hpp
/// @brief Global logger state management.
/// @author Maya4ok (https://github.com/maya4ok-dev)
///
/// @details
/// Provides global logger configuration:
/// - `enabled` - enable or disable logging entirely.
/// - `minLevelPriority` - set the minimum severity
///   level required for a log message to be processed.
///
/// Typical usage:
/// @code
/// mayak::logger::core::enabled(true);
/// int current_priority = mayak::logger::core::minLevelPriority();
/// @endcode
///
/// @note
/// This file is not part of the core modules; it is temporarily placed in the `core/` directory.
#pragma once

#include <atomic>
#include <mutex>

namespace mayak::logger::core {

/// @brief A global logger state
inline struct LoggerState {
    std::atomic<bool> enabled{true}; ///< Is logger enabled or not.
    std::atomic<int> minLevelPriority{0}; ///< Minimum severity priority.
    std::mutex mtx; ///< Mutex for thread safety (currently unused)
} state; ///< A global logger state.

/// @brief Check if logging is enabled.
/// @return True if logging is enabled, false otherwise.
[[nodiscard]] inline bool enabled() { return state.enabled.load(); }

/// @brief Enable or disable logging globally.
/// @param value Pass true to enable logging, false to disable.
inline void enabled(bool value) { state.enabled.store(value); }

/// @brief Get the minimum severity priority required for logging.
/// @return Minimum severity priority.
[[nodiscard]] inline int minLevelPriority() { return state.minLevelPriority.load(); }

/// @brief Set the minimum severity priority required for logging.
/// @param value Minimum severity priority to set.
inline void minLevelPriority(int value) { state.minLevelPriority.store(value); }

} // namespace mayak::logger::core
