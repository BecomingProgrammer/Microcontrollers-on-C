/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:              i2c.h
** Latest modified Date:    2017-6-13
** Latest Version:          
** Descriptions:           i2c����ͷ�ļ�
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

#ifndef I2C_H_
#define I2C_H_

/*********************************************************************************************************
** Function name:           i2cInit
** Descriptions:            ��ʼ��i2c
** input parameters:        none
** output parameters:       none
** Returned value:          0:  �ɹ�
**                          -1: ʧ��
*********************************************************************************************************/
extern char i2cInit(void);

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
extern unsigned char i2cWrite(unsigned char ucAdd,
                                unsigned int  uiResitAdd,
                                unsigned char ucResitLength,
                                unsigned char *ucData,
                                unsigned char ucDataLen);


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
extern unsigned char i2cRead(unsigned char ucAdd,
                               unsigned int  uiResitAdd,
                               unsigned char ucResitLength,
                               unsigned char *ucData,
                               unsigned char ucDataLen);



#endif


