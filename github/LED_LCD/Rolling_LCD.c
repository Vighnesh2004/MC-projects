#include<lpc17xx.h>
#define RS (1<<10)
//#define RW (1<<12)
#define EN (1<<11)
#define DATA (0xFF<<15)
void delay (unsigned int a);
void lcd_config(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_num(unsigned long long num);
void lcd_str(unsigned char *ptr);
int main(void)
{
lcd_config();
//lcd_data('A');
lcd_str("VIGHNESHWARA from SMVEC");
lcd_cmd(0x38);
lcd_cmd(0x0E);
lcd_cmd(0xC0);
lcd_num(9944316944);
}
void lcd_config(void)
{
LPC_GPIO0->FIODIR |=RS | EN | DATA ;	// to prevent overwriting of data
lcd_cmd(0x38);
lcd_cmd(0x0E);
lcd_cmd(0x01);
lcd_cmd(0x80);

}
void lcd_cmd(unsigned char cmd)
{
	LPC_GPIO0->FIOCLR = DATA;
	LPC_GPIO0->FIOSET = (cmd<<15);
	LPC_GPIO0->FIOCLR = RS;
	LPC_GPIO0->FIOSET = EN;
	delay(10);
	LPC_GPIO0->FIOCLR = EN;
}
void lcd_data(unsigned char data)
{
    LPC_GPIO0->FIOCLR = DATA;
	LPC_GPIO0->FIOSET = (data<<15);
	LPC_GPIO0->FIOSET = RS;
	LPC_GPIO0->FIOSET = EN;
	delay(10);
	LPC_GPIO0->FIOCLR = EN;
}
void lcd_str(unsigned char *ptr)
{
while(*ptr != '\0')
{
lcd_data(*ptr);
ptr++;
}
while(1)
{
lcd_cmd(0x1C);
delay(60);
}
}
void lcd_num(unsigned long long num)
{
if (num)
{
lcd_num(num/10);
lcd_data(num%10+0x30);
}
}
void delay (unsigned int a)
{
unsigned int j,k;
for(j=0;j<a;j++){
for(k=0;k<6000;k++);
}
}