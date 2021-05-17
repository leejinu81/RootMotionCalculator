cmake_minimum_required(VERSION 3.19)
#CMake 에서 FetchContent 모듈을 사용을 위해 include
include(FetchContent)

#외부 프로젝트인 googletest를 추가하기 위한 저장소 지정
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0
)

project(Testcpp)
#add_subdirectory(UnitTests)

set(CMAKE_CXX_STANDARD 20)

#googletest의 프로퍼티를 가져와 현재 프로젝트가 populate 되지 않았으면
#FetchContent_Populate를 통해서 하위 빌드 설정
FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    #googletest를 빌드하기위한 sub-build 구성
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)
endif ()

add_executable(Testcpp Main.cpp Vector3Nx.cpp Vector3Nx.h RootPosition.cpp RootPosition.h StartRootMotionArgs.h AnimationClipData.h RootMotionCalculator.cpp RootMotionCalculator.h RootMotionCalculatorTest.cc)

#단위 테스트를 위해 libgtest, libgtest_main 라이브러리 링크
target_link_libraries(Testcpp gtest gtest_main)
