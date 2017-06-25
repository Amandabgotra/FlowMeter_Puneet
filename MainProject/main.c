#include <stdio.h>
#include <stdint.h>
#include "LPC214x.H"                       /* LPC214x definitions */
#include "lcd.h"
#include "adc.h"

uint8_t au8DataToDisplay[100]  = {0U,};

void Delay_ms(unsigned int u32Delay)
{
    volatile uint8_t u8Const = 0;
    while(u32Delay--)
    {
        u8Const = 100;
        while(u8Const--)
        {
            
        }
    }
}/*End of void Delay_ms(unsigned int u32Delay)*/

uint16_t Read_adc(void)
{
	unsigned short adc_value = 0;
  	unsigned char buf[16] = {0};
    
    adc_value = adc_read(ADC0, CHANNEL_3);	
    return(adc_value);
}

void main(void)
{
    uint32_t u32Timer =0 ;
    uint32_t u32SumReading = 0;
    uint16_t u16AvgReading = 0;
    uint16_t  u8SampleCount = 0;
    init_lcd();
    init_adc0();						// Initialize ADC
    lcd_clear();
    lcd_putstring(LINE1, "KUSHAL FlowMeter");
    while(1)
    {
        if(u8SampleCount < 256)
        {
            u32SumReading += Read_adc();
            u8SampleCount++;
            Delay_ms(100);
        }
        else
        {
            u8SampleCount = 0;
            u16AvgReading = u32SumReading >> 8;
            sprintf(au8DataToDisplay,"[%d]       ",u16AvgReading);
            lcd_putstring(LINE2,au8DataToDisplay);
            u16AvgReading = 0;
            u32SumReading = 0;
        }
    }
}