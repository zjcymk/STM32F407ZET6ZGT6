

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
#include "timer.h"





int main(void)
{

		/* led 端口配置 */ 
	LED_GPIO_Config();	
	/* TIM2 定时配置 */
	TIME_NVIC_Configuration();
  TIME_Configuration();
while(1)
{


}
}






