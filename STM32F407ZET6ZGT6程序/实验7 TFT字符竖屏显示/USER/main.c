

/******************** ��ѧ�Ƽ� **************************
 * ʵ��ƽ̨��������STM32������
 * ��汾  ��ST3.5.0
 * ����    ����ѧ�Ƽ��Ŷ� 
 * �Ա�    ��http://shop102218275.taobao.com/
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 *��Ȩ���У�����ؾ���
**********************************************************************************/


#include "stm32f4xx.h"

#include "delay.h"
#include "text.h"
#include "lcd.h"

int main(void)
 {	 

	POINT_COLOR=RED;
	BACK_COLOR=WHITE;
  LCD_Init();
	LCD_Clear(WHITE);
	LCD_ShowString(30,50,"Mini STM32 ^_^",POINT_COLOR);	
	LCD_ShowString(30,70,"TFTLCD TEST",POINT_COLOR);	
	LCD_ShowString(30,90,"Pioneer",POINT_COLOR);
	LCD_ShowString(30,110,"2009/12/30",POINT_COLOR);	
	 
   while(1) 
	{		 
 
	} 
}
