#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include "RootPosition.h"
#include "StartRootMotionArgs.h"
#include "AnimationClipData.h"

class RootMotionCalculator final
{
public:
    RootMotionCalculator(int layerIndex,
                         const StartRootMotionArgs& args,
                         const AnimationClipData& clipData,
                         bool ignoreDeltaPos = false);

    std::tuple<Vector3Nx, float> OnTick(int repeatMs, bool isTurningPoint);

    void Stop();

    void SetScaleMultiplier(float scale);

    friend std::ostream& operator<<(std::ostream& os, const RootMotionCalculator& rootMotionCalculator);

    constexpr static float DefaultSpeedMultiplier = 1.0f;

    const float& scaleMultiplier = scaleMultiplier_;

private:
    Vector3Nx CalcLerpPosition(int rootPosTime);

    RootPosition GetPrevRootMotion(int index);

    static Vector3Nx CalcLerpPosition(const RootPosition& prev, const RootPosition& current, int rootPosTimeMs);

    bool IsBetweenLastRootPositionAndAnimLength(int rootPosTimeMs, int lastRootPositionTimeMs) const;

    Vector3Nx CalcDeltaPosition(bool isOverTurningPoint, const Vector3Nx& prev, const Vector3Nx& cur, bool isRewind);

    Vector3Nx CalcDeltaPositionOverTurningPoint(const Vector3Nx& prev, const Vector3Nx& cur, bool isRewind) const;

    float GetSpeedMultiplierOrDefault(int layerIndex = 0);

    const int layerIndex_;
    const std::vector<RootPosition> rootPositions_;
    const bool bakeIntoPosY_;
    const Vector3Nx scale_;
    const int animLength_;
    const bool ignoreDeltaPos_;

    Vector3Nx prevPos_;
    std::map<int, float> speedMultipliers_;
    float scaleMultiplier_ = DefaultSpeedMultiplier;
    Vector3Nx deltaPosition_;
    float animNormalizedTime_;
};