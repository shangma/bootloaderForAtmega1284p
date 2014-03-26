/*
 * test.c
 *
 * Created: 2014/3/25 23:01:53
 *  Author: ms2
 */ 


#include <avr/io.h>

#define  F_CPU 1000000
#include <util/delay.h>
# include <avr/interrupt.h>
# include <avr/boot.h>
# include <util/delay.h>
# include "uart.h"

int main(void)
{
	DDRB |= (1<< PB1);

    while(1)
    {
        //TODO:: Please write your application code 
		PORTB &= ~(1 << PB1);	//LED off
		_delay_ms(1000);
		PORTB |= (1 << PB1);	//LED on
		_delay_ms(1000);
    }
}