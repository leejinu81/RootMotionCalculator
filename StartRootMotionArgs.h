#pragma once

#include "Vector3Nx.h"

struct StartRootMotionArgs
{
    explicit StartRootMotionArgs(const int animNameHash, const Vector3Nx& lossyScale = Vector3Nx::one,
                                 const float speed = 1.0f, const bool bakeIntoPosY = false, const bool loop = false,
                                 const float startTimeRate = 0.0f)
            : animNameHash(animNameHash), lossyScale(lossyScale), speed(speed),
              bakeIntoPosY(bakeIntoPosY), loop(loop), startTimeRate(startTimeRate)
    {}

    int animNameHash;
    Vector3Nx lossyScale;
    float speed;
    bool bakeIntoPosY;
    bool loop;
    float startTimeRate;
};