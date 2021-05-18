#include "RootMotionCalculator.h"

RootMotionCalculator::RootMotionCalculator(int layerIndex,
                                           StartRootMotionArgs const& args,
                                           AnimationClipData const& clipData,
                                           bool ignoreDeltaPos)
        : layerIndex_(layerIndex),
          rootPositions_(clipData.rootPositions),
          animLength_(clipData.animLengthMs),
          bakeIntoPosY_(args.bakeIntoPosY),
          scale_(args.lossyScale),
          ignoreDeltaPos_(ignoreDeltaPos)
{
    prevPos_ = !rootPositions_.empty() ? rootPositions_[0].pos_ : Vector3();
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

    // deltaPosition 로컬변수라서 사라지지 않나??
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
    if (IsBetweenLastRootPositionAndAnimLength(rootPosTime, lastRootPosition.timeMs_))
    {
        return lastRootPosition.pos_;
    }

    return Vector3::zero;
}

RootPosition RootMotionCalculator::GetPrevRootMotion(int index) const
{
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
    auto const timeRatio = static_cast<float>(static_cast<double>(gap) / maxLerp);
    return Vector3::Lerp(prev.pos_, current.pos_, timeRatio);
}

bool RootMotionCalculator::IsBetweenLastRootPositionAndAnimLength(int rootPosTimeMs, int lastRootPositionTimeMs) const
{
    return lastRootPositionTimeMs < rootPosTimeMs && rootPosTimeMs <= animLength_;
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
    // 넘어갔을때 마지막값 더하기
    auto const endPrevPos = isRewind ? cur : prev;
    auto const endDelta = rootPositions_[rootPositions_.size() - 1].pos_ - endPrevPos;

    auto const startPrevPos = isRewind ? prev : cur;
    return startPrevPos + endDelta;
}

void RootMotionCalculator::Stop()
{
    deltaPosition_ = Vector3::zero;
}

float RootMotionCalculator::GetSpeedMultiplierOrDefault(int layerIndex)
{
    auto const[iter, success] = speedMultipliers_.insert({layerIndex, DefaultSpeedMultiplier});
    return success ? DefaultSpeedMultiplier : iter->second;
    // TODO 둘중 어느게 더 좋은가??
//        auto iter = speedMultipliers_.find(layerIndex);
//        if (iter != speedMultipliers_.end()) {
//            return iter->second;
//        }
//        speedMultipliers_.insert(layerIndex, DefaultSpeedMultiplier);
//return DefaultSpeedMultiplier;
}


void RootMotionCalculator::SetScaleMultiplier(float scale)
{
    scaleMultiplier_ = std::min(scale, 0.0f);
}

// For Debug
std::ostream& operator<<(std::ostream& os, RootMotionCalculator const& rootMotionCalculator)
{
    os << "[Layer:" << rootMotionCalculator.layerIndex_ << "] [" << rootMotionCalculator.animNormalizedTime_ << "] "
       << rootMotionCalculator.deltaPosition_;
    return os;
}

float RootMotionCalculator::GetScaleMultiplier() const
{
    return scaleMultiplier_;
}
