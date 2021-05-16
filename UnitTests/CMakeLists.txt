project(UnitTests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(UnitTests_run RootMotionCalculatorTest.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
#target_link_libraries(UnitTests_run DateConverter_lib)

#target_link_libraries(UnitTests_run gtest gtest_main)
