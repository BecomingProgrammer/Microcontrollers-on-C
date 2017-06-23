#include"buzze.h"
#include"buzze_cfg.h"
/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               buzze.h
** Latest modified Date:    2017-5-31
** Latest Version:          
** Descriptions:            ������ʵ���ļ�
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

/*********************************************************************************************************
** Function name:           buzzeInit
** Descriptions:             ��������ʼ��
** input parameters:      none
** output parameters:       char
** Returned value:      0------��ʼ���ɹ�
                                 -1----��ʼ��ʧ��
*********************************************************************************************************/

static volatile unsigned char GucLow8;
static volatile unsigned char GucHigh8;

static unsigned int GuiHigh16; //��16λ
static  volatile unsigned char Guctime32Flag=0;  //32λ��ʱ�������־
char buzzeInit()
{
	//��ʱ��1
	TMOD=(TMOD&0x0f)|0x10;
	TR1=0;
	TF1=0;
	ET1=1;
	PT1=1;
	//��ʱ��0
	time0Init();
   return 0;
}


/*********************************************************************************************************
** Function name:           buzzeRun
** Descriptions:             ����������
** input parameters:      uiHz:�ض�Ƶ��,ulTime;�ض�ʱ�䣬��100usΪ��λ
** output parameters:       none
** Returned value:      
                                 
*********************************************************************************************************/
void buzzeRun(unsigned int uiHz,unsigned long ulTime )
{
	unsigned int uiStart;
	
	uiStart=0x10000-(11059200ul/12)/(uiHz*2);
	GucHigh8=uiStart/0x100;
	GucLow8=uiStart%0x100;
	
	TH1=GucHigh8;
	TL1=GucLow8;
	TR1=1;
	delay100us(ulTime);
	
	
}


/*********************************************************************************************************
** Function name:           time1Interrupt
** Descriptions:             ��ʱ��1�жϺ���
** input parameters:      none
** output parameters:       none
** Returned value:      
*********************************************************************************************************/
void time1Interrupt()  interrupt 3
{
	TR1=0;
	
	TH1=GucHigh8;
	TL1=GucLow8;
	TR1=1;
	
	BUZZE_PIN=!BUZZE_PIN;
}

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
void delay100us(unsigned long uiTime)
{
	 unsigned long ulSatrt;
	 unsigned int uiLow16;
	 ulSatrt=((11059200ul/12)/400)*uiTime/(10000ul/400);
	 ulSatrt=-ulSatrt;
	 
	 uiLow16=ulSatrt%0x10000;
	 TL0=uiLow16%256;
	 TH0=uiLow16/256;
	 
	 GuiHigh16=ulSatrt/0x10000;
	 
	 TR0=1;
	 
	 while(Guctime32Flag==0){};
	 Guctime32Flag=0;
	   
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
	GuiHigh16++;
	if(GuiHigh16==0){
		Guctime32Flag=1;
		TR0=0;
		TR1=0;
		
	}
}


