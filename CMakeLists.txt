cmake_minimum_required(VERSION 3.19)
project(Testcpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(Testcpp Testcpp.cpp Vector3Nx.cpp Vector3Nx.h RootPosition.cpp RootPosition.h StartRootMotionArgs.h AnimationClipData.h RootMotionCalculator.cpp RootMotionCalculator.h UnitTests/RootMotionCalculatorTest.cpp)
