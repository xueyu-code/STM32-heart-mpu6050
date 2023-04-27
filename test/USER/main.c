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
 short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
 short aacx_data;
 
 int main(void)
 {	 
	int i=0;
	float pitch,roll,yaw; 		//ŷ����


	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	//��ʱ��ʼ�� 
	uart_init(9600);


	MPU_Init();					//��ʼ��MPU6050
	 while(mpu_dmp_init())
 	{
	} 
	
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(0,6,"ACC:");
	
	TIM3_Int_Init(71,999);				//һ���붨ʱ
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//�豸״̬�ṹ���ʼ��
	usart3_init((u32)9600);//WIFI��ʼ��
	gizwitsInit();//��������ʼ��
//	gizwitsSetMode(WIFI_RESET_MODE);
	delay_ms(500);
//	gizwitsSetMode(WIFI_AIRLINK_MODE);
	gizwitsSetMode(WIFI_SOFTAP_MODE);
//	 delay_ms(1000);

 	while(1)
	{
		
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 
//			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
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







