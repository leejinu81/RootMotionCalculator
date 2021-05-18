#pragma once

#include <utility>
#include <vector>
#include "RootPosition.h"

struct AnimationClipData
{
    AnimationClipData(int const animLengthMs, std::vector<RootPosition> rootPositions)
            : animLengthMs(animLengthMs), rootPositions(std::move(rootPositions))
    {}

    int const animLengthMs;
    std::vector<RootPosition> const rootPositions;
};
