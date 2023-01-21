#ifndef _AVRHW_GPIO_HPP
#define _AVRHW_GPIO_HPP

#include <Mmio/Mmio.hpp>
#include "AvrHw/Platform.hpp"

namespace Avr
{
    namespace Gpio
    {
        constexpr GpioDescriptor parseGpio(const char* const gpioStr)
        {
            // string format [PORT][PIN]
            // ex. A2, B3, D7
            uint8_t iPos = 0;
            if(gpioStr[iPos] == '\0') return {GpioPort::Invalid}; //< invalid config string
            // find port
            const char portOrd = gpioStr[iPos];
            // check if port is in bounds
            if(portOrd < 'A' || portOrd > 'E') return {GpioPort::Invalid}; //< invalid config string
            GpioPort port{GpioPort::Invalid};
            switch(portOrd)
            {
                case 'A': port = GpioPort::A; break;
                case 'B': port = GpioPort::B; break;
                case 'C': port = GpioPort::C; break;
                case 'D': port = GpioPort::D; break;
                case 'E': port = GpioPort::E; break;
                default: port = GpioPort::Invalid; break;
            }
            ++iPos;
            if(gpioStr[iPos] == '\0') return{GpioPort::Invalid}; //< invalid config string
            // find pin number
            if(gpioStr[iPos] < '0' || gpioStr[iPos] > '8') return{GpioPort::Invalid}; //< invalid config string
            const uint8_t pin = gpioStr[iPos] - '0';
            // fill gpio descriptor
            GpioDescriptor desc{port, pin};
            return desc;
        }

        constexpr GpioConfig parseConfigString(const char* const configStr)
        {
            // string format: [I/O][P (only if I)][L/H (only if O)]
            // ex. OL (output, low initial level)
            uint8_t iPos = 0;
            if(configStr[iPos] == '\0') return {}; //< invalid config string
            GpioConfig desc{};
            // input or output
            bool output = false;
            if(configStr[iPos] == 'I')
            {
                output = false;
            }
            else if(configStr[iPos] == 'O')
            {
                output = true;
            }
            else return {}; //< invalid config string
            desc.output = output;
            ++iPos;
            if(configStr[iPos] == '\0') return desc;
            // input or output specific options
            bool level = false;
            // if input, check if maybe P is added (PULL-UP)
            if(output && configStr[iPos] == 'P')
            {
                ++iPos;
                level = true;
            }
            // if output, check initial level
            else if(!output)
            {
                if(configStr[iPos] == 'H')
                {
                    level = true;
                    ++iPos;
                }
                else if(configStr[iPos] == 'L')
                {
                    level = false;
                    ++iPos;
                }
            }
            desc.level = level;
            return desc;
        }

        // compile-time tests
        namespace Test
        {
            // static tests for parseGpio
            static_assert(parseGpio("B5").port == GpioPort::B, "Invalid port parsing");
            static_assert(parseGpio("B5").pin == 5, "Invalid pin parsing");
            static_assert(parseGpio("D7").port == GpioPort::D, "Invalid port parsing");
            static_assert(parseGpio("D7").pin == 7, "Invalid port parsing");
            // static tests for parseConfigString
            static_assert(parseConfigString("OL").output == true, "Invalid input/output selection parsing");
            static_assert(parseConfigString("OL").level == false, "Invalid initial level parsing");
            static_assert(parseConfigString("I").output == false, "Invalid input/output selection parsing");
            static_assert(parseConfigString("I").level == false, "Invalid pull up selection parsing");
        }

        class Pin
        {
            public:
                explicit constexpr Pin(const char* const gpioStr)
                    : regs_{static_cast<AddressType>(parseGpio(gpioStr).port)}
                    , pin_{static_cast<AddressType>(parseGpio(gpioStr).pin)}
                { }

                void configure(const char* const configStr) const
                {
                    auto config = parseConfigString(configStr);
                    setMode(config.output);
                    setLevel(config.level);
                }

                bool read() const
                {
                    return regs_[GpioRegs::PIN](pin_);
                }

                void setLevel(const bool level) const
                {
                    regs_[GpioRegs::PORT].changeBit(pin_, level);
                }
            private:
                void setMode(const bool output) const
                {
                    regs_[GpioRegs::DDR].changeBit(pin_, output);
                }
            private:
                Mmio::Mmio<AddressType, uint8_t> regs_;
                const uint8_t pin_;
        };
    }
}

#endif //_AVRHW_GPIO_HPP