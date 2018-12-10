/*******************************************************************************
 * File Name:			CommTest5.c 
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
#define TEST_COM5               COM5//����ʹ�õĴ���
//////////////////////////
#define COMTEST5_MAX_REC_LEN    128 //�������ݵĳ���
#define COMTEST5_MAX_SEND_LEN   COM5_MAX_LEN_TX //�������ݵĳ���
///////////////////////
static unsigned char s_ucCommTest5recvBuff[COMTEST5_MAX_REC_LEN+1];     //��������
//static unsigned char s_ucCommTest5resendBuff[COMTEST5_MAX_SEND_LEN+1];  //���ͻ���
/////////////////////////
static ST_COMM s_stCommTest5;
//////////////////////////
/****************************************************/
/*                                                  */
/* Local Definitions and macros                     */
/*                                                  */
/****************************************************/
/*************************************************************
** ��������: CommTest5_SendData
** ��������: ��������
** ��ڲ���: pBufferԴ����,BufferLen���ݳ���
** ���ڲ���: ��
** ���ز���: 0:�ɹ���1:ʧ��,0xff:�������泤��
** ȫ�ֱ���: ��
** ����ģ��: ��
*************************************************************/
rt_size_t CommTest5_SendData(unsigned char *pBuffer,unsigned short datalen)
{
    return stm32_serial5_write(0,pBuffer,datalen);
}
/*************************************************************OK
** ��������: CommTest5_ProtocolParse
** ��������: Э�����
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest5_ProtocolParse(unsigned char *pBuffer,unsigned short datalen)
{
	App_DisposeGprsRecvData(pBuffer,datalen);
}
/*************************************************************OK
** ��������: CommTest5_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :50�������1��
*************************************************************/
void CommTest5_CheckReadData(void)
{
    unsigned short datalen;
    datalen=stm32_serial5_read(0,&s_stCommTest5.recvBuff[s_stCommTest5.recvlen],COMTEST5_MAX_REC_LEN-s_stCommTest5.recvlen);
    ///////////////////////////////
    s_stCommTest5.recvlen += datalen;
    ///////////////////////////////////
    if(0 == datalen)////��������ݳ���Ϊ0//////////    
    {
        if(s_stCommTest5.recvlen)
        {
            s_stCommTest5.recvfreeCnt++;
            ////////////////////////////////
            if(s_stCommTest5.recvfreeCnt >1)//�������ε���
            {
                CommTest5_ProtocolParse(s_stCommTest5.recvBuff,s_stCommTest5.recvlen);
                s_stCommTest5.recvlen       = 0;
                s_stCommTest5.recvfreeCnt   = 0;//
            }
        }
    }
    else//////////////////
    if(s_stCommTest5.recvlen+10>COMTEST5_MAX_REC_LEN)//����������ʱ��
    {
        CommTest5_ProtocolParse(s_stCommTest5.recvBuff,s_stCommTest5.recvlen);
        s_stCommTest5.recvlen       = 0;
        s_stCommTest5.recvfreeCnt   = 0;
    }
    else//////////////////
    {
        s_stCommTest5.recvfreeCnt = 0;
    }
}
/*************************************************************OK
** ��������: CommTest5_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :50�������1��
*************************************************************/
FunctionalState CommTest5_TimeTask(void)
{
    CommTest5_CheckReadData();
    ////////////////////
    //LZM_PublicTimerHandler(s_stCMTEST5Timer,CMTEST5_TIMERS_MAX);    
    //////////////////////
    return ENABLE;
}
/*************************************************************OK
** ��������: CommTest5Init
** ��������: //���ڳ�ʼ��
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest5Init(void)
{
    //LZM_PublicKillTimerAll(s_stCMTEST5Timer,CMTEST5_TIMERS_MAX); 
    //////////////////
    s_stCommTest5.recvlen       = 0;
    s_stCommTest5.resendlen     = 0;
    s_stCommTest5.resendCnt     = 0;
    s_stCommTest5.recvfreeCnt   = 0;
    s_stCommTest5.recvBuff      = s_ucCommTest5recvBuff;
    //s_stCommTest5.resendBuff    = s_ucCommTest5resendBuff;
    ////////////////////
    //COMM_Initialize(TEST_COM5,115200);
		gpio_out_on(PIN_NO_GSM_PWC);
		gpio_out_on(PIN_NO_GSM_ON);
    ////////////////////    
    SetTimerTask(TIME_COM5_TEST, LZM_TIME_BASE); 
    ////////////////////////    
}
/*******************************************************************************
 *                             end of module
 *******************************************************************************/

