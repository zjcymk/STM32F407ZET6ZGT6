#ifndef __TOUCH_H__
#define __TOUCH_H__

 #include "stm32f4xx.h"   

#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 
#define CT_MAX_TOUCH  5    //������֧�ֵĵ���,�̶�Ϊ5��


//����״̬	 
#define Key_Down 0x80
#define TP_Key_Down 0x40
#define Key_Up   0x00 


/* Һ������ṹ�� */
typedef	struct POINT 
{
   uint16_t x;		
   uint16_t y;
}Coordinate;

//�ʸ˽ṹ��
typedef struct 
{
	u16 X0;//ԭʼ����
	u16 Y0;
	u16 X; //����/�ݴ�����
	u16 Y;						   	    
	u8  Key_Sta;//�ʵ�״̬			  
}Pen_Parameters;	

//������У׼����
typedef struct 
{
float xfac;
float yfac;
short xoff;
short yoff;

}Touch_Adjust_Parameters;


extern Touch_Adjust_Parameters Touch_date;
extern Pen_Parameters Pen_data;


//�봥����оƬ��������	   
#define TS_DRAW_RANGE 50 
#define PEN GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)   //PC1  INT
#define DOUT GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)   //PC2  MISO 
#define TDIN_Low GPIO_ResetBits(GPIOF,GPIO_Pin_11)  //PC3  MOSI
#define TDIN_High GPIO_SetBits(GPIOF,GPIO_Pin_11)  //PC3  MOSI
#define TCLK_Low GPIO_ResetBits(GPIOB,GPIO_Pin_0)  //PC0  SCLK
#define TCLK_High GPIO_SetBits(GPIOB,GPIO_Pin_0)  //PC0  SCLK   
#define TCS_Low GPIO_ResetBits(GPIOC,GPIO_Pin_13) //PC13 CS
#define TCS_High GPIO_SetBits(GPIOC,GPIO_Pin_13) //PC13 CS
 
//����������
void TP_Write_Byte(u8 num);						//�����оƬд��һ������
u16 TP_Read_AD(u8 CMD);							//��ȡADת��ֵ
u16 TP_Read_XOY(u8 xy);							//���˲��������ȡ(X/Y)
u8 TP_Read_XY(u16 *x,u16 *y);					//˫�����ȡ(X+Y)
u8 TP_Read_XY2(u16 *x,u16 *y);					//����ǿ�˲���˫���������ȡ
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//��һ������У׼��
void TP_Save_Adjdata(void);						//����У׼����
u8 TP_Get_Adjdata(void);						//��ȡУ׼����
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);//��ʾУ׼��Ϣ
//������/������ ���ú���
u8 Read_TP(u8 tp);							//ɨ��
 void TP_Init(void);
 void Draw_Big_Circle(u8 x,u16 y,u16 Color);
#endif

















