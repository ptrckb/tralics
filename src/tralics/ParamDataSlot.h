#pragma once
#include <string>

// parameterised data \todo RA useless?
struct ParamDataSlot {
    std::string key, value;
    bool        is_used{false};
};
