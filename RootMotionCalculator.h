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

    void Stop();

    friend std::ostream& operator<<(std::ostream& os, RootMotionCalculator const& rootMotionCalculator);

    constexpr static float DefaultSpeedMultiplier = 1.0f;

    void SetScaleMultiplier(float scale);

    float GetScaleMultiplier() const;

private:
    Vector3 CalcLerpPosition(int rootPosTime);

    RootPosition GetPrevRootMotion(int index) const;

    static Vector3 CalcLerpPosition(RootPosition const& prev, RootPosition const& current, int rootPosTimeMs);

    bool IsBetweenLastRootPositionAndAnimLength(int rootPosTimeMs, int lastRootPositionTimeMs) const;

    Vector3 CalcDeltaPosition(bool isOverTurningPoint, Vector3 const& prev, Vector3 const& cur, bool isRewind);

    Vector3 CalcDeltaPositionOverTurningPoint(Vector3 const& prev, Vector3 const& cur, bool isRewind) const;

    float GetSpeedMultiplierOrDefault(int layerIndex = 0);

    int const layerIndex_;
    std::vector<RootPosition> const rootPositions_;
    bool const bakeIntoPosY_;
    Vector3 const scale_;
    int const animLength_;
    bool const ignoreDeltaPos_;

    Vector3 prevPos_;
    std::map<int, float> speedMultipliers_;
    float scaleMultiplier_ = DefaultSpeedMultiplier;
    Vector3 deltaPosition_;
    float animNormalizedTime_;
};