#pragma once

#include "Vector3Nx.h"

struct RootPosition final
{
    RootPosition(int timeMs, Vector3Nx const& pos)
            : timeMs_(timeMs), pos_(pos) {}

    static RootPosition const EmptyRootPosition;

    int const timeMs_;
    Vector3Nx const pos_;
};