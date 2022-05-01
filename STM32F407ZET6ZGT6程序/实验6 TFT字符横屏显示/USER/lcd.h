#ifndef __LCD_H
#define __LCD_H		

#include "stm32f4xx.h"
#include "stdlib.h"
	  
#define Horizontal_or_Vertical  1	//�����Ƿ�ʹ�ú��� 		0,��ʹ��.1,ʹ��.
 #if Horizontal_or_Vertical==1
#define LCD_W 320
#define LCD_H 240
 #define MAX_CHAR_POSX 312
 #define MAX_CHAR_POSY 232 

#define L2R_U2D  (0<<5)|(1<<4)|(1<<3);  //������,���ϵ���
#define L2R_D2U  (0<<5)|(0<<4)|(1<<3); //������,���µ���
#define R2L_U2D  (0<<5)|(0<<4)|(0<<3);//���ҵ���,���ϵ���
#define R2L_D2U  (1<<5)|(0<<4)|(1<<3); //���ҵ���,���µ���

#define U2D_L2R  (0<<5)|(1<<4)|(0<<3); //���ϵ���,������
#define U2D_R2L  (1<<5)|(1<<4)|(0<<3);//���ϵ���,���ҵ���
#define D2U_L2R  (0<<5)|(0<<4)|(0<<3); //���µ���,������
#define D2U_R2L  (1<<5)|(0<<4)|(0<<3); //���µ���,���ҵ���
#else     
#define LCD_W 240
#define LCD_H 320
// #define MAX_CHAR_POSX 232
// #define MAX_CHAR_POSY 312


#define L2R_U2D  (1<<5)|(1<<4)|(0<<3);  //������,���ϵ���
#define L2R_D2U  (0<<5)|(1<<4)|(0<<3); //������,���µ���
#define R2L_U2D  (1<<5)|(0<<4)|(0<<3);//���ҵ���,���ϵ���
#define R2L_D2U  (0<<5)|(0<<4)|(0<<3); //���ҵ���,���µ���

#define U2D_L2R  (0<<5)|(0<<4)|(0<<3); //���ϵ���,������
#define U2D_R2L  (1<<5)|(0<<4)|(1<<3);//���ϵ���,���ҵ���
#define D2U_L2R  (0<<5)|(1<<4)|(1<<3); //���µ���,������
#define D2U_R2L  (0<<5)|(0<<4)|(1<<3); //���µ���,���ҵ���
#endif
  

//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ


//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
#define	LCD_LED GPIO_SetBits(GPIOB,GPIO_Pin_15) //LCD����    		 PB0 	   

//LCD��ַ�ṹ��
typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;


//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 111110=0X3E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x0000007E))
#define LCD             ((LCD_TypeDef *) LCD_BASE)


#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	    															  
void LCD_WR_REG(u16 regval);
void LCD_WR_DATA(u16 data);
u16 LCD_RD_DATA(void);
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_Display(u8 off_on);
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_Scan_Dir(void);
void LCD_Init(void);
void LCD_Clear(u16 color);
#endif  
	 
	 



