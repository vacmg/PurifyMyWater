//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STC12C5A60S2,晶振30M  单片机工作电压3.3V
//QDtech-LCD液晶驱动 for C51
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/7/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
//********************************************************************************
//=========================================电源接线================================================//
//5V接DC 5V电源   3V3接DC 3.3V电源
//GND接地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为8位并口
//液晶屏模块             C51单片机
// LCD_D0~LCD_D7 接       P00~P07        //8位并口数据总线
//=======================================液晶屏控制线接线==========================================//
//液晶屏模块             C51单片机
// LCD_CS        接        P13           //片选控制信号
// LCD_RST       接        P33           //复位信号
// LCD_RS        接        P12           //数据/命令选择控制信号
// LCD_WR        接        P11           //写控制信号
// LCD_RD        接        P10           //读控制信号
//=========================================触摸屏接线=========================================//
//STC89C52RC单片机ROM太小，无法运行带触摸功能的程序，所以触摸屏不需要接线
//不使用触摸或者模块本身不带触摸，则可不连接
//触摸屏使用的数据总线类型为SPI
//触摸屏模块             C51单片机
//  T_CLK        接        P36          //触摸屏SPI时钟信号
//  T_CS         接        P37          //触摸屏片选控制信号
//  T_DIN        接        P34          //触摸屏SPI写信号
//  T_DO         接        P35          //触摸屏SPI读信号
//  T_IRQ        接        P40          //触摸屏响应检查信号，如单片机无P4组，请自行更改其他可用IO并修改代码定义
//**************************************************************************************************/		
#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"

//STC单片机IO推挽输出设置定义
//其他普通C51单片机无此配置请屏蔽下面这条语句
sfr P3M1  = 0xB1;	//P3M1.n,P3M0.n 	=00--->Standard,	01--->push-pull
sfr P3M0  = 0xB2;	//					=10--->pure input,	11--->open drain

sfr p0M1 = 0x93;
sfr p0M0 = 0x94;

sfr p1M1 = 0x91;
sfr p1M0 = 0x92;

sfr P2M1 = 0x95;
sfr P2M0 = 0x96;

/////////////////////////////////////用户配置区///////////////////////////////////	 
//支持横竖屏快速定义切换
#define USE_HORIZONTAL  	0 //定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转
#define LCD_USE8BIT_MODEL   1 	//定义数据总线是否使用8位模式 0,使用16位模式.1,使用8位模式
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////	  
//定义LCD的尺寸
#define LCD_W 320
#define LCD_H 480

//IO连接
#define  LCD_DataPortH P2     //高8位数据口,8位模式下只使用高8位 
#define  LCD_DataPortL P0     //低8位数据口	,8位模式下低8位可以不接线,请确认P0口已经上拉10K电阻,不宜太小，最小4.7K,推荐10K.
sbit LCD_RS = P1^2;  		 //数据/命令切换
sbit LCD_WR = P1^1;		  //写控制
sbit LCD_RD = P1^0;		     //读控制
sbit LCD_CS = P1^3;		//片选	
sbit LCD_RESET = P3^3;	      //复位 
//sbit LCD_BL=P3^2;		//背光控制，如果不需要控制，接3.3V

//LCD的画笔颜色和背景色	   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色
//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	 wramcmd;		//开始写gram指令
	u16  rramcmd;   //开始读gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
void LCD_Init(void); 
void LCD_Clear(u16 Color);
void LCD_write(u8 HVAL,u8 LVAL);
u16 LCD_read(void);
void LCD_WR_DATA(u16 Data);
u16 LCD_RD_DATA(void);
void LCD_WR_REG(u16 Reg);
void LCD_SetCursor(u16 Xpos, u16 Ypos);//设置光标位置
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);//设置显示窗口
void LCD_DrawPoint(u16 x,u16 y);//画点
u16 LCD_ReadPoint(u16 x,u16 y);
void LCD_WriteRAM_Prepare(void);
void LCD_ReadRAM_Prepare(void);
void LCD_direction(u8 direction );
void LCD_WR_DATA_16Bit(u16 Data);
u16 Lcd_RD_DATA_16Bit(void);
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
void LCD_ReadReg(u16 LCD_Reg,u8 *Rval,int n);
u16 LCD_Read_ID(void);


//画笔颜色
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
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


					  		 
#endif  
	 
	 



