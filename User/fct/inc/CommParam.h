/*******************************************************************************
 * File Name:			CommParam.h 
 * Function Describe:	
 * Relate Module:		
 * Writer:				joneming
 * Date:				2012-09-08
 * Rewriter:
 * Date:		
 *******************************************************************************/
#ifndef _COMM_PARAM_H_
#define _COMM_PARAM_H_  

///////////////////////////////
/*************************************************************
** ��������: CommParamInit
** ��������: //���ڳ�ʼ��
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommParamInit(void);
/*************************************************************
** ��������: CommParam_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :20�������1��
*************************************************************/
FunctionalState CommParam_TimeTask(void);
/*************************************************************
** ��������: CommParam_SendData
** ��������: ��������
** ��ڲ���: pBufferԴ����,BufferLen���ݳ���
** ���ڲ���: ��
** ���ز���: 0:�ɹ���1:�ȴ��ط�,2:ʧ��,0xff:�������泤��
** ȫ�ֱ���: ��
** ����ģ��: ��
*************************************************************/
unsigned char CommParam_SendData(unsigned char *pBuffer, unsigned short BufferLen);
/*************************************************************OK
** ��������: CommParam_CheckReadData
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :50�������1��
*************************************************************/
void CommParam_CheckReadData(void);

#endif//_CommParam_H_
/*******************************************************************************
 *                             end of module
 *******************************************************************************/