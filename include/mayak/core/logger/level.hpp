// include/mayak/core/logger/level.hpp

#pragma once

#include <string>

namespace mayak::logger::core {

struct Level {
    std::string label;
    int priority;

    Level(std::string label, int priority) : label(label), priority(priority) {}
};

}
