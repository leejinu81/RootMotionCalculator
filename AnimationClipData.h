#ifndef TESTCPP_ANIMATIONCLIPDATA_H
#define TESTCPP_ANIMATIONCLIPDATA_H

#include <vector>
#include "RootPosition.h"

// struct field ���̹� ��Ģ��??
struct AnimationClipData {
    int animLengthMs{};
    std::vector<RootPosition> rootPositions{};
};
#endif //TESTCPP_ANIMATIONCLIPDATA_H
