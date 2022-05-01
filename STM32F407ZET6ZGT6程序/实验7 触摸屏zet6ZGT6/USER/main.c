

/******************** ��ѧ�Ƽ� **************************
 * ʵ��ƽ̨��������STM32������
 * ��汾  ��ST3.5.0
 * ����    ����ѧ�Ƽ��Ŷ� 
 * �Ա�    ��http://shop102218275.taobao.com/
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

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
	delay_init(168);  //��ʼ����ʱ����
  LCD_Init();
	LCD_Clear(WHITE);
	TP_Init();				//��������ʼ��
	Pen_data.Key_Sta=0;
  Load_TFT_surface();	  

  	while(1)
	{

		Read_TP(0); 		 
		if(Pen_data.Key_Sta)			//������������
		{	
				if(Pen_data.X0>210&&Pen_data.Y0<20)
				{
			  Load_TFT_surface();//���
				}
				else if(Pen_data.X0>0&&Pen_data.Y0<20&&Pen_data.X0<30)
				{
						POINT_COLOR=BLUE;//��������Ϊ��ɫ 
		    }
				else if(Pen_data.X0>30&&Pen_data.Y0<20&&Pen_data.X0<60)
				{
         	POINT_COLOR=RED;//��������Ϊ��ɫ		
        }
				else if(Pen_data.X0>60&&Pen_data.Y0<20&&Pen_data.X0<90)
				{
         	POINT_COLOR=YELLOW;//��������Ϊ��ɫ
				}
				else if(Pen_data.X0>90&&Pen_data.Y0<20&&Pen_data.X0<120)
				{
         	POINT_COLOR=BLACK;//��������Ϊ��ɫ 
        }
				else if(Pen_data.X0>120&&Pen_data.Y0<20&&Pen_data.X0<150)
				{
         	POINT_COLOR=GREEN;//��������Ϊ��ɫ 
				
        }
				else if(Pen_data.X0>150&&Pen_data.Y0<20&&Pen_data.X0<180)
				{
         	POINT_COLOR=GRAY;//��������Ϊ��ɫ 
				
        }
				else if(Pen_data.X0>180&&Pen_data.Y0<20&&Pen_data.X0<210)
				{
         	POINT_COLOR=BROWN;//��������Ϊ��ɫ 
				
        }
				 else
				 {
	      Draw_Big_Circle(Pen_data.X0,Pen_data.Y0,POINT_COLOR);//��ͼ	    
         }					 				
			}
		else delay_ms(10);	//û�а������µ�ʱ�� 	    

	}
}



