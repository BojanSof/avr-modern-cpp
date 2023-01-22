cmake_minimum_required(VERSION 3.18)

add_executable(MmioTests
    Mmio_tests.cpp
)

target_link_libraries(MmioTests
    Mmio
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MmioTests MmioTests)