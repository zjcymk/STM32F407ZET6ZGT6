

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

#include "lcd.h"

int main(void)
 {	 


  LCD_Init();
   while(1) 
	{		 
	LCD_Clear(WHITE);
				Delay(0x5fffff);	 
			LCD_Clear(BLACK);
			Delay(0xfffff);	 
			LCD_Clear(BLUE);
			Delay(0x5fffff);	 
			LCD_Clear(RED);
				Delay(0x5fffff);	 
			LCD_Clear(MAGENTA);
			Delay(0x5fffff);	 
			LCD_Clear(GREEN);
			Delay(0x5fffff);	 
			LCD_Clear(CYAN);
				Delay(0x5fffff);	 
    LCD_Clear(YELLOW);
				Delay(0x5fffff);	 
		LCD_Clear(BRRED);
			Delay(0x5fffff);	 
		LCD_Clear(GRAY);
				Delay(0x5fffff);	 
			LCD_Clear(LGRAY);
				Delay(0x5fffff);	 
			LCD_Clear(BROWN);
		Delay(0x5fffff);	 
	} 
}






