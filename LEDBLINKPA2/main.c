//program for led blinking  FROM PA2
	#define SYSCTL_RCGC_GPIO_R (*(unsigned int *) 0x400FE608)
	#define SYSCTL_PR_GPIO_R (*(unsigned int *) 0x400FEA08)
	#define PCTL_R (*(unsigned int *) 0x4000452C)
	#define DIR_R (*(unsigned int *) 0x40004400)
	#define DEN_R (*(unsigned int *) 0x4000451C)
	#define DATA_R (*(unsigned int *) 0x400043FC)
void GPIO_PORTF_INIT (void)  // portf initilization PF1 set to output diretion
{
	SYSCTL_RCGC_GPIO_R |=(0x1<<0); // PORTA CLOCK IS ENABLED
	
 	while(!(SYSCTL_PR_GPIO_R) & 0x01)  //waiting for pr to get ready 
	{
			;
	}		
	PCTL_R &= (0xFFFFF0FF); //PORT A2 BIT ARE SET TO GPIO FUNCTIONALITY <-- this is of PCTL register
	DIR_R |= (0x1<<2); //PORT F1 DIRECTION IS SET TO OUTPUT
	DEN_R |= (0x1<<2); //PORT F1 DIGITALLY ENABLED
}

void delay() //delay function
{
	int temp=1500;
	while(temp>0)
	{
		temp--;
	}
}
int main()
{
	GPIO_PORTF_INIT();
	
while(1)
{
	DATA_R |=(0x1<<2); //RED LED ON
	delay(); //100MS DELAY
	DATA_R &=~(0X1<<2); // RED LED OFF
	delay();//100ms DELAY 
}
return 0;
}

