#include "RootMotionCalculator.h"
#include <cassert>

RootMotionCalculator::RootMotionCalculator(int layerIndex,
                                           StartRootMotionArgs const& args,
                                           AnimationClipData const& clipData,
                                           bool ignoreDeltaPos)
        : layerIndex_(layerIndex),
          bakeIntoPosY_(args.bakeIntoPosY),
          scale_(args.lossyScale),
          rootPositions_(clipData.rootPositions),
          animLength_(clipData.animLengthMs),
          ignoreDeltaPos_(ignoreDeltaPos)
{
    prevPos_ = GetDefaultPrevPos();
}

Vector3 RootMotionCalculator::GetDefaultPrevPos()
{
    return rootPositions_.empty() ? Vector3::zero : rootPositions_[0].pos_;
}

// 매 틱 마다 부르기 때문에 최적화에 신경써야됨
std::tuple<Vector3, float> RootMotionCalculator::OnTick(int repeatMs, bool isTurningPoint)
{
    if (rootPositions_.empty())
    { return std::make_tuple(Vector3::zero, 0.0f); }

    auto deltaPosition = Vector3::zero;
    if (!ignoreDeltaPos_)
    {
        auto const newPos = CalcLerpPosition(repeatMs);
        auto const isRewind = GetSpeedMultiplierOrDefault(layerIndex_) < 0.0f;
        auto const deltaPos = CalcDeltaPosition(isTurningPoint, prevPos_, newPos, isRewind);
        auto const scale = scale_ * scaleMultiplier_;
        deltaPosition = Vector3::Scale(deltaPos, scale);
        prevPos_ = newPos;
    }

    auto const normalize = (float) repeatMs / (float) animLength_;
    auto const animNormalizedTime = std::clamp(normalize, 0.0f, 1.0f);

    return std::make_tuple(deltaPosition, animNormalizedTime);
}

Vector3 RootMotionCalculator::CalcLerpPosition(int rootPosTime)
{
    if (rootPositions_.empty())
    { return Vector3::zero; }

    for (auto index = 0; index < rootPositions_.size(); ++index)
    {
        auto const& current = rootPositions_[index];
        if (rootPosTime <= current.timeMs_)
        {
            return CalcLerpPosition(GetPrevRootMotion(index), current, rootPosTime);
        }
    }

    auto const lastRootPosition = rootPositions_[rootPositions_.size() - 1];
    // 마지막 RootMotion과 animLength 사이에 Tick이 들어오면
    if (IsBetweenLastRootPosAndAnimLength(rootPosTime, lastRootPosition.timeMs_))
    {
        return lastRootPosition.pos_;
    }

    return Vector3::zero;
}

RootPosition RootMotionCalculator::GetPrevRootMotion(int index) const
{
    assert(!rootPositions_.empty());
    return index == 0 ? RootPosition::EmptyRootPosition : rootPositions_[index - 1];
}

Vector3 RootMotionCalculator::CalcLerpPosition(RootPosition const& prev,
                                               RootPosition const& current,
                                               int rootPosTimeMs)
{
    auto const maxLerp = current.timeMs_ - prev.timeMs_;
    if (maxLerp <= 0)
    { return prev.pos_; }

    auto const gap = rootPosTimeMs - prev.timeMs_;
    auto const timeRatio = (float) gap / (float) maxLerp;
    return Vector3::Lerp(prev.pos_, current.pos_, timeRatio);
}

bool RootMotionCalculator::IsBetweenLastRootPosAndAnimLength(int rootPosTimeMs, int lastRootPosTimeMs) const
{
    return lastRootPosTimeMs < rootPosTimeMs && rootPosTimeMs <= animLength_;
}

Vector3 RootMotionCalculator::CalcDeltaPosition(bool isOverTurningPoint, Vector3 const& prev, Vector3 const& cur,
                                                bool isRewind)
{
    Vector3 const delta = isOverTurningPoint ?
                          CalcDeltaPositionOverTurningPoint(prev, cur, isRewind) :
                          cur - prev;

    return bakeIntoPosY_ ? Vector3(delta.X(), 0, delta.Z()) : delta;
}

Vector3 RootMotionCalculator::CalcDeltaPositionOverTurningPoint(Vector3 const& prev, Vector3 const& cur,
                                                                bool isRewind) const
{
    assert(!rootPositions_.empty());
    // 넘어갔을때 마지막값 더하기
    auto const endPrevPos = isRewind ? cur : prev;
    auto const endDelta = rootPositions_[rootPositions_.size() - 1].pos_ - endPrevPos;

    auto const startPrevPos = isRewind ? prev : cur;
    return startPrevPos + endDelta;
}

float RootMotionCalculator::GetSpeedMultiplierOrDefault(int layerIndex)
{
    auto const[iter, success] = speedMultipliers_.insert({layerIndex, DefaultSpeedMultiplier});
    return success ? DefaultSpeedMultiplier : iter->second;
}

void RootMotionCalculator::SetScaleMultiplier(float scale)
{
    scaleMultiplier_ = std::min(scale, 0.0f);
}

float RootMotionCalculator::GetScaleMultiplier() const
{
    return scaleMultiplier_;
}

void RootMotionCalculator::Stop()
{
    prevPos_ = GetDefaultPrevPos();
}
