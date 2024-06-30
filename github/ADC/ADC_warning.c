#include<lpc17xx.h>
#include "lcd_func.c"
int main()
{
unsigned int adc_value;
lcd_config();

LPC_SC->PCONP|=(1<<12);
LPC_SC->PCLKSEL0|=(1<<25)|(1<<24);
LPC_PINCON->PINSEL1|=(1<<18);
LPC_ADC->ADCR=(1<<2)|(4<<8)|(1<<16)|(1<<21);
while(1)
{
while(!(LPC_ADC->ADGDR&(1<<31)));

adc_value=(LPC_ADC->ADDR2&(0xFFF<<4));
adc_value=adc_value/13.6;
adc_value=(adc_value>>4);
if(adc_value>30)
{
lcd_str("WARNING");
lcd_cmd(0xC0);
delay(30);
lcd_num(adc_value);
lcd_cmd(0X01);
}
else
{
lcd_cmd(0xC0);
lcd_num(adc_value);
delay(100);
lcd_cmd(0x01);}
}
}