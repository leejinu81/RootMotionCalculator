#pragma once

#include <vector>
#include "RootPosition.h"

// struct field ���̹� ��Ģ��??
struct AnimationClipData
{
    int animLengthMs{};
    std::vector<RootPosition> rootPositions{};
};
