cmake_minimum_required(VERSION 3.18)

project(
    avr-modern-cpp
    VERSION 0.1
    DESCRIPTION "Modern C++ on AVR 8-bit MCUs"
    LANGUAGES C CXX ASM
)

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/cmake"
)

option(AVR_GENERATE_UPLOAD_TARGETS "Generate upload targets" ON)

if(AVR_GENERATE_UPLOAD_TARGETS)
    include("avr_upload")
endif(AVR_GENERATE_UPLOAD_TARGETS)

add_subdirectory(src)