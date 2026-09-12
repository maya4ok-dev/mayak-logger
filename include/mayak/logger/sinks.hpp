#include "core/isink.hpp"

#include <iostream>
#include <string>

namespace mayak::logger {

struct ConsoleSink : mayak::logger::core::Sink {
    void log(const std::string& msg) override {
        std::cout << msg << std::endl;
    }
};

}
