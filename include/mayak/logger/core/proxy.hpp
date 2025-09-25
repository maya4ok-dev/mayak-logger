/// @file logger/core/proxy.hpp
/// @brief Logger stream proxy
/// @author Maya4ok (https://github.com/maya4ok-dev)
/// @license MIT
///
/// @details
/// Desines the logger stream proxy, used to wrap an abstract interface `ILoggerStream`.
/// The proxy is returned by the main entry point (`mayak::log`) and allows
/// streaming values with `<<` operator while ensuring flush
/// when the proxy goes out of scope (RAII).

#include "stream.hpp"
namespace mayak::logger::core {

struct LoggerProxy {
    ILoggerStream& stream;

    template<typename T>
    LoggerProxy& operator<<(const T& val) {
        stream << val;
        return *this;
    }

    ~LoggerProxy() {
        stream.flush();
    }
};

}
