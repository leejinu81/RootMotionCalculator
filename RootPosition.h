#pragma once

#include "Vector3Nx.h"

struct RootPosition final
{
    RootPosition(int timeMs, const Vector3Nx& pos)
            : timeMs_(timeMs), pos_(pos) {}

    static RootPosition const EmptyRootPosition;

    int const timeMs_;
    Vector3Nx const pos_;
};