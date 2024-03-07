/*
 * Atmega32_Drivers.c
 *
 * Created: 12/14/2023 8:26:01 AM
 * Author : Elmag
 */ 

#include "LCD/lcd.h"
#include "Atmega32_SPI_Driver.h"

//#define Master_Mode
#define  Slave_Mode
int main(void)
{
	 uint8 count = 0 ;
	 
	 uint8 data  ,RXdata;
	LCD_init() ;
	
	SPI_Config SPI_cfg ;
	
	SPI_cfg.Baud_Rate = SPI_Baud_Rate_Double_Speed_8 ;
	SPI_cfg.CLK_Phase = SPI_CLK_Phase_second_edge ;
	SPI_cfg.CLK_Polarity =SPI_CLK_Polarity_HIGH_idle ;
	SPI_cfg.CLK_Speed = SPI_CLK_Speed_Double ;
	SPI_cfg.Data_Order = SPI_Data_Order_MSB_First ;
#ifdef Master_Mode
      SPI_cfg.Device_Mode = SPI_Mode_Master ;
	  SPI_cfg.IRQ_Enable = SPI_IR_Enable_NONE ;
	  SPI_cfg.P_IRQ_CallBack = NULL ;
#endif	

#ifdef 	Slave_Mode
      SPI_cfg.Device_Mode = SPI_Mode_slave ;
      SPI_cfg.IRQ_Enable = SPI_IR_Enable_NONE ;
      SPI_cfg.P_IRQ_CallBack = NULL ;
#endif
    MCAL_SPI_Init(SPI1 , &SPI_cfg);
	MCAL_SPI_GPIO_Set_Pins(SPI1);
	
#ifdef Master_Mode
    LCD_write_string("Master");
	data ='A';
#endif

#ifdef Slave_Mode
    LCD_write_string("Slave");
	RXdata ='a';
#endif	

  while(1)
  {
	  
	  #ifdef Master_Mode
	   if(data == 'Z'+1)
	   data ='A';
	   MCAL_SPI_Send_Data(SPI1 , &data, SPI_enable);
	   MCAL_SPI_Recieve_Data(SPI1 , &RXdata, SPI_enable);
	   Cursor_pos(1,0);
	  LCD_write(RXdata);	   
	   _delay_ms(1000);
	   data++;
	  #endif
	  
	  #ifdef Slave_Mode
	  if(RXdata == 'z'+1)
	  RXdata ='a';
	  MCAL_SPI_Send_Data(SPI1 , &RXdata, SPI_enable);
	  MCAL_SPI_Recieve_Data(SPI1 , &data , SPI_enable);
	  Cursor_pos(1,0);
	  LCD_write(data);
	  _delay_ms(200);
	  RXdata++;
	  #endif	
	    
	  Cursor_pos(0,10);
	  if(count == 10)
       count = 0;
	   
	   LCD_display_number(count);
	   count++ ;
  }
}
