/*******************************************************************************
 * File Name:			CommParam.c 
 * Function Describe:	
 * Relate Module:		�������Э�顣
 * Writer:				Joneming
 * Date:				2011-09-08
 * ReWriter:			
 * Date:				
 *******************************************************************************/
#include "include.h"
#include "usart.h"
#include <rthw.h>
#include <rtthread.h>

///////////////////////
#define PARAM_COM               COM1//����ʹ�õĴ���
//////////////////////////
#define COMPARAM_MAX_REC_LEN    128 //�������ݵĳ���
#define COMPARAM_MAX_SEND_LEN   COM1_MAX_LEN_TX //�������ݵĳ���
///////////////////////
static unsigned char s_ucCommrecvBuff[COMPARAM_MAX_REC_LEN+1];     //��������
static unsigned char s_ucCommresendBuff[COMPARAM_MAX_SEND_LEN+1];  //���ͻ���
/////////////////////////
static ST_COMM s_stCommParam;
//////////////////////////
enum 
{
    CPARAM_TIMER_RESEND, //    
    CPARAM_TIMERS_MAX
}E_COM_PARAMTIME;
//static LZM_TIMER s_stCParamTimer[CPARAM_TIMERS_MAX];
/****************************************************/
/*                                                  */
/* Local Definitions and macros                     */
/*                                                  */
/****************************************************/
/*************************************************************
** ��������: CommParam_StartSendData
** ��������: ��������
** ��ڲ���: pBufferԴ����,BufferLen���ݳ���
** ���ڲ���: ��
** ���ز���: 0:�ɹ���1:ʧ��,0xff:�������泤��
** ȫ�ֱ���: ��
** ����ģ��: ��
*************************************************************/
rt_size_t CommParam_StartSendData(unsigned char *pBuffer,unsigned short datalen)
{
	return stm32_serial1_write(0,pBuffer,datalen);
}
/************************************************************
** ��������: CommParam_ResendData
** ��������: �ط�ʱ�䵽��ִ���ط�����
             
** ��ڲ���:
** ���ڲ���:
************************************************************/ 
ErrorStatus CommParam_ResendData(void)
{
    if(0 == CommParam_StartSendData(s_stCommParam.resendBuff,s_stCommParam.resendlen))//���ͳɹ�
    {
        s_stCommParam.resendCnt = 0;
        return SUCCESS;
    }
    /////////////////////////
    if(s_stCommParam.resendCnt)//�����ط�
    {
        s_stCommParam.resendCnt--;
        Timer10msStart(TIMER_10MS_ID_COMM_RESEND,15,TIMER_MODE_ONCE,CommParam_ResendData);
				return ERROR;
    }  
		return SUCCESS;
}
/*************************************************************
** ��������: CommParam_SendData
** ��������: ��������
** ��ڲ���: pBufferԴ����,BufferLen���ݳ���
** ���ڲ���: ��
** ���ز���: 0:�ɹ���1:�ȴ��ط�,2:ʧ��,0xff:�������泤��
** ȫ�ֱ���: ��
** ����ģ��: ��
*************************************************************/
unsigned char CommParam_SendData(unsigned char *pBuffer,unsigned short datalen)
{
    if(datalen>COMPARAM_MAX_SEND_LEN)return 0xff;//��������,ֱ�ӷ���
    //////////////////
    if(0 == CommParam_StartSendData(pBuffer,datalen))return 0;//���ͳɹ�
    //////ʧ��//////////////////
    if(0==s_stCommParam.resendCnt)
    {
        s_stCommParam.resendlen = datalen;
        memcpy(&s_stCommParam.resendBuff,pBuffer,s_stCommParam.resendlen);
        s_stCommParam.resendCnt = 4;//�ط��ʹ���
        //LZM_PublicSetOnceTimer(&s_stCParamTimer[CPARAM_TIMER_RESEND], PUBLICSECS(0.15), CommParam_ResendData); 
				Timer10msStart(TIMER_10MS_ID_COMM_RESEND,15,TIMER_MODE_ONCE,CommParam_ResendData);
        return 1;//�ȴ��ط�
    }
    else
    if((s_stCommParam.resendlen+datalen)<COMPARAM_MAX_SEND_LEN)
    {
        memcpy(&s_stCommParam.resendBuff[s_stCommParam.resendlen],pBuffer,datalen);
        s_stCommParam.resendlen += datalen;
        return 1;//�ȴ��ط�
    }
    else//
    {
        return 2;//ʧ��
    }
}

/*************************************************************OK
** ��������: CommParam_ProtocolParse
** ��������: Э�����
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommParam_ProtocolParse(unsigned char *pBuffer,unsigned short datalen)
{
    FCT_AppDisposeDebugRecvData(pBuffer,datalen);
}
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
void CommParam_CheckReadData(void)
{
		unsigned short datalen;

		datalen=stm32_serial1_read(0,&s_stCommParam.recvBuff[s_stCommParam.recvlen],COMPARAM_MAX_REC_LEN-s_stCommParam.recvlen);
		///////////////////////////////
		s_stCommParam.recvlen += datalen;
		///////////////////////////////////
		if(0 == datalen)////��������ݳ���Ϊ0////////// 	 
		{
				if(s_stCommParam.recvlen)
				{
						s_stCommParam.recvfreeCnt++;
						////////////////////////////////
						if(s_stCommParam.recvfreeCnt >1)//�������ε���
						{
								CommParam_ProtocolParse(s_stCommParam.recvBuff,s_stCommParam.recvlen);
								s_stCommParam.recvlen 			= 0;
								s_stCommParam.recvfreeCnt 	= 0;//
						}
				}
		}
		else//////////////////
		if(s_stCommParam.recvlen+10>COMPARAM_MAX_REC_LEN)//����������ʱ��
		{
				CommParam_ProtocolParse(s_stCommParam.recvBuff,s_stCommParam.recvlen);
				s_stCommParam.recvlen 			= 0;
				s_stCommParam.recvfreeCnt 	= 0;
		}
		else//////////////////
		{
				s_stCommParam.recvfreeCnt = 0;
		}
}

/*************************************************************OK
** ��������: CommParam_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :50�������1��
*************************************************************/
FunctionalState CommParam_TimeTask(void)
{
    CommParam_CheckReadData();
    ////////////////////
    //LZM_PublicTimerHandler(s_stCParamTimer,CPARAM_TIMERS_MAX);    
    //////////////////////
    return ENABLE;
}
/*************************************************************OK
** ��������: CommParamInit
** ��������: //���ڳ�ʼ��
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommParamInit(void)
{
    s_stCommParam.recvlen       = 0;
    s_stCommParam.resendlen     = 0;
    s_stCommParam.resendCnt     = 0;
    s_stCommParam.recvfreeCnt   = 0;
    s_stCommParam.recvBuff      = s_ucCommrecvBuff;
    s_stCommParam.resendBuff    = s_ucCommresendBuff;
    ////////////////////
    //COMM_Initialize(PARAM_COM,115200);
		////////////////////    
    SetTimerTask(TIME_COM_PARAM, LZM_TIME_BASE); 
}
/*******************************************************************************
 *                             end of module
 *******************************************************************************/

