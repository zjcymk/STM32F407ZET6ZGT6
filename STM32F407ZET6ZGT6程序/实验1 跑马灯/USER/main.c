

/******************** ��ѧ�Ƽ� **************************
 * ʵ��ƽ̨��������STM32������
 * ��汾  ��ST3.5.0
 * ����    ����ѧ�Ƽ��Ŷ� 
 * �Ա�    ��http://shop102218275.taobao.com/
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 *��Ȩ���У�����ؾ���
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


