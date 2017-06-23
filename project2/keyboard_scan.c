/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               keyboard_scan.c
** Latest modified Date:    2017-5-9
** Latest Version:          
** Descriptions:            ��������ͷ�ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              jsj
** Created date:            2017-5-9
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
#include<8051.h>
#include"./keyboard_scan.h"
#include"./keyboard_scan_cfg.h"


/*********************************************************************************************************
** Function name:           keyboardInit
** Descriptions:             ���̳�ʼ��
** input parameters:      none
** output parameters:       char
** Returned value:      0------��ʼ���ɹ�
                                 -1----��ʼ��ʧ��
*********************************************************************************************************/

 char keyboardInit()
 {
	 return 0;
 }


/*********************************************************************************************************
** Function name:           allKeyCheck
** Descriptions:             ����а����Ƿ񱻰���
** input parameters:      none
** output parameters:       none
** Returned value:        ��key��-------�а���key����
                                  -1------�ް���
*********************************************************************************************************/
char allKeyCheck()
{
	char cOut=-1;
	unsigned char i,j;
	for(i=0;i<4;i++)
	{
		KEYBOARD_KR1_PIN=1;
		KEYBOARD_KR2_PIN=1;
		KEYBOARD_KR3_PIN=1;
		KEYBOARD_KR4_PIN=1;
		KEYBOARD_KC1_PIN=1;
		KEYBOARD_KC2_PIN=1;
		KEYBOARD_KC3_PIN=1;
		switch(i)
		{
			case 0:
				KEYBOARD_KR1_PIN=0;
				break;
			case 1:
				KEYBOARD_KR2_PIN=0;
				break;
			case 2:
				KEYBOARD_KR3_PIN=0;
				break;
			case 3:
				KEYBOARD_KR4_PIN=0;
				break;
		}
		for(j=0;j<3;j++)
		{
			KEYBOARD_NC_PIN=1;
			switch(j)
			{
				case 0:
					if(KEYBOARD_KC1_PIN==0)
					KEYBOARD_NC_PIN=0;
					break;
				case 1:
					if(KEYBOARD_KC2_PIN==0)
					KEYBOARD_NC_PIN=0;
					break;
				case 2:
					if(KEYBOARD_KC3_PIN==0)
					KEYBOARD_NC_PIN=0;
					break;
			}
			if(KEYBOARD_NC_PIN==0)
			{
				cOut=i*3+j+'1';
			}
		}
	}
	if(cOut==('0'+10)||cOut==('0'+12))
		cOut=-1;
	if(cOut==('0'+11))
		cOut='0';
	return cOut;
}

/*********************************************************************************************************
** Function name:           throwError
** Descriptions:             ����
** input parameters:      none
** output parameters:       none
** Returned value:        none
*********************************************************************************************************/

void throwError()
{
	unsigned char uiNumber=100;
	unsigned char i;
	do{
		i=46;
		do{
		}while(--i!=0);
	}while(--uiNumber!=0);
}

/*********************************************************************************************************
** Function name:           isExsitPushKey
** Descriptions:             �Ƿ���ڰ��µİ������Ѿ�����
** input parameters:      none
** output parameters:       none
** Returned value:        ��key��-------�а���key����
                                  -1------�ް���
*********************************************************************************************************/
char isExsitPushKey()
{
	char cKey;
	if((cKey=allKeyCheck())>0)
	{
		throwError();
		if(cKey==allKeyCheck())
			;
		else
			cKey=-1;
	}
	return cKey;
}

/*********************************************************************************************************
** Function name:           isExsitRealaseKey
** Descriptions:             �Ƿ���ڰ��µİ����Ѿ��ͷţ��Ѿ�����
** input parameters:      none
** output parameters:       none
** Returned value:        0-------���ͷ�
                                  -1------���ͷ�
*********************************************************************************************************/
char isExsitRealaseKey()
{
	if(allKeyCheck()<0)
	{
		throwError();
		if(allKeyCheck()<0)
		   return 0;
	}
	return -1;
	
}

