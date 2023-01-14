cmake_minimum_required(VERSION 3.18)

add_executable(HwRegTests
    TypeHelper_tests.cpp
)

target_link_libraries(HwRegTests
    HwReg
    GTest::gtest_main
)

add_test(HwRegTests HwRegTests)