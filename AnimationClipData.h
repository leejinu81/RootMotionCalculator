#pragma once

#include <vector>
#include "RootPosition.h"

// struct field 네이밍 규칙이??
struct AnimationClipData
{
    int animLengthMs{};
    std::vector<RootPosition> rootPositions{};
};
