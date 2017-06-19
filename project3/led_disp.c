/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               led_disp.c
** Latest modified Date:    2017-5-2
** Latest Version:          
** Descriptions:            LED���������
**
**--------------------------------------------------------------------------------------------------------
** Created by:              jsj
** Created date:            2017-5-2
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
#include<string.h>
#include "led_disp_cfg.h"    //����ģ��/��������ͷ�ļ�
#include "led_disp.h"         //����ģ��/����Ӧ��ͷ�ļ�


/*********************************************************************************************************
** Function name:           ledDisplayInit
** Descriptions:            LED�����������ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          0:  �ɹ�
**                          -1: ʧ��
*********************************************************************************************************/
char ledDisplayInit(void)
{
	return 0;
}

unsigned char GucLedDisplayShowBuf[6];  //������ʾ������

static code  unsigned char GucShowTable[][2] = {                      /*  ��������ʾ�ֿ�                    */
    {'0', 0x3f}, {'1', 0x06}, {'2', 0x5b}, {'3', 0x4f}, {'4', 0x66},
    {'5', 0x6d}, {'6', 0x7d}, {'7', 0x07}, {'8', 0x7f}, {'9', 0x6f},
    {'A', 0x77}, {'B', 0x7c}, {'C', 0x39}, {'D', 0x5e}, {'E', 0x79}, {'F', 0x71},
    {'a', 0x77}, {'b', 0x7c}, {'c', 0x39}, {'d', 0x5e}, {'e', 0x79}, {'f', 0x71},
    {'O', 0x3f}, {'R', 0x50}, {'P', 0x73}, {'N', 0x37}, {'-', 0x40},
    {'o', 0x5c}, {'r', 0x50}, {'p', 0x73}, {'n', 0x37}, {' ', 0x00}, {'\011', 0x00},
	{'L',0x38},{'l',0x30},{'V',0x3e},{'H',0x76},
    {0x00, 0x00}
};

static code unsigned char GucTimeShowTable[10]={
	0x3f, 0x06,0x5b,0x4f,0x66,0x6d,0x7d ,0x07,  0x7f, 0x6f
};

/*********************************************************************************************************
** Function name:           ledDisplayScan
** Descriptions:             LED�����ɨ����򣬱����Բ�С��200Hz��Ƶ�ʵ���
** input parameters:        none
** output parameters:       none
** Returned value:         
*********************************************************************************************************/
void ledDisplayScan(void)
{
	static unsigned char ucIndex=0;   //����ɨ��λ��������̬����
	
	/*
         �ر���ʾ
         */
	
	_LED_DIG1_OFF();
	_LED_DIG2_OFF();
	_LED_DIG3_OFF();
	_LED_DIG4_OFF();
	_LED_DIG5_OFF();
	_LED_DIG6_OFF();
	
	/*
       ��ʾucIndexλ��������ʾ�����ַ�����ֵ�͵���ѡλ����I/0��
      */
	_LED_SEG(~GucLedDisplayShowBuf[ucIndex]);
	switch(ucIndex)
	{
		case 0:
			_LED_DIG1_ON();     //���������1
			break;
		case 1:
			_LED_DIG2_ON();     //���������2
			break;
		case 2:
			_LED_DIG3_ON();     //���������3
			break;
		case 3:
			_LED_DIG4_ON();     //���������4
			break;
		case 4:
			_LED_DIG5_ON();     //���������5
			break;
		case 5:
			_LED_DIG6_ON();     //���������6
			break;
		default:
			break;
	}
	
	/*
        ׼����ʾ��һλ
       */
	ucIndex++;
	if(ucIndex>=6)
		ucIndex=0;      //������ص����
}

/*********************************************************************************************************
** Function name:           ledDisplayPuts
** Descriptions:             ����ַ���
** input parameters:     Ҫ������ַ���
** output parameters:       none
** Returned value:        0-------�ɹ���
                                  -1------ʧ��
*********************************************************************************************************/
char ledDisplayPuts(char *pStr)
{
	char i;
	unsigned char j;
	
	if(pStr==NULL)
		return -1;
	
	for(i=0;i<6;i++)
	{
		if(*pStr==0)
		{
			GucLedDisplayShowBuf[i]=0;//��������ַ���β����ʣ�µ�������ó�ȫϨ��
			continue;                       //ָ�벻������ǰ����ѭ��
		}
		
		/*
	          С���㵥������:��С������л�����ϲ���ǰһ���ַ�ȥ
              */
		if(*pStr=='.')
		{
			i--;
			GucLedDisplayShowBuf[i]|=0x80;
		}
		else
		{
			/*
		        �����ַ���
                        */
			for(j=0;GucShowTable[j][0]!=0;j++)
			{
				if(*pStr==(char)GucShowTable[j][0])
				{
				   /*
				     ������ʾ���ַ����뻺����
                                      */
					GucLedDisplayShowBuf[i]=GucShowTable[j][1];
					break;
				}
				
			}
		}
		pStr++;
	}
	return 0;
	
}

/*********************************************************************************************************
** Function name:           ledDisplayDecPuts
** Descriptions:             ������ʮ�����ַ���
** input parameters:     pcStr��Ҫ�������ʮ�����ַ���,ucLen���ַ����ĳ���
** output parameters:       none
** Returned value:        0-------�ɹ���
                                  -1------ʧ��
*********************************************************************************************************/
char ledDisplayDecPuts(char *pStr,unsigned char ucLen)
{
	unsigned char i;
	
	if(pStr==NULL)
		return -1;
	for(i=0;i<ucLen;i++)
	{
		if(pStr[i]>='0'&&pStr[i]<='9')
		GucLedDisplayShowBuf[i]=GucTimeShowTable[pStr[i]-'0'];
	}
	return 0;
}

/*********************************************************************************************************
** Function name:           ledDisplayClr
** Descriptions:             ����
** input parameters:     none
** output parameters:       none
** Returned value:        0-------�ɹ���
                                  -1------ʧ��
*********************************************************************************************************/
char ledDisplayClr(void)
{
	memset(GucLedDisplayShowBuf,0,6);//�ڴ�ռ��ʼ��
	return 0;
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
	 TL1  = (65536 - ((11059200ul / 12) /1000)) % 256;
    TH1  = (65536 - ((11059200ul / 12) / 1000)) / 256;
    ledDisplayScan();
}

/*********************************************************************************************************
** Function name:           time1nit
** Descriptions:             ��ʱ��1��ʼ��
** input parameters:      none
** output parameters:       char
** Returned value:      0------��ʼ���ɹ�
                                 -1----��ʼ��ʧ��
*********************************************************************************************************/
char time1Init()
{
	TMOD = (TMOD & 0x0f) | 0x10;
    TL1  = (65536 - ((11059200ul / 12) /1000)) % 256;
    TH1  = (65536 - ((11059200ul / 12) / 1000)) / 256;
    TR1  = 1;
    ET1  = 1;
	PT1=1;
	return 0;
}

