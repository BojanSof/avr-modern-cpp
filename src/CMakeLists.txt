cmake_minimum_required(VERSION 3.18)

if(CMAKE_CROSSCOMPILING)
    add_subdirectory(blink-example)
    add_subdirectory(gpio-example)
endif(CMAKE_CROSSCOMPILING)