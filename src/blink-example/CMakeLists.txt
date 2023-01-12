cmake_minimum_required(VERSION 3.18)

set(TARGET "blink-example")

add_executable(${TARGET})
target_sources(${TARGET}
    PRIVATE
        main.cpp
)

target_compile_features(${TARGET}
    PRIVATE
        cxx_std_17
        c_std_99
)

avr_generate_hex_file(${TARGET})
include("../../cmake/avr_upload.cmake")
avr_generate_flash_target(${TARGET})