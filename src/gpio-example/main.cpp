#define F_CPU 1000000UL // 1 MHz

#include <avr/io.h>
#include <util/delay.h>

#include <AvrHw/Gpio.hpp>

int main(void)
{
    constexpr Avr::Gpio::Pin led{"D0"};
    led.configure("OH");
    while (1)
    {
        led.write(true);
        _delay_ms(500);
        led.write(false);
        _delay_ms(500);
    }
}