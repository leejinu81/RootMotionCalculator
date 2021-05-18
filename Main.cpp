#include <iostream>
#include "gtest/gtest.h"
#include "RootMotionCalculator.h"

auto const kAnimPos = std::vector<RootPosition>(
        {
                RootPosition(0, Vector3::zero),
                RootPosition(200, Vector3(0, 1, 1)),
                RootPosition(400, Vector3(0, 0, 2)),
                RootPosition(600, Vector3(0, 3, 3)),
                RootPosition(700, Vector3(0, 0, 5)),
        });

TEST(Test, BakeIntoPosY가_True이면_DeltaPosition의_Y가_0이다)
{
    auto const arg = StartRootMotionArgs(1, Vector3::one, 1.0f, true);
    auto const animationClipData = AnimationClipData(1000, kAnimPos);
    auto rmc = RootMotionCalculator(0, arg, animationClipData);

    auto const[pos, nor] = rmc.OnTick(200, false);
    EXPECT_EQ(pos, Vector3(0, 0, 1));

    auto const[pos2, nor2] = rmc.OnTick(600, false);
    EXPECT_EQ(pos2, Vector3(0, 0, 2));
}

TEST(Test, TestDeltaPosition)
{
    auto const arg = StartRootMotionArgs(1);
    auto const animationClipData = AnimationClipData(1000, kAnimPos);
    auto rmc = RootMotionCalculator(0, arg, animationClipData);

    auto const[pos, nor] = rmc.OnTick(200, false);
    EXPECT_EQ(pos, Vector3(0, 1, 1));
    auto const[pos2, nor2] = rmc.OnTick(400, false);
    EXPECT_EQ(pos2, Vector3(0, -1, 1));
    auto const[pos3, nor3] = rmc.OnTick(600, false);
    EXPECT_EQ(pos3, Vector3(0, 3, 1));
}

TEST(Test, TurningPoint지나가는_DeltaTime이면_마지막지점과_더해서_DeltaPosition이_나온다)
{
    auto const arg = StartRootMotionArgs(1, Vector3::one, 1.0f, true);
    auto const animationClipData = AnimationClipData(1000, kAnimPos);
    auto rmc = RootMotionCalculator(0, arg, animationClipData);

    auto const[pos, nor] = rmc.OnTick(100, true);
    // Vector3(0,0,0.5f) + Vector3(0,0,5)
    EXPECT_EQ(pos, Vector3(0, 0, 5.5f));

    auto const[pos2, nor2] = rmc.OnTick(300, true);
    // Vector3(0,0,5) - Vector3(0,0, 0.5f) + Vector3(0,0,1.5f)
    EXPECT_EQ(pos2, Vector3(0, 0, 6));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}