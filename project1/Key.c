/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Key.c
** Latest modified Date:    2017-5-15
** Latest Version:          
** Descriptions:                 ������̶�̬ɨ������
**
**--------------------------------------------------------------------------------------------------------
** Created by:             LX
** Created date:            2017-5-10
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
#include"./Key_cfg.h"
#include"./Key.h"

/*********************************************************************************************************
** Function name:         KeyNumberGet
** Descriptions:            ������̵�����ɨ��
** input parameters:        none
** output parameters:       none
** Returned value:          -1: �ް�������
**                          	   ��������Ӧ�ļ�λ
*********************************************************************************************************/
char KeyNumberGet(void)
{
	char KeyNumber;//��ֵ
	unsigned char KeySum;  //����Ƿ��а�������
	
	KeyNumber=-1;
	KeySum=0;
	
	__KEY_C1=1;
	__KEY_C2=1;
	__KEY_C3=1;
	__KEY_R1=1;
	__KEY_R2=1;
	__KEY_R3=1;
	__KEY_R4=1;
	
	//ɨ���һ��
	__KEY_R1=0;
	if(__KEY_C1==0)
	{
		KeyNumber=1;
		KeySum++;
	}
	if(__KEY_C2==0)
	{
		KeyNumber=2;
		KeySum++;
	}
	if(__KEY_C3==0)
	{
		KeyNumber=3;
		KeySum++;
	}
	__KEY_R1=1;//��һ��ɨ�����
	
	//ɨ��ڶ���
	__KEY_R2=0;
	if(__KEY_C1==0)
	{
		KeyNumber=4;
		KeySum++;
	}
	if(__KEY_C2==0)
	{
		KeyNumber=5;
		KeySum++;
	}
	if(__KEY_C3==0)
	{
		KeyNumber=6;
		KeySum++;
	}
	__KEY_R2=1;//�ڶ���ɨ�����
	
	//ɨ�������
	__KEY_R3=0;
	if(__KEY_C1==0)
	{
		KeyNumber=7;
		KeySum++;
	}
	if(__KEY_C2==0)
	{
		KeyNumber=8;
		KeySum++;
	}
	if(__KEY_C3==0)
	{
		KeyNumber=9;
		KeySum++;
	}
	__KEY_R3=1;//������ɨ�����
	
	//ɨ�������
	__KEY_R4=0;
	if(__KEY_C1==0)
	{
		KeyNumber=-2;
		KeySum++;
	}
	if(__KEY_C2==0)
	{
		KeyNumber=0;
		KeySum++;
	}
	if(__KEY_C3==0)
	{
		KeyNumber=-3;
		KeySum++;
	}
	__KEY_R4=1;//��һ��ɨ�����
	
	if(KeySum!=1)
	{
		return -1;
	} 
	if(KeyNumber>=0)
		KeyNumber+='0';
	return KeyNumber;
}


