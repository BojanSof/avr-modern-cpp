# AVR CMake toolchain file

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# find toolchain programs
find_program(CMAKE_C_COMPILER NAMES avr-gcc HINTS ${TOOLCHAIN_BIN_PATH} REQUIRED)
find_program(CMAKE_CXX_COMPILER NAMES avr-g++ HINTS ${TOOLCHAIN_BIN_PATH} REQUIRED)
find_program(CMAKE_ASM_COMPILER NAMES avr-gcc HINTS ${TOOLCHAIN_BIN_PATH} REQUIRED)
find_program(CMAKE_OBJCOPY NAMES avr-objcopy HINTS ${TOOLCHAIN_BIN_PATH} REQUIRED)
find_program(CMAKE_SIZE NAMES avr-size HINTS ${TOOLCHAIN_BIN_PATH} REQUIRED)
find_program(CMAKE_OBJDUMP NAMES avr-objdump HINTS ${TOOLCHAIN_BIN_PATH})
find_program(CMAKE_CPPFILT NAMES avr-c++filt HINTS ${TOOLCHAIN_BIN_PATH})

# cross-compilation vars 
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# executables suffixes
set(CMAKE_EXECUTABLE_SUFFIX_C   .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)
set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)

# MCU related
if(NOT AVR_MCU)
    set(AVR_MCU attiny2313
        CACHE STRING "MCU used in the project. Default: attiny2313")
endif(NOT AVR_MCU)
# MCU clock freq
# if(NOT F_CPU)
#     set(F_CPU 8000000
#         CACHE STRING "MCU clock frequency in Hz. Default: 8000000")
# endif(NOT F_CPU)

# compile options
add_compile_options(
    -mmcu=${AVR_MCU} # MCU
    -Os
    -Wall # enable warnings
    -Wno-main
    -Wundef
    -pedantic
    -Wstrict-prototypes
    -Werror
    -Wfatal-errors
    -Wl,--relax,--gc-sections
)
# C flags
set(CMAKE_C_FLAGS
    -funsigned-char
    -funsigned-bitfields
    -fpack-struct
    -fshort-enums
    -ffunction-sections
    -fdata-sections
    -fno-split-wide-types
    -fno-tree-scev-cprop
)
string(REPLACE ";" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
# C++ flags
set(CMAKE_CXX_FLAGS
  -fno-exceptions
  -fno-unwind-tables
  -fno-rtti
  -fno-threadsafe-statics
)
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# linker options
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${AVR_MCU})

# functions for creating targets
function(avr_generate_binary_file TARGET)
    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:${TARGET}>" "$<TARGET_FILE_BASE_NAME:${TARGET}>.bin"
        COMMAND ${CMAKE_SIZE} "$<TARGET_FILE:${TARGET}>"
        BYPRODUCTS ${TARGET}.bin
        COMMENT "Generate binary file ${CMAKE_PROJECT_NAME}.bin"
    )
endfunction()

function(avr_generate_hex_file TARGET)
    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -R .eeprom -O ihex "$<TARGET_FILE:${TARGET}>" "$<TARGET_FILE_BASE_NAME:${TARGET}>.hex"
        COMMAND ${CMAKE_SIZE} "$<TARGET_FILE:${TARGET}>"
        BYPRODUCTS ${TARGET}.hex
        COMMENT "Generate flash hex file ${CMAKE_PROJECT_NAME}.hex"
    )
endfunction()

function(avr_generate_eeprom_hex_file TARGET)
    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -j .eeprom -O ihex "$<TARGET_FILE:${TARGET}>" "$<TARGET_FILE_BASE_NAME:${TARGET}>_eeprom.hex"
        COMMAND ${CMAKE_SIZE} "$<TARGET_FILE:${TARGET}>"
        BYPRODUCTS ${TARGET}_eeprom.hex
        COMMENT "Generate eeprom hex file ${CMAKE_PROJECT_NAME}.hex"
    )
endfunction()