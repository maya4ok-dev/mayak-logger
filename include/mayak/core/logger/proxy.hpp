#include "mayak/core/logger/stream.hpp"
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
