/// @file logger/core/stream.hpp
/// @brief Logger stream proxy
/// @author Maya4ok (https://github.com/maya4ok-dev)
///
/// @details
/// Defines the logger stream wrapper, used to wrap an abstract interface `ILogger`.
/// The proxy is returned by the main entry point (`mayak::log`) and allows
/// streaming values with `<<` operator while ensuring flush
/// when the proxy goes out of scope (RAII).

#include "ilogger.hpp"
namespace mayak::logger::core {

/// @struct LoggerStrean
/// @brief The logger stream proxy, used to wrap `ILogger`.
/// @details
/// Allows streaming values with `<<` operator while ensuring flush
/// when the proxy goes out of scope (RAII).
struct LoggerStream {
    ILogger& logger; ///< A reference to the logger stream implementation.

    /// @brief A template operator that forward a value to a stream.
    /// @tparam T The type of value to be forwarded.
    /// @param val A value to be forwarded.
    /// @return A reference to current LoggerProxy.
    template<typename T>
    LoggerStream& operator<<(const T& val) {
        logger.append(val);
        return *this;
    }

    /// @brief Flushes the wrapped logger stream when the proxy goes out of scope.
    ~LoggerStream() {
        logger.flush();
    }
};

}
