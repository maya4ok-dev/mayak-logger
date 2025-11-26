/// @file logger/core/isink.hpp
/// @brief Logger sink base interface.
/// @author Maya4ok (https://github.com/maya4ok-dev)
///
/// @details
/// Defines the abstract sink interface used to handle log messages.
///
/// A "sink" is the final destination of a log message (e.g. console, file,
/// syslog, custom handler). All sinks registered in the logger receive the
/// same message via `logAll`.
///
/// Example of a custom sink:
/// @code
/// struct ConsoleSink : mayak::logger::core::Sink {
///     void log(const std::string& msg) override {
///         std::cout << msg << std::endl;
///     }
///     void flush() override {
///         std::cout << std::flush;
///     }
/// };
///
/// // Register sink
/// mayak::logger::core::Sink::createSink<ConsoleSink>();
/// @endcode
///
/// Built-in helpers:
/// - `logAll` - broadcasts message to all registered sinks.
/// - `flushAll` - flushes all sinks.
/// - `createSink<T>` - helper to create and register new sink instance.

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace mayak::logger::core {

/// @class Sink
/// @brief A sink interface
class Sink {
private:
    static inline std::vector<std::unique_ptr<Sink>> sinks{}; ///< A vector of sink pointers

public:
    /// @brief Destroys the sink.
    /// @note This method is virtual and must be overridden by derived sinks.
    virtual ~Sink() = default;

    /// @brief Log to all registered sinks
    /// @param msg A message to log
    static void logAll(const std::string& msg) {
        for (auto& sink : sinks) {
            sink->log(msg);
        }   
    }

    /// @brief Flush all registered sinks
    static void flushAll() {
        for (auto& sink : sinks) {
            sink->flush();
        }
    }

    /// @brief Write a message to the sink.
    /// @param msg The message to write.
    /// @note This method is virtual and must be overridden by derived sinks.
    virtual void log(const std::string& msg) = 0;

    /// @brief Flushes the sink's internal buffers.
    /// @note This method is virtual and must be overridden by derived sinks.
    virtual void flush() = 0;

    /// @brief Register and create a sink
    /// @tparam T A type that inherits from Sink
    /// @tparam Args Argument types to forward to Sink's constructor
    /// @param args Arguments to forward to Sink's constructor
    /// @return A raw pointer to the created sink
    template<typename T, typename... Args>
    static T* createSink(Args&&... args) {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = ptr.get();
        sinks.push_back(std::move(ptr));
        return raw;
    }
};

}
