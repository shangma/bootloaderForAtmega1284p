/*
 * applicationCode.c
 *
 * Created: 2014/3/26 5:22:45
 *  Author: ms2
 */ 

#define  F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "uart.h"

#define UART_BAUD_RATE	9600

int main(void)
{
    unsigned int c;
    void (*bootloader)(void) = 0xFC00; 
    
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE , F_CPU));
    sei() ;
    
    uart_puts_P("\n\rhere is the application program ...\n\r");
    
    for(;;)
    {
	    c = uart_getc();
	    if(!(c & UART_NO_DATA))
	    {
		    switch((unsigned char)c)
		    {
			    case 'b':
					uart_puts("\n\rHi bootloader...\r\n");
					_delay_ms(1000);
					bootloader();
					break;
			    default:
					uart_puts("\n\rSee what we got: ");
					uart_putc((unsigned char)c);
					break;
		    }
	    }
    }
    return 0;
}