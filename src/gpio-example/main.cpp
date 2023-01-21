#define F_CPU 1000000UL // 1 MHz

#include <util/delay.h>

#include <AvrHw/Gpio.hpp>

int main(void)
{
    constexpr Avr::Gpio::Pin pin{"D0"};
    pin.configure("OL");
    while (1)
    {
        pin.setLevel(true);
        _delay_ms(500);
        pin.setLevel(false);
        _delay_ms(500);
    }
}