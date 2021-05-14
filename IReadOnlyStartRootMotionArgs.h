
#ifndef TESTCPP_IREADONLYSTARTROOTMOTIONARGS_H
#define TESTCPP_IREADONLYSTARTROOTMOTIONARGS_H

#include "Vector3Nx.h"

class IReadOnlyStartRootMotionArgs {
public:
    virtual int GetAnimNameHash() const = 0;

    virtual Vector3Nx GetLossyScale() const = 0;

    virtual float GetSpeed() const = 0;

    virtual bool GetBakeIntoPosY() const = 0;

    virtual bool GetLoop() const = 0;

    virtual float GetStartTimeRate() const = 0;
};

#endif //TESTCPP_IREADONLYSTARTROOTMOTIONARGS_H
