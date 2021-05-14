#include "AnimationSimulatorModel.h"

float AnimationSimulatorModel::GetSpeedMultiplier(int layerIndex) const
{
    auto[iter, success] = speedMultipliers_.insert({layerIndex, DefaultSpeedMultiplier});
    return success ? DefaultSpeedMultiplier : iter->second;
    // TODO 둘중 어느게 더 좋은가??
//        auto iter = speedMultipliers_.find(layerIndex);
//        if (iter != speedMultipliers_.end()) {
//            return iter->second;
//        }
//        speedMultipliers_.insert(layerIndex, DefaultSpeedMultiplier);
//return DefaultSpeedMultiplier;
}
