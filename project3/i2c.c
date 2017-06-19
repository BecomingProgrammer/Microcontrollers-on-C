/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:              i2c.c
** Latest modified Date:    2017-6-13
** Latest Version:          
** Descriptions:           i2c����ʵ���ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              jsj
** Created date:            2017-6-13
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
#include"i2c.h"
#include"i2c_cfg.h"


/*********************************************************************************************************
** Function name:           i2cBitSend
** Descriptions:            i2c����һλ����
** input parameters:        ucData��Ҫ���͵�����
** output parameters:       none
** Returned value:          none
**            
*********************************************************************************************************/
static void i2cBitSend(unsigned char ucData)
{
	if(ucData&0x80)
	  I2C_SDA=1;
	else
		I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cBitReceive
** Descriptions:            i2c����һλ����
** input parameters:        none
** output parameters:       none
** Returned value:          ucReturnValue�����յ�һλ����
**                   
*********************************************************************************************************/
static unsigned char i2cBitReceive(void)
{
	unsigned char ucReturnValue;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	ucReturnValue=I2C_SDA;
	I2C_SCL=0;
	return ucReturnValue;
}

/*********************************************************************************************************
** Function name:           i2cStartSend
** Descriptions:            i2c��ʼ�ź�
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                          
*********************************************************************************************************/
static void i2cStartSend(void)
{
	I2C_DELAY();
	I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cStopSend
** Descriptions:            i2cֹͣ�ź�
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                          
*********************************************************************************************************/
static void i2cStopSend(void)
{
	I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	I2C_SDA=1;
}

/*********************************************************************************************************
** Function name:           i2cRestartSend
** Descriptions:            i2c��������
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                          
*********************************************************************************************************/
static void i2cRestartSend(void)
{
	I2C_SDA=1;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cSendAck
** Descriptions:            i2c����Ӧ���ź�
** input parameters:        none
** output parameters:       none
** Returned value:       none
**                          
*********************************************************************************************************/
static void i2cSendAck(void)
{
	I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
    I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cSendInvailAck
** Descriptions:            i2c���ͷ�Ӧ���ź�
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                          
*********************************************************************************************************/
static void i2cSendInvailAck(void)
{
	I2C_SDA=1;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
    I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cReceiveAck
** Descriptions:            i2c����Ӧ���ź�
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                         
*********************************************************************************************************/
static char i2cReceiveAck(void)
{
	I2C_SDA=1;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	if(I2C_SDA==1)
	{
		I2C_SCL=0;
		return 0;
	}
	I2C_SCL=0;
	return 1;
		
}



/*********************************************************************************************************
** Function name:           i2cByteSend
** Descriptions:            i2c����һ�ֽ�����
** input parameters:        ucData��Ҫ���͵�����
** output parameters:       none
** Returned value:        none
**                          
*********************************************************************************************************/
static void i2cByteSend(unsigned char ucData)
{
	unsigned char i=8;
	
	while(i-->0 )
	{
		i2cBitSend(ucData);
		ucData=ucData<<1;
	}
		
		
}

/*********************************************************************************************************
** Function name:           i2cByteReceive
** Descriptions:            i2c����һ�ֽ�����
** input parameters:        none
** output parameters:       none
** Returned value:        ucReturn�����յ�����
**                          
*********************************************************************************************************/
static unsigned char i2cByteReceive(void)
{
	unsigned char ucReturn=0;
	unsigned char i=8;
	I2C_SDA=1;
	while(i-->0)
	{
		ucReturn=ucReturn<<1;
		ucReturn=ucReturn+i2cBitReceive();
	}
	
	return ucReturn;
		
		
}

/*********************************************************************************************************
** Function name:           i2cInit
** Descriptions:            ��ʼ��i2c
** input parameters:        none
** output parameters:       none
** Returned value:          0:  �ɹ�
**                          -1: ʧ��
*********************************************************************************************************/
char i2cInit(void)
{
	I2C_SCL=0;
	i2cStopSend();
	return 0;
	
}

/*********************************************************************************************************
** Function name:           i2cWrite
** Descriptions:            i2cд����
** input parameters:         ucAdd:       �ӻ���ַ
**                          uiResitAdd:    �Ĵ�����ַ
**                          ucResitLength: �Ĵ�����ַ���ȣ��ֽ�Ϊ��λ��
**                          ucData:      Ҫд�������
**                          ucDataLen:    Ҫд������ݳ��ȣ��ֽ�Ϊ��λ��
** output parameters:       none
** Returned value:          �Ѿ��ɹ�д����ֽ���
*********************************************************************************************************/
 unsigned char i2cWrite(unsigned char ucAdd,
                                unsigned int  uiResitAdd,
                                unsigned char ucResitLength,
                                unsigned char *ucData,
                                unsigned char ucDataLen)
{
		unsigned char i;
		if(ucDataLen==0||ucData==0)
			return 0;
		i=ucDataLen;
		i2cStartSend();
		i2cByteSend(ucAdd&0xfe);
		
		if(i2cReceiveAck())
		{
			while(ucResitLength>0)
			{
				
				i2cByteSend(uiResitAdd);
				if(!i2cReceiveAck())
					break;
				ucResitLength--;
				uiResitAdd=uiResitAdd>>8;
			}
			
			if(ucResitLength==0)
			{
				do{
					
					i2cByteSend(*ucData++);
					if(!i2cReceiveAck())
						break;
				}while(--i!=0);
			}
			
		}
		i2cStopSend();
		return ucDataLen-i;
}


/*********************************************************************************************************
** Function name:           i2cRead
** Descriptions:            i2c������
** input parameters:         ucAdd:       �ӻ���ַ
**                          uiResitAdd:    �Ĵ�����ַ
**                          ucResitLength: �Ĵ�����ַ���ȣ��ֽ�Ϊ��λ��
**                          ucData:      Ҫ����������
**                          ucDataLen:    Ҫ�������ݳ��ȣ��ֽ�Ϊ��λ��
** output parameters:       none
** Returned value:          �Ѿ��ɹ���������ֽ���
*********************************************************************************************************/
 unsigned char i2cRead(unsigned char ucAdd,
                               unsigned int  uiResitAdd,
                               unsigned char ucResitLength,
                               unsigned char *ucData,
                               unsigned char ucDataLen)
{

	unsigned char i;
	if(ucDataLen==0||ucData==0)
		return 0;
	i2cStartSend();
	i2cByteSend(ucAdd&0xfe);
	
	if(i2cReceiveAck())
	{
		while(ucResitLength>0)
		{
			i2cByteSend(uiResitAdd);
			if(!i2cReceiveAck())
				break;
			ucResitLength--;
			uiResitAdd==uiResitAdd>>8;
		}
		if(ucResitLength==0)
		{
			i2cRestartSend();
			i2cByteSend(ucAdd|0x01);
			if(i2cReceiveAck())
			{
				i=ucDataLen-1;
				while(i--!=0)
				{
					*ucData++=i2cByteReceive();
					i2cSendAck();
				}
				*ucData=i2cByteReceive();
				i2cSendInvailAck();
			}
		}
	}
	else{
		ucDataLen=0;
	}
	i2cStopSend();
	return ucDataLen;
}
