//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F767IGT6,����ԭ��Apollo STM32F4/F7������,��Ƶ216MHZ������12MHZ
//QDtech-TFTҺ������ for STM32 IOģ��
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/08/09
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
//     LCDģ��                STM32��Ƭ��
//      5V/3V3       ��        DC5V/3.3V        //��Դ
//      GND          ��          GND            //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������Ϊ8λ��������
//     LCDģ��                STM32��Ƭ��    
//     LCD_D0~LCD_D7 ��        PE0~PE7         //Һ������8λ���������ź�
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 				        STM32��Ƭ�� 
//       WR          ��          PC7           //Һ����д���ݿ����ź�
//       RD          ��          PC6           //Һ���������ݿ����ź�
//       RS          ��          PC8           //Һ��������/��������ź�
//       RST         ��          PC4           //Һ������λ�����ź�
//       CS          ��          PC9           //Һ����Ƭѡ�����ź�
//       BL          ��          PC10          //Һ������������ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��                STM32��Ƭ�� 
//       PEN         ��          PH10          //�����������ж��ź�
//       MISO        ��          PH11          //������SPI���߶��ź�
//       MOSI        ��          PH12          //������SPI����д�ź�
//       T_CS        ��          PH13          //������Ƭѡ�����ź�
//       CLK         ��          PH9           //������SPI����ʱ���ź�
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/			
#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED�˿ڶ���
#define LED0(n)		(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET))
#define LED0_Toggle (HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1))
#define LED1(n)		(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET))
#define LED1_Toggle (HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0))

void LED_Init(void);//��ʼ��		 				    
#endif