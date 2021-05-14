#include "RootPosition.h"

RootPosition::RootPosition()
        : timeMs_(), pos_() {}

RootPosition::RootPosition(int timeMs, const Vector3Nx& pos)
        : timeMs_(timeMs), pos_(pos)
{
}

const RootPosition RootPosition::EmptyRootPosition{};
