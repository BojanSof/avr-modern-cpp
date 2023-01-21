#ifndef _AVRHW_PLATFORM_HPP
#define _AVRHW_PLATFORM_HPP

#include <stdint.h>

namespace Avr
{
#if defined(__AVR_ATtiny2313__)
    using AddressType = uint8_t;
#endif
    // GPIO related
#if defined(__AVR_ATtiny2313__)
    static constexpr AddressType GPIOA{0x19};
    static constexpr AddressType GPIOB{0x16};
    static constexpr AddressType GPIOC{0x00}; //< invalid
    static constexpr AddressType GPIOD{0x10};
    static constexpr AddressType GPIOE{0x00}; //< invalid
#endif
    enum class GpioPort : AddressType
    {
        Invalid = 0,
        A       = GPIOA,
        B       = GPIOB,
        C       = GPIOC,
        D       = GPIOD,
        E       = GPIOE
    };
    struct GpioDescriptor
    {
        GpioPort port;
        uint8_t pin;
    };
    struct GpioConfig
    {
        bool output;
        bool level;
    };
    enum GpioRegs : AddressType
    {
        PIN = 0,
        DDR = 1,
        PORT = 2
    };
}

#endif //_AVRHW_PLATFORM_HPP