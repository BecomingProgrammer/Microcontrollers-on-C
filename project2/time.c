/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               time.c
** Latest modified Date:    2017-5-31
** Latest Version:          
** Descriptions:            ��ʱ��ʵ���ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              jsj
** Created date:            2017-5-31
** Version:                 
** Descriptions:            
**
**--------------------------------------------------------------------------------------------------------
*--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#include "time.h"
#include<8051.h>
static unsigned int uiHigh16; //��16λ
static  volatile unsigned char uctime32Flag=0;  //32λ��ʱ�������־

/*********************************************************************************************************
** Function name:           allEnableOpen
** Descriptions:             ��ʹ���жϽ���ʹ��
** input parameters:      none
** output parameters:       char
** Returned value:      0------ʹ�ܳɹ�
                                 -1----ʹ��ʧ��
*********************************************************************************************************/
char allEnableOpen()
{
	EA=1;
	return 0;
}

/*********************************************************************************************************
** Function name:           allEnableClose
** Descriptions:             ��ʹ���жϽ��н�ֹ
** input parameters:      none
** output parameters:       char
** Returned value:      0------��ֹ�ɹ�
                                 -1----��ֹʧ��
*********************************************************************************************************/
char allEnableClose()
{
	EA=0;
	return 0;
}


/*********************************************************************************************************
** Function name:           time0Init
** Descriptions:             ��ʱ��0��ʼ��
** input parameters:      none
** output parameters:       char
** Returned value:      0------��ʼ���ɹ�
                                 -1----��ʼ��ʧ��
*********************************************************************************************************/
char time0Init()
{
	TMOD=(TMOD&0xf0)|0x01;
	ET0=1;
	return 0;
}

/*********************************************************************************************************
** Function name:           delay100us
** Descriptions:             ��ʱ��������ʱ��λΪ100us
** input parameters:      ��ʱʱ��
** output parameters:       none
** Returned value:      
*********************************************************************************************************/
void delay100us(unsigned int uiTime)
{
	 unsigned long ulSatrt;
	 unsigned int uiLow16;
	 ulSatrt=((11059200ul/12)/400)*uiTime/(10000ul/400);
	 ulSatrt=-ulSatrt;
	 
	 uiLow16=ulSatrt%0x10000;
	 TL0=uiLow16%256;
	 TH0=uiLow16/256;
	 
	 uiHigh16=ulSatrt/0x10000;
	 
	 TR0=1;
	 
	 while(uctime32Flag==0){};
	 uctime32Flag=0;
	   
}


/*********************************************************************************************************
** Function name:           time0Interrupt
** Descriptions:             ��ʱ��0�жϺ���
** input parameters:      none
** output parameters:       none
** Returned value:      
*********************************************************************************************************/
void time0Interrupt()  interrupt 1
{
	uiHigh16++;
	
	if(uiHigh16==0){
		uctime32Flag=1;
		TR0=0;
	}
}
