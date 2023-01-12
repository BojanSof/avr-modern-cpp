# AVR uploading tool

# upload tool
find_program(AVRDUDE NAMES avrdude HINTS ${AVRDUDE_PATH})

# programmer
if(NOT AVR_PROGRAMMER)
    set(AVR_PROGRAMMER usbasp
        CACHE STRING "Programmer used for uploading to the target. Default: usbasp")
endif(NOT AVR_PROGRAMMER)

if(NOT AVR_PROGRAMMER_BAUDRATE)
    set(AVR_PROGRAMMER_BAUDRATE ""
        CACHE STRING "Programmer's baud rate. Default is: (empty)")
endif(NOT AVR_PROGRAMMER_BAUDRATE)

if(NOT AVR_PROGRAMMER_PORT)
    set(AVR_PROGRAMMER_PORT "usb"
        CACHE STRING "Programmer's port. Default is: usb")
endif(NOT AVR_PROGRAMMER_PORT)

function(avr_generate_flash_target TARGET)
    set(HEX ${TARGET}.hex)
    set(AVRDUDE_PARAMS -c ${AVR_PROGRAMMER} -P ${AVR_PROGRAMMER_PORT} -p ${AVR_MCU})
    if(NOT AVR_PROGRAMMER_BAUDRATE STREQUAL "")
        set(AVRDUDE_PARAMS ${AVRDUDE_PARAMS} -b ${AVR_PROGRAMMER_BAUDRATE})
    endif(NOT AVR_PROGRAMMER_BAUDRATE STREQUAL "")

    set(AVRDUDE_PARAMS ${AVRDUDE_PARAMS} -U flash:w:${HEX}:i)

    add_custom_target(${TARGET}-flash
        COMMAND ${AVRDUDE} ${AVRDUDE_PARAMS}
        DEPENDS "$<TARGET_FILE:${TARGET}>"
    )
endfunction()

function(avr_generate_eeprom_target TARGET)
    set(HEX ${TARGET}_eeprom.hex)
    set(AVRDUDE_PARAMS -c ${AVR_PROGRAMMER} -P ${AVR_PROGRAMMER_PORT} -p ${AVR_MCU})
    if(NOT AVR_PROGRAMMER_BAUDRATE STREQUAL "")
        set(AVRDUDE_PARAMS ${AVRDUDE_PARAMS} -b ${AVR_PROGRAMMER_BAUDRATE})
    endif(NOT AVR_PROGRAMMER_BAUDRATE STREQUAL "")

    set(AVRDUDE_PARAMS ${AVRDUDE_PARAMS} -U eeprom:w:${HEX}:i)

    add_custom_target(${TARGET}-eeprom
        COMMAND ${AVRDUDE} ${AVRDUDE_PARAMS}
        DEPENDS "$<TARGET_FILE:${TARGET}>"
    )
endfunction()