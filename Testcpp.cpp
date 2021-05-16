#include <iostream>
#include "RootMotionCalculator.h"

int main()
{
    auto arg = StartRootMotionArgs(1);
    auto animPos = std::vector<RootPosition>({RootPosition(0, Vector3Nx::zero), RootPosition(100, Vector3Nx(1, 0, 0))});
    auto animationClipData = AnimationClipData(100, animPos);
    auto rmc = RootMotionCalculator(0, arg, animationClipData);

    auto const[p, n] = rmc.OnTick(30, false);
    std::cout << p << n << std::endl;

    auto const[p2, n2] = rmc.OnTick(70, false);
    std::cout << p2 << n2 << std::endl;

    rmc.Stop();
}