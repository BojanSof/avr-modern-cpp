cmake_minimum_required(VERSION 3.18)

add_library(HwReg INTERFACE)

target_sources(HwReg
    INTERFACE
        "include/HwReg/IoReg.hpp"
        "include/HwReg/TypeHelper.hpp"
)

target_include_directories(HwReg
    INTERFACE
        include
)

target_compile_features(HwReg
    INTERFACE
        cxx_std_20
)