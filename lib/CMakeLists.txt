cmake_minimum_required(VERSION 3.18)

add_subdirectory(Mmio)

if(CMAKE_CROSSCOMPILING)
    add_subdirectory(AvrHw)
endif(CMAKE_CROSSCOMPILING)