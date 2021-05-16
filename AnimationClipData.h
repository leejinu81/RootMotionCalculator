#pragma once

#include <utility>
#include <vector>
#include "RootPosition.h"

struct AnimationClipData
{
    AnimationClipData(const int animLengthMs, std::vector<RootPosition>  rootPositions)
            : animLengthMs(animLengthMs), rootPositions(std::move(rootPositions))
    {}

    const int animLengthMs;
    const std::vector<RootPosition> rootPositions;
};
