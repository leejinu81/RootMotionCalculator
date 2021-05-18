#pragma once

#include "Vector3.h"

struct RootPosition final
{
    RootPosition(int timeMs, Vector3 const& pos)
            : timeMs_(timeMs), pos_(pos) {}

    static RootPosition const EmptyRootPosition;

    int const timeMs_;
    Vector3 const pos_;
};