#define F_CPU 1000000UL // 1 MHz

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0xff;
    while (1)
    {
        PORTD = 0x01;
        _delay_ms(500);
        PORTD = 0x00;
        _delay_ms(500);
    }
}