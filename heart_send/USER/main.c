#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "math.h"
#include "oled.h"
#include "bmp.h"
#include "iic.h"
#include "MAX30102.h"
#include "algorithm.h"
#include "blood.h"
#include "timer.h"

u8 data_buf[20];
u8 data_return;

 int main(void)
 {	 
	int i;
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�


	uart_init(9600);	 	
	delay_init();	//��ʱ��ʼ�� 
	//���ʴ�������س�ʼ��
	IIC_GPIO_INIT();
	MAX30102_GPIO();
	Max30102_reset();	
	MAX30102_Config();
		for(i = 0;i < 128;i++) 
	{
		while(MAX30102_INTPin_Read()==0)
		{
			//��ȡFIFO
			max30102_read_fifo();
		}
	}

 	while(1)
	{
if(MAX30102_INTPin_Read()==0)
	blood_Loop();


}
}







