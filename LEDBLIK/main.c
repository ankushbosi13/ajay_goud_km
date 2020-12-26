//program for led blinking 

	#define SYSCTL_RCGC_GPIO_R (*(unsigned int *) 0x400FE608)
	#define SYSCTL_PR_GPIO_R (*(unsigned int *) 0x400FEA08)
	#define PCTL (*(unsigned int *) 0x4002552C)
	#define DIR (*(unsigned int *) 0x40025400)
	#define DEN (*(unsigned int *) 0x4002551C)
	#define DATA (*(unsigned int *) 0x400253FC)
void GPIO_PORTF_INIT (void)  // portf initilization PF1 set to output diretion
{
	SYSCTL_RCGC_GPIO_R |=(0x1<<5); // PORTF CLOCK IS ENABLED
	
 	while(!(SYSCTL_PR_GPIO_R))  //waiting for pr to get ready 
	{
			;
	}		
	PCTL &= (0xFFFFFF0F); //PORT F1 BIT ARE SET TO GPIO FUNCTIONALITY <-- this is of PCTL register
	DIR |= (0x1<<1); //PORT F1 DIRECTION IS SET TO OUTPUT
	DEN |= (0x1<<1); //PORT F1 DIGITALLY ENABLED
}

void delay() //delay function
{
	int temp=150000;
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
	DATA |=(0x1<<1); //RED LED ON
	delay(); //100MS DELAY
	DATA &=~(0X1<<1); // RED LED OFF
	delay();//100ms DELAY 
}
return 0;
}

