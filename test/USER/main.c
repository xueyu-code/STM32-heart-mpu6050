#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "math.h"
#include "oled.h"
#include "bmp.h"
#include "usart2.h"
#include "timer.h"
#include "gizwits_product.h"


 extern u8 heart,spo2;
 short aacx,aacy,aacz;		//加速度传感器原始数据
 short aacx_data;
 
 int main(void)
 {	 
	int i=0;
	float pitch,roll,yaw; 		//欧拉角


	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();	//延时初始化 
	uart_init(9600);


	MPU_Init();					//初始化MPU6050
	 while(mpu_dmp_init())
 	{
	} 
	
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(0,6,"ACC:");
	
	TIM3_Int_Init(71,999);				//一毫秒定时
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//设备状态结构体初始化
	usart3_init((u32)9600);//WIFI初始化
	gizwitsInit();//缓冲区初始化
//	gizwitsSetMode(WIFI_RESET_MODE);
	delay_ms(500);
//	gizwitsSetMode(WIFI_AIRLINK_MODE);
	gizwitsSetMode(WIFI_SOFTAP_MODE);
//	 delay_ms(1000);

 	while(1)
	{
		
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 
//			temp=MPU_Get_Temperature();	//得到温度值
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
				aacx_data=aacx;
			OLED_ShowNum(80,6,aacx,3,16);
		}
	OLED_ShowString(0,0,"hearts:");
	OLED_ShowNum(100,0,heart,3,16);

	userHandle();
  gizwitsHandle((dataPoint_t *)&currentDataPoint);
		
	OLED_ShowString(6,4,"Spo2:");
	OLED_ShowNum(100,4,spo2,3,16);
		
				


}
}







