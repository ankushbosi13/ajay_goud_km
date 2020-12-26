//program for led initilization

#include  "km_tm4c123gh6pm.h"
#include "KM_SysTickTimer.h"
void KM_SysTickTimer_Init(void);
void KM_delay_ms(unsigned long );
void KM_delay_us(unsigned long );
void KM_PLL_Init(void);
void enable();
void GPIO_PORT_AD_Init (void)
{
	SYSCTL_RCGCGPIO_R |= 0x09;
	while( ! (SYSCTL_PRGPIO_R) & 0x09)
	{
		;
	}

GPIO_PORTA_PCTL_R &=~ (0x000FFFFF);
GPIO_PORTD_PCTL_R &=~ (0xFFFF0000);  
GPIO_PORTA_DIR_R  |= (0xE0);
GPIO_PORTD_DIR_R  |= (0x0F);
GPIO_PORTA_DEN_R  |= (0xE0);
GPIO_PORTD_DEN_R  |= (0x0F);
}
void pulse(int data)
{
	KM_delay_ms(data);
	enable();
}


void enable()
{
	GPIO_PORTA_DATA_R |=(0xE0); // set enable 
	KM_delay_ms(10);
	GPIO_PORTA_DATA_R &=~(0xE0); //clear enable 
}
void higher_nibble (char data)
{
	GPIO_PORTD_DATA_R &=~(0xFFFFFFF0); // CLEARING THE LAST 4 BITS OF D PORT
	GPIO_PORTD_DATA_R = (data>>4); // SHIFTING 4 BITS OF MSB TO LSB
	enable();
}

void lower_nibble (char data)
{
	GPIO_PORTD_DATA_R =  (data);
	enable();
}
void lcd_cmd(char data)
{
	enable();
	higher_nibble (data);
	lower_nibble  (data);
	
}

void lcd_init(void)
{
	enable();
	pulse(18);
	GPIO_PORTD_DATA_R |= (0x3);
	pulse(5);
	GPIO_PORTD_DATA_R |= (0x3);
	KM_delay_us(101);
	enable();
	GPIO_PORTD_DATA_R |= (0x3);
	enable();
	GPIO_PORTD_DATA_R |= (0x02);
	enable();
	GPIO_PORTD_DATA_R |= (0x28);
	enable();
	GPIO_PORTD_DATA_R |= (0x08);
	enable();
	GPIO_PORTD_DATA_R |= (0x01);
	enable();
	GPIO_PORTD_DATA_R |= (0x06);
}
void lcd_data (char  data )
{
	enable();
	higher_nibble (data);
	lower_nibble  (data);
}
void lcd_string (char s[])
{
	int i;
	for(i=0;s[i];i++)
	{
		lcd_data(s[i]); //calling lcd data function 
	}
}

int main()
{
	KM_PLL_Init();
	KM_SysTickTimer_Init();
	GPIO_PORT_AD_Init();
	lcd_init();
	lcd_cmd(0x01);
	lcd_cmd(0x0E);
	lcd_cmd(0x06);
	lcd_cmd(0x86);//
	lcd_data('a'); 
	lcd_string("kernel");
}
