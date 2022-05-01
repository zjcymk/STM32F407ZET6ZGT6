

/******************** 尚学科技 **************************
 * 实验平台：开拓者STM32开发板
 * 库版本  ：ST3.5.0
 * 作者    ：尚学科技团队 
 * 淘宝    ：http://shop102218275.taobao.com/
 * 本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *版权所有，盗版必究。
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






