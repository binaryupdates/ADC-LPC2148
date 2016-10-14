/************************************************************/
/* PROJECT NAME: ADC (Analog to Digital Converter)	        */
/* Device:       LPC2148                					*/
/* Filename:     main.c                                   	*/
/* Language:     C                      	                */
/* Compiler:     Keil ARM				            		*/
/* For more detail visit www.binaryupdates.com		      	*/
/************************************************************/

#include <lpc214x.h>
#include "serial.h"
#include <stdio.h>

char String[]="Wel-Come to BINARYUPDATES.COM, ADC and UART Configured @LPC2148 \n\r Serial Communication @ 9600 baudrate, 8 bits, no Parity, 1 Stop bit\n\r\n";
char Newline[]="\n\r\n";

char adcreading[16] ;

void ADC_Init (void)
{
	PINSEL1 = 0x01000000 ;							// P0.28, AD0.1
}

unsigned int ADC_GetAdcReading()
{
	unsigned int adcdata;
	AD0CR = 0x01200302 ;								// Select AD0.1, Select clock for ADC, Start of conversion
	
	while(!((adcdata = AD0GDR) & 0x80000000))		// Check end of conversion (Done bit) and read result
	{
	}
	return((adcdata >> 6) & 0x3ff) ;				// Return 10 bit result
}

int main(void)
{ 
	unsigned int delay, adc;
	
	initClocks(); // Set CCLK=60Mhz and PCLK=60Mhz 
	initUART0();
	ADC_Init() ;
	
	Send_String(String); 
	
	while(1) 
	{ 
		adc = ADC_GetAdcReading();	
		sprintf(adcreading,"ADC0 CH1= %u",adc);  // read data in decimal format
		//sprintf(adcreading,"ADC0 CH1= 0x%03X",adc); // read data in hexx format
		Send_String(adcreading);
		Send_String(Newline); 
		for(delay=0; delay<10000000; delay++); // delay
	}
}

