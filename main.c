#include "sys.h"
#include "delay.h"
#include "lm75a.h"
#include "encoder.h"
#include "oled0561.h"
#include "rtc.h"
#include "bkp.h"
int main (void){//主程序
	//初始化变量常量
	u8 buffer[3];//放入温度值
	u16 MENU=1;//主菜单菜单号
	int a,b;//选装编码器状态标志
	//系统初始化
	delay_ms(100); //上电时等待其他器件就绪
	RCC_Configuration(); //系统时钟初始化 
	RTC_Config();//初始化时钟
	BKP_Configuration();//初始化BKP
	I2C_Configuration();//I2C初始化
	LM75A_GetTemp(buffer); //读取LM75A的温度数据
	OLED0561_Init(); //OLED初始化
	OLED_DISPLAY_LIT(100);//亮度设置
	ENCODER_Init();//初始化旋转编码器
	delay_ms(1000); //延时
	MENU = BKP_ReadBackupRegister(BKP_DR2);//读取BKP值
	if(!(MENU>=1&&MENU<=3))MENU=1;//判断BKP的值不等于1,2,3//菜单值设置为1
		
	while(1){
		if(MENU==1){//主菜单显示当前温度，当前湿度，北京时间
			OLED_DISPLAY_CLEAR();//	清楚OLDE屏幕
			INVERSE_OLED_DISPLAY_8x16(0,0*8,1+0x30); //数字反显示1
			INVERSE_OLED_DISPLAY_8x16(0,1*8,80+0x30); //显示白面
			INVERSE_OLED_DISPLAY_16x16(0,1*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,2*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,3*16,0);//汉字显示	 主菜单
			INVERSE_OLED_DISPLAY_16x16(0,4*16,1);
			INVERSE_OLED_DISPLAY_16x16(0,5*16,2);
			INVERSE_OLED_DISPLAY_16x16(0,6*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,7*16,13);
			OLED_DISPLAY_16x16(2,0*16,14);//汉字显示	 当前
			OLED_DISPLAY_16x16(2,1*16,15);
			OLED_DISPLAY_16x16(2,2*16,3);//汉字显示	 温度
			OLED_DISPLAY_16x16(2,3*16,4);
			OLED_DISPLAY_8x16(2,8*8,10+0x30);//冒号
			OLED_DISPLAY_16x16(2,7*16,16);//显示℃
			OLED_DISPLAY_16x16(4,0*16,14);//汉字显示	 当前
			OLED_DISPLAY_16x16(4,1*16,15);
			OLED_DISPLAY_16x16(4,2*16,5);//汉字显示	 湿度
			OLED_DISPLAY_16x16(4,3*16,4);
			OLED_DISPLAY_8x16(4,8*8,10+0x30);//冒号
			OLED_DISPLAY_8x16(4,9*8,2+0x30);
			OLED_DISPLAY_8x16(4,10*8,5+0x30);
			OLED_DISPLAY_8x16(4,11*8,0x25);//显示百分号
			OLED_DISPLAY_16x16(6,0*16,17);//汉字显示 北京时间	 
			OLED_DISPLAY_16x16(6,1*16,18);
			OLED_DISPLAY_16x16(6,2*16,19);	
			OLED_DISPLAY_16x16(6,3*16,20);
			BKP_WriteBackupRegister(BKP_DR2, 1);//备用寄存器里写入1
			MENU=11; //自动跳到菜单11
		}
	
		if(MENU==11){ //菜单切换
			RTC_Get();//读取RTC时钟
			LM75A_GetTemp(buffer);
			OLED_DISPLAY_8x16(6,8*8,rhour/10+0x30);
			OLED_DISPLAY_8x16(6,9*8,rhour%10+0x30);
			OLED_DISPLAY_8x16(6,10*8,10+0x30);//冒号
			OLED_DISPLAY_8x16(6,11*8,rmin/10+0x30);
			OLED_DISPLAY_8x16(6,12*8,rmin%10+0x30);
			OLED_DISPLAY_8x16(6,13*8,10+0x30);//冒号
			OLED_DISPLAY_8x16(6,14*8,rsec/10+0x30);
			OLED_DISPLAY_8x16(6,15*8,rsec%10+0x30);
		
			if(buffer[0])OLED_DISPLAY_8x16(2,9*8,-3+0x30);//显示负数
			else OLED_DISPLAY_8x16(2,9*8,80+0x30);
			
			OLED_DISPLAY_8x16(2,10*8,buffer[1]/10+0x30);//温度值
			OLED_DISPLAY_8x16(2,11*8,buffer[1]%10+0x30);
			OLED_DISPLAY_8x16(2,12*8,-2+0x30);//小数点
			OLED_DISPLAY_8x16(2,13*8,buffer[2]/10+0x30);
			b=ENCODER_READ();	//读出旋转编码器左右旋转方向
				if(b==1)MENU=2;//向右旋转，进入菜单2
				if(b==2)MENU=3;//向左旋转，进入菜单3
		}
		if(MENU==2){//ADC显示菜单
			OLED_DISPLAY_CLEAR();
			INVERSE_OLED_DISPLAY_8x16(0,0*8,2+0x30); //数字反显示1
			INVERSE_OLED_DISPLAY_8x16(0,1*8,80+0x30); //显示白面
			INVERSE_OLED_DISPLAY_16x16(0,1*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,2*16,13);
			
			INVERSE_OLED_DISPLAY_16x16(0,2*16,10); //显示模拟量菜单
			INVERSE_OLED_DISPLAY_16x16(0,3*16,11);
			INVERSE_OLED_DISPLAY_16x16(0,4*16,12);
			INVERSE_OLED_DISPLAY_16x16(0,5*16,1);
			INVERSE_OLED_DISPLAY_16x16(0,6*16,2);
			INVERSE_OLED_DISPLAY_16x16(0,7*16,13);
			
			OLED_DISPLAY_8x16_BUFFER(2,"ADC1:"); //显示字符串 
			OLED_DISPLAY_8x16_BUFFER(4,"ADC2:"); //显示字符串
			OLED_DISPLAY_8x16_BUFFER(6,"ADC3: "); //显示字符串
			BKP_WriteBackupRegister(BKP_DR2, 2);//备用寄存器里写入2
			MENU=21;//自动进入菜单21
		}
		if(MENU==21){
			b=ENCODER_READ();	//读出旋转编码器左右旋转方向	
			if(b==1)MENU=3;//向右旋转，进入菜单3	
			if(b==2)MENU=1;//向左旋转，进入菜单1	              
		}
		if(MENU==3){//设置菜单
			OLED_DISPLAY_CLEAR();//清除屏幕
			INVERSE_OLED_DISPLAY_8x16(0,0*8,3+0x30); //数字反显示1
			INVERSE_OLED_DISPLAY_8x16(0,1*8,80+0x30); //显示白面
			INVERSE_OLED_DISPLAY_16x16(0,1*16,13);
			INVERSE_OLED_DISPLAY_16x16(0,2*16,6);//汉字显示	 设置菜单
			INVERSE_OLED_DISPLAY_16x16(0,3*16,7);
			INVERSE_OLED_DISPLAY_16x16(0,4*16,1);
			INVERSE_OLED_DISPLAY_16x16(0,5*16,2);
			INVERSE_OLED_DISPLAY_16x16(0,6*16,13); //显示白面
			INVERSE_OLED_DISPLAY_16x16(0,7*16,13);
			
			OLED_DISPLAY_16x16(2,0*16,21);//汉字显示	 高温
			OLED_DISPLAY_16x16(2,1*16,3);
			OLED_DISPLAY_8x16(2,4*8,10+0x30);//冒号
			OLED_DISPLAY_16x16(4,0*16,22);//汉字显示	 低温
			OLED_DISPLAY_16x16(4,1*16,3);
			OLED_DISPLAY_8x16(4,4*8,10+0x30);//冒号
			INVERSE_OLED_DISPLAY_16x16(6,0*16,8);//汉字显示	 光照
			INVERSE_OLED_DISPLAY_16x16(6,1*16,9);
			OLED_DISPLAY_8x16(6,4*8,10+0x30);//冒号
			MENU=31;//自动转入菜单31.
			BKP_WriteBackupRegister(BKP_DR2, 3);//备用寄存器里写入2
		}
		if(MENU==31){ //判断旋转编码器，设置菜单
			b=ENCODER_READ();//读出旋转编码器左右旋转方向	
			if(b==1)MENU=1;	//向右旋转，进入菜单1
			if(b==2)MENU=2; //向左旋转，进入菜单2
		}
	}
}
	
	
	/*********************************************************************************************
	* 杜洋工作室 www.DoYoung.net
	* 洋桃电子 www.DoYoung.net/YT 
	*********************************************************************************************/
	/*
	
	【变量定义】
	u32     a; //定义32位无符号变量a
	u16     a; //定义16位无符号变量a
	u8     a; //定义8位无符号变量a
	vu32     a; //定义易变的32位无符号变量a
	vu16     a; //定义易变的 16位无符号变量a
	vu8     a; //定义易变的 8位无符号变量a
	uc32     a; //定义只读的32位无符号变量a
	uc16     a; //定义只读 的16位无符号变量a
	uc8     a; //定义只读 的8位无符号变量
	#define ONE  1   //宏定义
	delay_us(1); //延时1微秒
	delay_ms(1); //延时1毫秒
	delay_s(1); //延时1秒
	GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED控制
	
	*/



