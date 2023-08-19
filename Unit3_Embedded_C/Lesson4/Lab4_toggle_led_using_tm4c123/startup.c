
// startup.c
//Eng.Hossam Elmaghraby

#include <stdint.h>
extern int main(void);

void Reset_Handler();

void Default_Handler()
{
	Reset_Handler();
}

void NMI_Handler() __attribute__((weak, alias ("Default_Handler")));;
void H_Fault_Handler()__attribute__((weak, alias ("Default_Handler")));;

static uint32_t _stack_top[256];

  void (*const g_p_to_fn_vectors[])() __attribute__((section(".vectors"))) =
  {
  	 (void(*)())&(_stack_top[256]),
  	  &Reset_Handler,
	  &NMI_Handler,
	  &H_Fault_Handler,
  };

extern unsigned int _E_text ;
extern unsigned int _S_data ;
extern unsigned int _E_data ;
extern unsigned int _S_bss ;
extern unsigned int _E_bss ;
void Reset_Handler()
{
	// copy data from ROM to RAM
	unsigned int Data_size=(unsigned char*)&_E_data - (unsigned char*)&_S_data ;
	unsigned char* p_src = (unsigned char*)&_E_text ;
	unsigned char* p_dst = (unsigned char*)&_S_data ;
	for (int i = 0; i < Data_size; ++i)
	{
		*((unsigned char*)p_dst++)=*((unsigned char*)p_src++);
	}

	//init the .bss with zero
	unsigned int bss_size =(unsigned char*)&_E_bss - (unsigned char*)& _S_bss ;
	p_dst =(unsigned char*)&_S_bss ;
	for (int i = 0; i < bss_size; ++i)
	{
		*((unsigned char*)p_dst++)=(unsigned char)0 ;
	}
	// jump to main
   main();
}