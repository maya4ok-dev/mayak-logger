#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace mayak::logger::core {

class Sink {
private:
    static inline std::vector<std::unique_ptr<Sink>> sinks{};

public:
    virtual ~Sink() = default;

    static void logAll(const std::string& msg) {
        for (auto& sink : sinks) {
            sink->log(msg);
        }
    }
    static void flushAll() {
        for (auto& sink : sinks) {
            sink->flush();
        }
    }

    virtual void log(const std::string& msg) = 0;
    virtual void flush() = 0;

    template<typename T, typename... Args>
    static T* createSink(Args&&... args) {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = ptr.get();
        sinks.push_back(std::move(ptr));
        return raw;
    }
};

}
