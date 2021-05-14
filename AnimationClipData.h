#ifndef TESTCPP_ANIMATIONCLIPDATA_H
#define TESTCPP_ANIMATIONCLIPDATA_H

#include <vector>
#include "RootPosition.h"

// struct field 네이밍 규칙이??
struct AnimationClipData {
    int animLengthMs{};
    std::vector<RootPosition> rootPositions{};
};
#endif //TESTCPP_ANIMATIONCLIPDATA_H
