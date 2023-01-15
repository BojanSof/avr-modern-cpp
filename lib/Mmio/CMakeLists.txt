cmake_minimum_required(VERSION 3.18)

add_library(Mmio INTERFACE)

target_sources(Mmio
    INTERFACE
        "include/Mmio/Register.hpp"
        "include/Mmio/Mmio.hpp"
)

target_include_directories(Mmio
    INTERFACE
        include
)

target_compile_features(Mmio
    INTERFACE
        cxx_std_20
)