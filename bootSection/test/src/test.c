/*
 * test.c
 *
 * Created: 2014/3/25 23:01:53
 *  Author: ms2
 */ 


#include <avr/io.h>

#define  F_CPU 8000000
#include <util/delay.h>
# include <avr/interrupt.h>
# include <avr/boot.h>
# include <util/delay.h>
# include "uart.h"

#define BOOT_UART_BAUD_RATE 9600
#define XON                     17      
#define XOFF                    19       

int main(void)
{
	unsigned int c = 0;
	unsigned char temp,flag=1, p_mode=0 ;
	
	void (*start) (void) = 0x0000;
	
	DDRB |= (1<< PB1);

	PORTB |= (1 << PB1);	//LED on
	_delay_ms(1000);
	PORTB &= ~(1 << PB1);	//LED off
	_delay_ms(1000);

	
	char sregtemp = SREG;
	cli();
	temp = MCUCR;
	MCUCR = temp | (1<<IVCE);
	MCUCR = temp | (1<<IVSEL);
	SREG = sregtemp;
		
	uart_init( UART_BAUD_SELECT(BOOT_UART_BAUD_RATE,F_CPU) );
	sei();
		
	uart_puts("hello bootloader\n\r");
	_delay_ms(1000);
		
	do
	{
		c = uart_getc();
		if( !(c & UART_NO_DATA) )
		{
			switch((unsigned char)c)
			{
				case 'q':
				flag=0;
				uart_puts("hello again bootloader!\n\r");
				break;
				default:
				uart_puts("This is the sent ");
				uart_putc((unsigned char)c);
				uart_puts("\n\r");
				break;
			}
		}
	}
	while(flag);
		
	uart_puts("Jump to address 0x0000!\n\r");
	_delay_ms(1000);
		
	cli();
	temp = MCUCR;
	MCUCR = temp | (1<<IVCE);
	MCUCR = temp & ~(1<<IVSEL);
		
	PORTB |= (1 << PB1);	//LED on
	_delay_ms(1000);
	PORTB &= ~(1 << PB1);	//LED off
	_delay_ms(1000);
		
	start();
		
	return 0;
	 
}