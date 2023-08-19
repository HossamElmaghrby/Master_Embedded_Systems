/*Lab4 toggle led with cortexm4
Eng.Hossam Bahaa
*/
#define SYSCTL_RGC2_R        (*((volatile unsigned long * )0x400FE108))
#define GPIO_PORTF_DIR_R     (*((volatile unsigned long * )0x40025400))
#define GPIO_PORTF_DEN_R     (*((volatile unsigned long * )0x4002551C))
#define GPIO_PORTF_DATA_R    (*((volatile unsigned long * )0x400253FC))

int main(void)
{
	volatile unsigned long delay_c;
	SYSCTL_RGC2_R = 0x20;
	for(delay_c=0 ; delay_c < 200 ; delay_c++);
	GPIO_PORTF_DIR_R |= 1<<3; // set portf pin3 as output pin
	GPIO_PORTF_DEN_R |= 1<<3; // Enable GPIO
	while(1)
	{
		GPIO_PORTF_DATA_R |= 1<<3;
		for(delay_c=0 ; delay_c < 200000 ; delay_c++);
		GPIO_PORTF_DATA_R &= ~(1<<3);
		for(delay_c=0 ; delay_c < 200000 ; delay_c++);
	}
	return 0;
}