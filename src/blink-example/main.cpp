#define F_CPU 8000000UL // 8 MHz

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0xff;
    while (1)
    {
        PORTD = 0x01;
        _delay_ms(500);
        PORTD = 0x02;
        _delay_ms(500);
        PORTD = 0x03;
        _delay_ms(500);
        PORTD = 0x00;
        _delay_ms(500);
    }
}