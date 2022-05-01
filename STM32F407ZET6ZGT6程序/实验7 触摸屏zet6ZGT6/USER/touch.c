/******************** ��ѧ�Ƽ� **************************
 * ʵ��ƽ̨��������STM32������
 * ��汾  ��ST3.5.0
 * ����    ����ѧ�Ƽ��Ŷ� 
 * �Ա�    ��http://shop102218275.taobao.com/
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

**********************************************************************************/

#include "stdlib.h"
#include "math.h"
#include "lcd.h"
#include "delay.h"
#include "touch.h"
#include "stm32f4xx.h" 


Pen_Parameters Pen_data;//�����ʵ��
Touch_Adjust_Parameters Touch_date;//����������У׼

//X,Y��������Ļ��ͬ
u8 CMD_CHX=0XD0;
u8 CMD_CHY=0X90;
//X,Y��������Ļ�෴
// u8 CMD_CHX=0X90;
// u8 CMD_CHY=0XD0;
u8* TP_REMIND_MSG_TBL="Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.";
u8* TP_REMIND_MSG_TBL1="Touch screen calibration failure,Please re calibrate the touch screen.";

signed short Coordinate_xy[4][2];//У׼ʱ�����껺��ֵ


Coordinate DisplaySample[4] =   
{
    { 20,  20 },
    { 220, 20},
    { 20, 300},
    { 220, 300}
};


				
//Ĭ��Ϊtouchtype=0������.
u8 CMD_RDX=0XD0;
u8 CMD_RDY=0X90;
 	 			    					   
//SPIд����
//������ICд��1byte����    
//num:Ҫд�������
void TP_Write_Byte(u8 num)    
{  
	u8 count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)TDIN_High;  
		else TDIN_Low;   
		num<<=1;    
		TCLK_Low; 
		delay_us(1);
		TCLK_High;		//��������Ч	        
	}		 			    
} 		 
//SPI������ 
//�Ӵ�����IC��ȡadcֵ
//CMD:ָ��
//����ֵ:����������	   
u16 TP_Read_AD(u8 CMD)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0; 
	TCLK_Low;		//������ʱ�� 	 
	TDIN_Low; 	//����������
	TCS_Low;		//ѡ�д�����IC
	TP_Write_Byte(CMD);//����������
	delay_us(6);//ADS7846��ת��ʱ���Ϊ6us
	TCLK_Low; 	     	    
	delay_us(1);    	   
	TCLK_High;	//��1��ʱ�ӣ����BUSY
	delay_us(1);    
	TCLK_Low; 	     	    
	for(count=0;count<16;count++)//����16λ����,ֻ�и�12λ��Ч 
	{ 				  
		Num<<=1; 	 
		TCLK_Low;	//�½�����Ч  	    	   
	delay_us(1);    
 		TCLK_High;
 		if(DOUT)Num++; 		 
	}  	
	Num>>=4;   	//ֻ�и�12λ��Ч.
	TCS_High;		//�ͷ�Ƭѡ	 
	return(Num);   
}
//��ȡһ������ֵ(x����y)
//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ 
//xy:ָ�CMD_RDX/CMD_RDY��
//����ֵ:����������
#define READ_TIMES 5 	//��ȡ����
#define LOST_VAL 1	  	//����ֵ
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 
//��ȡx,y����
//��Сֵ��������100.
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);	  												   
	//if(xtemp<100||ytemp<100)return 0;//����ʧ��
	*x=xtemp;
	*y=ytemp;
	return 1;//�����ɹ�
}
//����2�ζ�ȡ������IC,�������ε�ƫ��ܳ���
//ERR_RANGE,��������,����Ϊ������ȷ,�����������.	   
//�ú����ܴ�����׼ȷ��
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
#define ERR_RANGE 50 //��Χ 
u8 TP_Read_XY2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=TP_Read_XY(&x1,&y1);   
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-50��
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
}  
	  
//��������ɨ��
//tp:0,��Ļ����;1,��������(У׼�����ⳡ����)
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
u8 Read_TP(u8 tp)
{			   
	if(PEN==0)//�а�������
	{
if(tp)TP_Read_XY2(&Pen_data.X,&Pen_data.Y);//��ȡ��������
else if(TP_Read_XY2(&Pen_data.X,&Pen_data.Y))//��ȡ��Ļ����
		{
	
		Pen_data.X0=Touch_date.xfac*(Pen_data.X)+Touch_date.xoff;
		Pen_data.Y0=Touch_date.yfac*(Pen_data.Y)+Touch_date.yoff;  
	 	} 
		if((Pen_data.Key_Sta&Key_Down)==0)//֮ǰû�б�����
		{		 
			Pen_data.Key_Sta=Key_Down|TP_Key_Down;
 	   			 
		}			   
	}
	
	else
	{
		if(Pen_data.Key_Sta&Key_Down)//֮ǰ�Ǳ����µ�
		{
    Pen_data.Key_Sta=~(1<<7);//��ǰ����ɿ�	
		}   
	}
	return Pen_data.Key_Sta;//���ص�ǰ�Ĵ���״̬
}	  

//////////////////////////////////////////////////
//��LCD�����йصĺ���  
//��һ��������
//����У׼�õ�
void Draw_Touch_Coordinate(u8 x,u16 y,u16 Color)
{
	LCD_DrawLine(x-12,y,x+13,y,Color);//����
	LCD_DrawLine(x,y-12,x,y+13,Color);//����
	LCD_DrawPoint(x+1,y+1,Color);
	LCD_DrawPoint(x-1,y+1,Color);
	LCD_DrawPoint(x+1,y-1,Color);
	LCD_DrawPoint(x-1,y-1,Color);
	Draw_Circle(x,y,6,Color);//������Ȧ
}	  
//��һ�����
//2*2�ĵ�			   
void Draw_Big_Circle(u8 x,u16 y,u16 Color)
{	    
	LCD_DrawPoint(x,y,Color);//���ĵ� 
	LCD_DrawPoint(x+1,y,Color);
	LCD_DrawPoint(x,y+1,Color);
	LCD_DrawPoint(x+1,y+1,Color);	 	  	
}
								    
void Load_TFT_surface(void)
{
	LCD_Clear(WHITE);//����   
	LCD_Fill(0,0,30,20,BLUE);
	LCD_Fill(30,0,60,20,RED);
	LCD_Fill(60,0,90,20,YELLOW);
	LCD_Fill(90,0,120,20,BLACK);
	LCD_Fill(120,0,150,20,GREEN);
	LCD_Fill(150,0,180,20,GRAY);
	LCD_Fill(180,0,210,20,BROWN);
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(216,0,"CLR",POINT_COLOR);//��ʾ��������
  //POINT_COLOR=RED;//���û�����ɫ 
}

//���������������
u16 Calculation_distance(signed short *point1,signed short *point2)
{
  u32 tem1,tem2;
	tem1=abs(point1[0]-point2[0]);//x1-x2
	tem2=abs(point1[1]-point2[1]);//y1-y2
  return sqrt(tem1*tem1+tem2*tem2);//�õ��������ľ���
}

///������У׼������ˮƽ����ֱ���Խ������
#define Calibration_Error 3       
u8 touch_Calibration_Calculation(void)
{

	u16 d1,d2;
  float fac; 	
	//ˮƽ�������
						d1=Calculation_distance(Coordinate_xy[0],Coordinate_xy[1]);
						d2=Calculation_distance(Coordinate_xy[2],Coordinate_xy[3]);
					  if((d1+d2)!=0)
						{
            fac=abs(d1-d2)*100/(d1+d2);
            }
						if((fac>Calibration_Error)||d1==0||d2==0)
            return 0;
///��ֱ�߾���
					d1=Calculation_distance(Coordinate_xy[0],Coordinate_xy[2]);
					d2=Calculation_distance(Coordinate_xy[1],Coordinate_xy[3]);
				  if((d1+d2)!=0)
						{
           fac=abs(d1-d2)*100/(d1+d2);
            }
						if((fac>Calibration_Error)||d1==0||d2==0)
            return 0;
							//�Խ������
					d1=Calculation_distance(Coordinate_xy[1],Coordinate_xy[2]);
					d2=Calculation_distance(Coordinate_xy[0],Coordinate_xy[3]);
						if((d1+d2)!=0)
						{
                fac=abs(d1-d2)*100/(d1+d2);
            }
						if((fac>Calibration_Error)||d1==0||d2==0)
          return 0;						
		      return 1;
}



//����У׼����

void touch_Calibration(void)
{
    //ˮƽ����LCD�����ʵ�ʾ���DisplaySample[1].x-DisplaySample[0].x���������ϵľ���Coordinate_xy[1][0]-Coordinate_xy[0][0]
	
	Touch_date.xfac=(float)(DisplaySample[1].x-DisplaySample[0].x)/(Coordinate_xy[1][0]-Coordinate_xy[0][0]);
	Touch_date.xoff=((DisplaySample[1].x+DisplaySample[0].x)-Touch_date.xfac*(Coordinate_xy[1][0]+Coordinate_xy[0][0]))/2;//�õ�xoff
						  
 Touch_date.yfac=(float)(DisplaySample[2].y-DisplaySample[0].y)/(Coordinate_xy[2][1]-Coordinate_xy[0][1]);//�õ�yfac
 Touch_date.yoff=((DisplaySample[2].y+DisplaySample[0].y)-Touch_date.yfac*(Coordinate_xy[2][1]+Coordinate_xy[0][1]))/2;//�õ�yoff  
}

//������У׼����
//�õ��ĸ�У׼����
void Touch_Adjust(void)
{								 
	u8  cnt=0;		
  u8 flag;   
	cnt=0;				
	BACK_COLOR =WHITE;
	LCD_Clear(WHITE);//����   
	POINT_COLOR=RED;//��ɫ 
	flag=0;

	Touch_date.xfac=0;//xfac��������Ƿ�У׼��,����У׼֮ǰ�������!�������	 
	
	loop:for( cnt=0;cnt<4;cnt++)
	   {
       LCD_Clear(WHITE);//���� 
			 if(flag==0)
			 {

		 LCD_ShowString(35,80,TP_REMIND_MSG_TBL,POINT_COLOR);
			 }
			 else
			 {

		 LCD_ShowString(35,80,TP_REMIND_MSG_TBL1,POINT_COLOR);
       }
	     Draw_Touch_Coordinate(DisplaySample[cnt].x,DisplaySample[cnt].y,POINT_COLOR);
			 while(1)
			 {
	
      Read_TP(1);
		if((Pen_data.Key_Sta&0xc0)==TP_Key_Down)//����������һ��(��ʱ�����ɿ���.)
    {							//������������ 
			 Coordinate_xy[cnt][0]=Pen_data.X;
			 Coordinate_xy[cnt][1]=Pen_data.Y; 
     Pen_data.Key_Sta&=~(1<<6);//��ǰ����Ѿ����������.
			 break;
			}
			// }
		  }
    }
		if(!touch_Calibration_Calculation())
		{
    		cnt=0;
				flag=1;		
        goto loop;

    }
//������
				 touch_Calibration();

					POINT_COLOR=BLUE;
					LCD_Clear(WHITE);//����

			LCD_ShowString(35,110,"Touch Screen Adjust OK!",POINT_COLOR);//У�����
					delay_ms(400);
					LCD_Clear(WHITE);//����   
}

//��������ʼ��  		    
//����ֵ:0,û�н���У׼
//       1,���й�У׼
void TP_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;	
		
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOB,C,Fʱ��

    //GPIOB1,2��ʼ������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;//PB1/PB2 ����Ϊ��������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//����ģʽ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PB0����Ϊ�������
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//PC13����Ϊ�������
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��	
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PF11�����������
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��			
		

    Touch_Adjust();  	//��ĻУ׼ 						 
}
