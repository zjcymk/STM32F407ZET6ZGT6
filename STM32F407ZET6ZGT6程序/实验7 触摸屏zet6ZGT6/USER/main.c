

/******************** 尚学科技 **************************
 * 实验平台：开拓者STM32开发板
 * 库版本  ：ST3.5.0
 * 作者    ：尚学科技团队 
 * 淘宝    ：http://shop102218275.taobao.com/
 * 本程序只供学习使用，未经作者许可，不得用于其它任何用途

**********************************************************************************/


#include "stm32f4xx.h"
#include "delay.h"
#include "text.h"
#include "lcd.h"
#include "touch.h"




int main(void)
 {	 
  POINT_COLOR=RED;
	BACK_COLOR=WHITE;
	delay_init(168);  //初始化延时函数
  LCD_Init();
	LCD_Clear(WHITE);
	TP_Init();				//触摸屏初始化
	Pen_data.Key_Sta=0;
  Load_TFT_surface();	  

  	while(1)
	{

		Read_TP(0); 		 
		if(Pen_data.Key_Sta)			//触摸屏被按下
		{	
				if(Pen_data.X0>210&&Pen_data.Y0<20)
				{
			  Load_TFT_surface();//清除
				}
				else if(Pen_data.X0>0&&Pen_data.Y0<20&&Pen_data.X0<30)
				{
						POINT_COLOR=BLUE;//设置字体为蓝色 
		    }
				else if(Pen_data.X0>30&&Pen_data.Y0<20&&Pen_data.X0<60)
				{
         	POINT_COLOR=RED;//设置字体为红色		
        }
				else if(Pen_data.X0>60&&Pen_data.Y0<20&&Pen_data.X0<90)
				{
         	POINT_COLOR=YELLOW;//设置字体为黄色
				}
				else if(Pen_data.X0>90&&Pen_data.Y0<20&&Pen_data.X0<120)
				{
         	POINT_COLOR=BLACK;//设置字体为黑色 
        }
				else if(Pen_data.X0>120&&Pen_data.Y0<20&&Pen_data.X0<150)
				{
         	POINT_COLOR=GREEN;//设置字体为绿色 
				
        }
				else if(Pen_data.X0>150&&Pen_data.Y0<20&&Pen_data.X0<180)
				{
         	POINT_COLOR=GRAY;//设置字体为灰色 
				
        }
				else if(Pen_data.X0>180&&Pen_data.Y0<20&&Pen_data.X0<210)
				{
         	POINT_COLOR=BROWN;//设置字体为棕色 
				
        }
				 else
				 {
	      Draw_Big_Circle(Pen_data.X0,Pen_data.Y0,POINT_COLOR);//画图	    
         }					 				
			}
		else delay_ms(10);	//没有按键按下的时候 	    

	}
}



