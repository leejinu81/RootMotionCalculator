#pragma once

#include <map>
#include "Vector3Nx.h"

class AnimationSimulatorModel
{
public:
    float GetSpeedMultiplier(int layerIndex = 0) const;

    constexpr static float DefaultSpeedMultiplier = 1.0f;

    Vector3Nx deltaPosition;
    float animNormalizedTime;

    const float &scaleMultiplier = scaleMultiplier_;
private:
    mutable std::map<int, float> speedMultipliers_{};
    float scaleMultiplier_{};
};