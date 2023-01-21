cmake_minimum_required(VERSION 3.18)

add_library(AvrHw STATIC)

target_sources(AvrHw
    PUBLIC
        "include/AvrHw/Platform.hpp"
        "include/AvrHw/Gpio.hpp"
    PRIVATE
        "src/AvrHw/empty.cpp"
)

target_include_directories(AvrHw
    PUBLIC
        include
)

target_link_libraries(AvrHw
    PUBLIC
        Mmio
)

target_compile_features(AvrHw
    PUBLIC
        cxx_std_20
)