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
                         StartRootMotionArgs const& args,
                         AnimationClipData const& clipData,
                         bool ignoreDeltaPos = false);

    std::tuple<Vector3, float> OnTick(int repeatMs, bool isTurningPoint);

    constexpr static float DefaultSpeedMultiplier = 1.0f;

    void SetScaleMultiplier(float scale);

    float GetScaleMultiplier() const;

    void Stop();

private:
    Vector3 GetDefaultPrevPos();

    Vector3 CalcLerpPosition(int rootPosTime);

    RootPosition GetPrevRootMotion(int index) const;

    static Vector3 CalcLerpPosition(RootPosition const& prev, RootPosition const& current, int rootPosTimeMs);

    bool IsBetweenLastRootPosAndAnimLength(int rootPosTimeMs, int lastRootPosTimeMs) const;

    Vector3 CalcDeltaPosition(bool isOverTurningPoint, Vector3 const& prev, Vector3 const& cur, bool isRewind);

    Vector3 CalcDeltaPositionOverTurningPoint(Vector3 const& prev, Vector3 const& cur, bool isRewind) const;

    float GetSpeedMultiplierOrDefault(int layerIndex = 0);

    int const layerIndex_;
    // StartRootMotionArgs
    bool const bakeIntoPosY_;
    Vector3 const scale_;
    bool const ignoreDeltaPos_;
    // AnimationClipData
    int const animLength_;
    std::vector<RootPosition> const rootPositions_;

    Vector3 prevPos_;
    std::map<int, float> speedMultipliers_;
    float scaleMultiplier_ = DefaultSpeedMultiplier;
};