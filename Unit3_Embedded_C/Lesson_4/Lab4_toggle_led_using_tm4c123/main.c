/*Lab4 toggle led with cortexm4
Eng.Hossam Bahaa
*/
#include "Platform_Types.h"

#define SYSCTL_BASE 0x400FE000
#define GPIOF_BASE  0x40025000

#define SYSCTL_RCGC2_R 	  *((vuint32_t*)(SYSCTL_BASE + 0x108))
#define GPIO_PORTF_DIR_R  *((vuint32_t*)(GPIOF_BASE + 0x400))
#define GPIO_PORTF_DEN_R  *((vuint32_t*)(GPIOF_BASE + 0x51c))
#define GPIO_PROTF_DATA_R *((vuint32_t*)(GPIOF_BASE + 0x3FC))


#define SET_SPECIFIC_BIT(reg,bit)   (reg |= (1<<bit))
#define RESET_SPECIFIC_BIT(reg,bit) (reg &= ~(1<<bit))


void delay(vuint32_t counter);

int main()
{
   SYSCTL_RCGC2_R = 0x20 ;
   delay(200);
   SET_SPECIFIC_BIT(GPIO_PORTF_DIR_R,3);
   SET_SPECIFIC_BIT(GPIO_PORTF_DEN_R,3);

   while(1)
   {
      SET_SPECIFIC_BIT(GPIO_PROTF_DATA_R,3);
      delay(200000);
      RESET_SPECIFIC_BIT(GPIO_PROTF_DATA_R,3);
      delay(200000);
   } 
	return 0;
}

void delay(vuint32_t counter)
{
	vuint32_t delay_counter ;
	for(delay_counter = 0 ; delay_counter<counter ; delay_counter++);
}