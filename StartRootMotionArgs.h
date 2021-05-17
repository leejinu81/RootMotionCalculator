#pragma once

#include "Vector3Nx.h"

struct StartRootMotionArgs
{
    explicit StartRootMotionArgs(int const animNameHash, Vector3Nx const& lossyScale = Vector3Nx::one,
                                 float const speed = 1.0f, bool const bakeIntoPosY = false, bool const loop = false,
                                 float const startTimeRate = 0.0f)
            : animNameHash(animNameHash), lossyScale(lossyScale), speed(speed),
              bakeIntoPosY(bakeIntoPosY), loop(loop), startTimeRate(startTimeRate) {}

    int const animNameHash;
    Vector3Nx const lossyScale;
    float const speed;
    bool const bakeIntoPosY;
    bool const loop;
    float const startTimeRate;
};