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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级


	uart_init(9600);	 	
	delay_init();	//延时初始化 
	//心率传感器相关初始化
	IIC_GPIO_INIT();
	MAX30102_GPIO();
	Max30102_reset();	
	MAX30102_Config();
		for(i = 0;i < 128;i++) 
	{
		while(MAX30102_INTPin_Read()==0)
		{
			//读取FIFO
			max30102_read_fifo();
		}
	}

 	while(1)
	{
if(MAX30102_INTPin_Read()==0)
	blood_Loop();


}
}







