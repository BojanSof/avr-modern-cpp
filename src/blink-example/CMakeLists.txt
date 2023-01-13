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

avr_generate_hex_files(${TARGET})

if(AVR_GENERATE_UPLOAD_TARGETS)
    avr_generate_flash_target(${TARGET})
endif(AVR_GENERATE_UPLOAD_TARGETS)