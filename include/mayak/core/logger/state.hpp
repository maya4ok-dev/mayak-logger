#pragma once

#include <atomic>
#include <mutex>
namespace mayak::logger::core {

inline struct LoggerState {
    std::atomic<bool> enabled{true};
    std::atomic<int> minLevelPriority{0};
    std::mutex mtx;
} state;

[[nodiscard]] inline bool enabled() { return state.enabled.load(); }
inline void enabled(bool value) { state.enabled.store(value); }

[[nodiscard]] inline int minLevelPriority() { return state.minLevelPriority.load(); }
inline void minLevelPriority(int value) { state.minLevelPriority.store(value); }

}
