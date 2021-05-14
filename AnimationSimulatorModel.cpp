#include "AnimationSimulatorModel.h"

float AnimationSimulatorModel::GetSpeedMultiplier(int layerIndex) const
{
    auto[iter, success] = speedMultipliers_.insert({layerIndex, DefaultSpeedMultiplier});
    return success ? DefaultSpeedMultiplier : iter->second;
    // TODO ���� ����� �� ������??
//        auto iter = speedMultipliers_.find(layerIndex);
//        if (iter != speedMultipliers_.end()) {
//            return iter->second;
//        }
//        speedMultipliers_.insert(layerIndex, DefaultSpeedMultiplier);
//return DefaultSpeedMultiplier;
}
