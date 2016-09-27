#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

void led();
uint8_t led_v = 0x80;
uint8_t state = 1;
uint8_t digit = 0;
uint8_t tmb[4]={4,3,2,1,8,7,6,5};
uint8_t offset=0;

int main()
{


    TCCR0 = (1<<CS02)| (1<<CS00);
    TIMSK = (1<<TOIE0);
    sei();

    DDRD = 0xF0;
    DDRB = 0xF0;
    DDRA = 0xFF;
    DDRG = 0x00;

    while(1)
    {
        if(PING == 1){
            offset++;
            if (offset == 8)offset=0;
            while(PING);
            _delay_ms(200);
        }
    }
    return 0;
}

ISR(TIMER0_OVF_vect)
{
    digit = (digit+1)%4;
    PORTA = (1<<7) + (digit<<4) + tmb[(digit+offset)%8];
}

