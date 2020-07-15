#include "sys.h"
#include "delay.h"
#include "lm75a.h"
#include "encoder.h"
#include "oled0561.h"
#include "rtc.h"
#include "bkp.h"
int main (void){//������
	//��ʼ����������
	u8 buffer[3];//�����¶�ֵ
	u16 MENU=1;//���˵��˵���
	int a,b;//ѡװ������״̬��־
	//ϵͳ��ʼ��
	delay_ms(100); //�ϵ�ʱ�ȴ�������������
	RCC_Configuration(); //ϵͳʱ�ӳ�ʼ�� 
	RTC_Config();//��ʼ��ʱ��
	BKP_Configuration();//��ʼ��BKP
	I2C_Configuration();//I2C��ʼ��
	LM75A_GetTemp(buffer); //��ȡLM75A���¶�����
	OLED0561_Init(); //OLED��ʼ��
	OLED_DISPLAY_LIT(100);//��������
	ENCODER_Init();//��ʼ����ת������
	delay_ms(1000); //��ʱ
	MENU = BKP_ReadBackupRegister(BKP_DR2);//��ȡBKPֵ
	if(!(MENU>=1&&MENU<=3))MENU=1;//�ж�BKP��ֵ������1,2,3//�˵�ֵ����Ϊ1
		
	while(1){
		if(MENU==1){//���˵���ʾ��ǰ�¶ȣ���ǰʪ�ȣ�����ʱ��
			OLED_DISPLAY_CLEAR();//	���OLDE��Ļ
			INVERSE_OLED_DISPLAY_8x16(0,0*8,1+0x30); //���ַ���ʾ1
			INVERSE_OLED_DISPLAY_8x16(0,1*8,80+0x30); //��ʾ����
			INVERSE_OLED_DISPLAY_16x16(0,1*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,2*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,3*16,0);//������ʾ	 ���˵�
			INVERSE_OLED_DISPLAY_16x16(0,4*16,1);
			INVERSE_OLED_DISPLAY_16x16(0,5*16,2);
			INVERSE_OLED_DISPLAY_16x16(0,6*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,7*16,13);
			OLED_DISPLAY_16x16(2,0*16,14);//������ʾ	 ��ǰ
			OLED_DISPLAY_16x16(2,1*16,15);
			OLED_DISPLAY_16x16(2,2*16,3);//������ʾ	 �¶�
			OLED_DISPLAY_16x16(2,3*16,4);
			OLED_DISPLAY_8x16(2,8*8,10+0x30);//ð��
			OLED_DISPLAY_16x16(2,7*16,16);//��ʾ��
			OLED_DISPLAY_16x16(4,0*16,14);//������ʾ	 ��ǰ
			OLED_DISPLAY_16x16(4,1*16,15);
			OLED_DISPLAY_16x16(4,2*16,5);//������ʾ	 ʪ��
			OLED_DISPLAY_16x16(4,3*16,4);
			OLED_DISPLAY_8x16(4,8*8,10+0x30);//ð��
			OLED_DISPLAY_8x16(4,9*8,2+0x30);
			OLED_DISPLAY_8x16(4,10*8,5+0x30);
			OLED_DISPLAY_8x16(4,11*8,0x25);//��ʾ�ٷֺ�
			OLED_DISPLAY_16x16(6,0*16,17);//������ʾ ����ʱ��	 
			OLED_DISPLAY_16x16(6,1*16,18);
			OLED_DISPLAY_16x16(6,2*16,19);	
			OLED_DISPLAY_16x16(6,3*16,20);
			BKP_WriteBackupRegister(BKP_DR2, 1);//���üĴ�����д��1
			MENU=11; //�Զ������˵�11
		}
	
		if(MENU==11){ //�˵��л�
			RTC_Get();//��ȡRTCʱ��
			LM75A_GetTemp(buffer);
			OLED_DISPLAY_8x16(6,8*8,rhour/10+0x30);
			OLED_DISPLAY_8x16(6,9*8,rhour%10+0x30);
			OLED_DISPLAY_8x16(6,10*8,10+0x30);//ð��
			OLED_DISPLAY_8x16(6,11*8,rmin/10+0x30);
			OLED_DISPLAY_8x16(6,12*8,rmin%10+0x30);
			OLED_DISPLAY_8x16(6,13*8,10+0x30);//ð��
			OLED_DISPLAY_8x16(6,14*8,rsec/10+0x30);
			OLED_DISPLAY_8x16(6,15*8,rsec%10+0x30);
		
			if(buffer[0])OLED_DISPLAY_8x16(2,9*8,-3+0x30);//��ʾ����
			else OLED_DISPLAY_8x16(2,9*8,80+0x30);
			
			OLED_DISPLAY_8x16(2,10*8,buffer[1]/10+0x30);//�¶�ֵ
			OLED_DISPLAY_8x16(2,11*8,buffer[1]%10+0x30);
			OLED_DISPLAY_8x16(2,12*8,-2+0x30);//С����
			OLED_DISPLAY_8x16(2,13*8,buffer[2]/10+0x30);
			b=ENCODER_READ();	//������ת������������ת����
				if(b==1)MENU=2;//������ת������˵�2
				if(b==2)MENU=3;//������ת������˵�3
		}
		if(MENU==2){//ADC��ʾ�˵�
			OLED_DISPLAY_CLEAR();
			INVERSE_OLED_DISPLAY_8x16(0,0*8,2+0x30); //���ַ���ʾ1
			INVERSE_OLED_DISPLAY_8x16(0,1*8,80+0x30); //��ʾ����
			INVERSE_OLED_DISPLAY_16x16(0,1*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,2*16,13);
			
			INVERSE_OLED_DISPLAY_16x16(0,2*16,10); //��ʾģ�����˵�
			INVERSE_OLED_DISPLAY_16x16(0,3*16,11);
			INVERSE_OLED_DISPLAY_16x16(0,4*16,12);
			INVERSE_OLED_DISPLAY_16x16(0,5*16,1);
			INVERSE_OLED_DISPLAY_16x16(0,6*16,2);
			INVERSE_OLED_DISPLAY_16x16(0,7*16,13);
			
			OLED_DISPLAY_8x16_BUFFER(2,"ADC1:"); //��ʾ�ַ��� 
			OLED_DISPLAY_8x16_BUFFER(4,"ADC2:"); //��ʾ�ַ���
			OLED_DISPLAY_8x16_BUFFER(6,"ADC3: "); //��ʾ�ַ���
			BKP_WriteBackupRegister(BKP_DR2, 2);//���üĴ�����д��2
			MENU=21;//�Զ�����˵�21
		}
		if(MENU==21){
			b=ENCODER_READ();	//������ת������������ת����	
			if(b==1)MENU=3;//������ת������˵�3	
			if(b==2)MENU=1;//������ת������˵�1	              
		}
		if(MENU==3){//���ò˵�
			OLED_DISPLAY_CLEAR();//�����Ļ
			INVERSE_OLED_DISPLAY_8x16(0,0*8,3+0x30); //���ַ���ʾ1
			INVERSE_OLED_DISPLAY_8x16(0,1*8,80+0x30); //��ʾ����
			INVERSE_OLED_DISPLAY_16x16(0,1*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,2*16,6);//������ʾ	 ���ò˵�
			INVERSE_OLED_DISPLAY_16x16(0,3*16,7);
			INVERSE_OLED_DISPLAY_16x16(0,4*16,1);
			INVERSE_OLED_DISPLAY_16x16(0,5*16,2);
			INVERSE_OLED_DISPLAY_16x16(0,6*16,13); //��ʾ����
			INVERSE_OLED_DISPLAY_16x16(0,7*16,13);
			
			OLED_DISPLAY_16x16(2,0*16,21);//������ʾ	 ����
			OLED_DISPLAY_16x16(2,1*16,3);
			OLED_DISPLAY_8x16(2,4*8,10+0x30);//ð��
			OLED_DISPLAY_16x16(4,0*16,22);//������ʾ	 ����
			OLED_DISPLAY_16x16(4,1*16,3);
			OLED_DISPLAY_8x16(4,4*8,10+0x30);//ð��
			INVERSE_OLED_DISPLAY_16x16(6,0*16,8);//������ʾ	 ����
			INVERSE_OLED_DISPLAY_16x16(6,1*16,9);
			OLED_DISPLAY_8x16(6,4*8,10+0x30);//ð��
			MENU=31;//�Զ�ת��˵�31.
			BKP_WriteBackupRegister(BKP_DR2, 3);//���üĴ�����д��2
		}
		if(MENU==31){ //�ж���ת�����������ò˵�
			b=ENCODER_READ();//������ת������������ת����	
			if(b==1)MENU=1;	//������ת������˵�1
			if(b==2)MENU=2; //������ת������˵�2
		}
	}
}
	
	
	/*********************************************************************************************
	* �������� www.DoYoung.net
	* ���ҵ��� www.DoYoung.net/YT 
	*********************************************************************************************/
	/*
	
	���������塿
	u32     a; //����32λ�޷��ű���a
	u16     a; //����16λ�޷��ű���a
	u8     a; //����8λ�޷��ű���a
	vu32     a; //�����ױ��32λ�޷��ű���a
	vu16     a; //�����ױ�� 16λ�޷��ű���a
	vu8     a; //�����ױ�� 8λ�޷��ű���a
	uc32     a; //����ֻ����32λ�޷��ű���a
	uc16     a; //����ֻ�� ��16λ�޷��ű���a
	uc8     a; //����ֻ�� ��8λ�޷��ű���
	#define ONE  1   //�궨��
	delay_us(1); //��ʱ1΢��
	delay_ms(1); //��ʱ1����
	delay_s(1); //��ʱ1��
	GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED����
	
	*/



