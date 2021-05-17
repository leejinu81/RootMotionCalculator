#include <iostream>
//#include <gtest/gtest.h>
//#include "RootMotionCalculator.h"
#include "gtest/gtest.h"

//int main()
//{
//    auto const arg = StartRootMotionArgs(1);
//    auto const animPos = std::vector<RootPosition>(
//            {
//                    RootPosition(0, Vector3Nx::zero),
//                    RootPosition(100, Vector3Nx(1, 0, 0))
//            });
//    auto const animationClipData = AnimationClipData(100, animPos);
//    auto rmc = RootMotionCalculator(0, arg, animationClipData);
//
//    auto const[p, n] = rmc.OnTick(30, false);
//    std::cout << p << n << std::endl;
//
//    auto const[p2, n2] = rmc.OnTick(70, false);
//    std::cout << p2 << n2 << std::endl;
//
//    rmc.Stop();
//}
TEST(Test, test)
{
    EXPECT_EQ(1,1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}