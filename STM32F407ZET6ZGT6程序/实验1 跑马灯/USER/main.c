

/******************** 尚学科技 **************************
 * 实验平台：开拓者STM32开发板
 * 库版本  ：ST3.5.0
 * 作者    ：尚学科技团队 
 * 淘宝    ：http://shop102218275.taobao.com/
 * 本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *版权所有，盗版必究。
**********************************************************************************/


#include "stm32f4xx.h"
#include "LED.H"


  
void delay(unsigned int count);




int main(void)
{
	LED_GPIO_Config();
	
while(1)
{

	LED1_ON;
	LED2_OFF;
	delay(0x7fffff);

	LED1_OFF;
	LED2_ON;
	delay(0x7fffff);
}
}



void delay(unsigned int count)
{
int i;
for(i=0;i<count;i++);
}


