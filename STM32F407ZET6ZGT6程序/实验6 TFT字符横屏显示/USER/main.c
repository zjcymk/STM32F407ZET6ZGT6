

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
