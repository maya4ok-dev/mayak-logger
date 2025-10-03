/// @file logger/core/proxy.hpp
/// @brief Logger stream proxy
/// @author Maya4ok (https://github.com/maya4ok-dev)
///
/// @details
/// Defines the logger stream proxy, used to wrap an abstract interface `ILoggerStream`.
/// The proxy is returned by the main entry point (`mayak::log`) and allows
/// streaming values with `<<` operator while ensuring flush
/// when the proxy goes out of scope (RAII).

#include "stream.hpp"
namespace mayak::logger::core {

/// @struct LoggerProxy
/// @brief The logger stream proxy, used to wrap `ILoggerStream`.
/// @details
/// Allows streaming values with `<<` operator while ensuring flush
/// when the proxy goes out of scope (RAII).
struct LoggerProxy {
    ILoggerStream& stream; ///< A reference to the logger stream implementation.

    /// @brief A template operator that forward a value to a stream.
    /// @tparam T The type of value to be forwarded.
    /// @param val A value to be forwarded.
    /// @return A reference to current LoggerProxy.
    template<typename T>
    LoggerProxy& operator<<(const T& val) {
        stream << val; // maybe remove `<<` from the ILoggerStream and forward straight to `append()` method.
        return *this;
    }

    /// @brief Flushes the wrapped logger stream when the proxy goes out of scope.
    ~LoggerProxy() {
        stream.flush();
    }
};

}
