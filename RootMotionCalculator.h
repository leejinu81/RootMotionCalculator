#pragma once

#include <vector>
#include <algorithm>
#include "AnimationSimulatorModel.h"
#include "RootPosition.h"
#include "IReadOnlyStartRootMotionArgs.h"
#include "AnimationClipData.h"

class RootMotionCalculator final
{
public:
    RootMotionCalculator(int layerIndex,
                         const AnimationSimulatorModel &model,
                         const IReadOnlyStartRootMotionArgs &args,
                         const AnimationClipData &clipData,
                         bool ignoreDeltaPos = false);

    void OnTick(int repeatMs, bool isTurningPoint);

    void Stop();

private:
    Vector3Nx CalcLerpPosition(int rootPosTime);

    RootPosition GetPrevRootMotion(int index);

    static Vector3Nx CalcLerpPosition(const RootPosition &prev, const RootPosition &current, int rootPosTimeMs);

    bool IsBetweenLastRootPositionAndAnimLength(int rootPosTimeMs, int lastRootPositionTimeMs) const;

    Vector3Nx CalcDeltaPosition(bool isOverTurningPoint, const Vector3Nx &prev, const Vector3Nx &cur, bool isRewind);

    Vector3Nx CalcDeltaPositionOverTurningPoint(const Vector3Nx &prev, const Vector3Nx &cur, bool isRewind) const;

    const int layerIndex_;
    AnimationSimulatorModel model_;

    // time, position
    const std::vector<RootPosition> rootPositions_;

    const bool bakeIntoPosY_;
    const Vector3Nx scale_;
    const int animLength_;
    const bool ignoreDeltaPos_;

    Vector3Nx prevPos_;
};