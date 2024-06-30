#include<lpc17xx.h>
#include "lcd_func.c"

#define ROWS (0x0F<<4)
#define COLS (0x0F<<0)

#define PASSWORD_LENGTH 4
const unsigned int correct_password[PASSWORD_LENGTH] = {1, 2, 3, 4}; // Example password, you can change this
unsigned int entered_password[PASSWORD_LENGTH] = {0}; // Initialize entered password
    unsigned int pass_index = 0; // Password index
	unsigned int i;
void row_scan(void);
void col1_scan(void);
void col2_scan(void);
void col3_scan(void);
void col4_scan(void);

int main() {
    
    lcd_config();
	lcd_str("WELCOME");
	delay(100);
	lcd_cmd(0x01);
    lcd_str("Door locked");
    delay(100);
    lcd_cmd(0x01);
    lcd_str("Enter pass:");
    lcd_cmd(0xC0);

    while(1) {
        row_scan();
        // Check if the entered password matches the correct password
        if(pass_index == PASSWORD_LENGTH) {
            unsigned int correct = 1;
            for( i = 0; i < PASSWORD_LENGTH; i++) {
                if(entered_password[i] != correct_password[i]) {
                    correct = 0;
                    break;
                }
            }
            if(correct) {
                lcd_cmd(0x01);
                lcd_cmd(0x80);
                lcd_str("Door unlocked");
                break; // Exit while loop and unlock the door
            } else {
                // Clear entered password and reset password index
                for(i = 0; i < PASSWORD_LENGTH; i++) {
                    entered_password[i] = 0;
                }  
                pass_index = 0;
                lcd_cmd(0x01);
                lcd_cmd(0x80);
                lcd_str("Incorrect pass");
                delay(2000); // Delay for 2 seconds
                lcd_cmd(0x01);
                lcd_str("Enter pass:");
                lcd_cmd(0xC0);
            }
        }
    }
}

void row_scan(void)
{
	unsigned int val;
	LPC_GPIO2->FIODIR|=COLS;	//configure COLS as output
	LPC_GPIO2->FIODIR&=~ROWS;	//configure ROWS as input port

	val=LPC_GPIO2->FIOPIN&ROWS;	 //if switch is pressed or not
	val=val>>4;
	switch(val)
	{
		case 0X0E:
			col1_scan();
			delay(50);
			break;
		case 0X0D:
			col2_scan();
			delay(50);
			break;
		case 0X0B:
			col3_scan();
			delay(50);
			break;
		case 0X07:
			col4_scan();
			delay(50);
			break;
		default:
			break;

	}	
}

void col1_scan(void)
{
	unsigned int val;
	LPC_GPIO2->FIODIR&=~COLS;	//configure COLS as output
	LPC_GPIO2->FIODIR|=ROWS;	//configure ROWS as input port

	val=LPC_GPIO2->FIOPIN&COLS;	 //if switch is pressed or not
	val=val>>0;
	switch(val)
	{
		case 0X0E:
			lcd_str("0");
			entered_password[pass_index++] = 0;
			delay(50);
			break;
		case 0X0D:
			lcd_str("1");
			entered_password[pass_index++] = 1;
			delay(50);
			break;
		case 0X0B:
			lcd_str("2");
			entered_password[pass_index++] = 2;
			delay(50);
			break;
		case 0X07:
			lcd_str("3");
			entered_password[pass_index++] = 3;
			delay(50);
			break;
		default:
			lcd_cmd(0X01);
	}
}
void col2_scan(void)
{
	unsigned int val;
	LPC_GPIO2->FIODIR&=~COLS;	//configure COLS as output
	LPC_GPIO2->FIODIR|=ROWS;	//configure ROWS as input port
																					    
	val=LPC_GPIO2->FIOPIN&COLS;	 //if switch is pressed or not
	val=val>>0;
	switch(val)
	{
		case 0X0E:
			lcd_str("4");
			entered_password[pass_index++] = 4;
			delay(50);
			break;
		case 0X0D:
			lcd_str("5");
			entered_password[pass_index++] = 5;
			delay(50);
			break;
		case 0X0B:
			lcd_str("6");
			entered_password[pass_index++] = 6;
			delay(50);
			break;
		case 0X07:
			lcd_str("7");
			entered_password[pass_index++] = 7;
			delay(50);
			break;
		default:
			lcd_cmd(0X01);
	}
}
void col3_scan(void)
{
	unsigned int val;
	LPC_GPIO2->FIODIR&=~COLS;	//configure COLS as output
	LPC_GPIO2->FIODIR|=ROWS;	//configure ROWS as input port

	val=LPC_GPIO2->FIOPIN&COLS;	 //if switch is pressed or not
	val=val>>0;
	switch(val)
	{
		case 0X0E:
			lcd_str("8");
			entered_password[pass_index++] = 8;
			delay(50);
			break;
		case 0X0D:
			lcd_str("9");
			entered_password[pass_index++] = 9;
			delay(50);
			break;
		case 0X0B:
			lcd_str("A");
			entered_password[pass_index++] = 10; // Assuming A is represented as 10
			delay(50);
			break;
		case 0X07:
			lcd_str("B");
			entered_password[pass_index++] = 11; // Assuming B is represented as 11
			delay(50);
			break;
		default:
			lcd_cmd(0X01);
	}
}
void col4_scan(void)
{
	unsigned int val;
	LPC_GPIO2->FIODIR&=~COLS;	//configure COLS as output
	LPC_GPIO2->FIODIR|=ROWS;	//configure ROWS as input port

	val=LPC_GPIO2->FIOPIN&COLS;	 //if switch is pressed or not
	val=val>>0;
	switch(val)
	{
		case 0X0E:
			lcd_str("C");
			entered_password[pass_index++] = 12; // Assuming C is represented as 12
			delay(50);
			break;
		case 0X0D:
			lcd_str("D");
			entered_password[pass_index++] = 13; // Assuming D is represented as 13
			delay(50);
			break;
		case 0X0B:
			lcd_str("E");
			entered_password[pass_index++] = 14; // Assuming E is represented as 14
			delay(50);
			break;
		case 0X07:
			lcd_str("F");
			entered_password[pass_index++] = 15; // Assuming F is represented as 15
			delay(50);
			break;
		default:
			lcd_cmd(0X01);
	}
}

