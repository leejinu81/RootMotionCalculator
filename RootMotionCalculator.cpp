#include "RootMotionCalculator.h"

RootMotionCalculator::RootMotionCalculator(int layerIndex,
                                           const StartRootMotionArgs& args,
                                           const AnimationClipData& clipData,
                                           bool ignoreDeltaPos)
        : layerIndex_(layerIndex),
          rootPositions_(clipData.rootPositions),
          animLength_(clipData.animLengthMs),
          bakeIntoPosY_(args.bakeIntoPosY),
          scale_(args.lossyScale),
          ignoreDeltaPos_(ignoreDeltaPos)
{
    prevPos_ = !rootPositions_.empty() ? rootPositions_[0].pos_ : Vector3Nx();
}

// 매 틱 마다 부르기 때문에 최적화에 신경써야됨
std::tuple<Vector3Nx, float> RootMotionCalculator::OnTick(int repeatMs, bool isTurningPoint)
{
    if (rootPositions_.empty()) return std::make_tuple(Vector3Nx::zero, 0.0f);

    auto deltaPosition = Vector3Nx::zero;
    if (!ignoreDeltaPos_)
    {
        auto newPos = CalcLerpPosition(repeatMs);
        auto isRewind = GetSpeedMultiplierOrDefault(layerIndex_) < 0.0f;
        auto deltaPos = CalcDeltaPosition(isTurningPoint, prevPos_, newPos, isRewind);
        auto scale = scale_ * scaleMultiplier;
        deltaPosition = Vector3Nx::Scale(deltaPos, scale);
        prevPos_ = newPos;
    }

    auto normalize = (float) repeatMs / (float) animLength_;
    auto animNormalizedTime = std::clamp(normalize, 0.0f, 1.0f);

    // deltaPosition 로컬변수라서 사라지지 않나??
    return std::make_tuple(deltaPosition, animNormalizedTime);
}

Vector3Nx RootMotionCalculator::CalcLerpPosition(int rootPosTime)
{
    if (rootPositions_.empty()) return Vector3Nx::zero;

    for (auto index = 0; index < rootPositions_.size(); ++index)
    {
        auto const& current = rootPositions_[index];
        if (rootPosTime <= current.timeMs_)
        {
            return CalcLerpPosition(GetPrevRootMotion(index), current, rootPosTime);
        }
    }

    auto lastRootPosition = rootPositions_[rootPositions_.size() - 1];
    // 마지막 RootMotion과 animLength 사이에 Tick이 들어오면
    if (IsBetweenLastRootPositionAndAnimLength(rootPosTime, lastRootPosition.timeMs_))
    {
        return lastRootPosition.pos_;
    }

    return Vector3Nx::zero;
}

RootPosition RootMotionCalculator::GetPrevRootMotion(int index)
{
    return index == 0 ? RootPosition::EmptyRootPosition : rootPositions_[index - 1];
}

Vector3Nx RootMotionCalculator::CalcLerpPosition(const RootPosition& prev,
                                                 const RootPosition& current,
                                                 int rootPosTimeMs)
{
    auto maxLerp = current.timeMs_ - prev.timeMs_;
    if (maxLerp <= 0)
    {
        return prev.pos_;
    }

    auto gap = rootPosTimeMs - prev.timeMs_;
    auto timeRatio = static_cast<float>(static_cast<double>(gap) / maxLerp);
    return Vector3Nx::Lerp(prev.pos_, current.pos_, timeRatio);
}

bool RootMotionCalculator::IsBetweenLastRootPositionAndAnimLength(int rootPosTimeMs, int lastRootPositionTimeMs) const
{
    return lastRootPositionTimeMs < rootPosTimeMs && rootPosTimeMs <= animLength_;
}

Vector3Nx RootMotionCalculator::CalcDeltaPosition(bool isOverTurningPoint, const Vector3Nx& prev, const Vector3Nx& cur,
                                                  bool isRewind)
{
    Vector3Nx delta = isOverTurningPoint ?
                      CalcDeltaPositionOverTurningPoint(prev, cur, isRewind) :
                      cur - prev;

    return bakeIntoPosY_ ? Vector3Nx(delta.X(), 0, delta.Z()) : delta;
}

Vector3Nx RootMotionCalculator::CalcDeltaPositionOverTurningPoint(const Vector3Nx& prev, const Vector3Nx& cur,
                                                                  bool isRewind) const
{
    // 넘어갔을때 마지막값 더하기
    auto endPrevPos = isRewind ? cur : prev;
    auto endDelta = rootPositions_[rootPositions_.size() - 1].pos_ - endPrevPos;

    auto startPrevPos = isRewind ? prev : cur;
    return startPrevPos + endDelta;
}

void RootMotionCalculator::Stop()
{
    deltaPosition_ = Vector3Nx::zero;
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


void RootMotionCalculator::SetScaleMultiplier(const float scale)
{
    scaleMultiplier_ = std::min(scale, 0.0f);
}

// For Debug
std::ostream& operator<<(std::ostream& os, const RootMotionCalculator& rootMotionCalculator)
{
    os << "[Layer:" << rootMotionCalculator.layerIndex_ << "] [" << rootMotionCalculator.animNormalizedTime_ << "] "
       << rootMotionCalculator.deltaPosition_;
    return os;
}
