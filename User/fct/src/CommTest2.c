/*******************************************************************************
 * File Name:			CommTest2.c 
 * Function Describe:	
 * Relate Module:		�������Э�顣
 * Writer:				Joneming
 * Date:				2011-09-08
 * ReWriter:			
 * Date:				
 *******************************************************************************/
#include "include.h"
///////////////////////
#define TEST_COM2               COM2//����ʹ�õĴ���
//////////////////////////
#define COMTEST2_MAX_REC_LEN    128 //�������ݵĳ���
#define COMTEST2_MAX_SEND_LEN   COM2_MAX_LEN_TX //�������ݵĳ���
///////////////////////
static unsigned char s_ucCommTest2recvBuff[COMTEST2_MAX_REC_LEN+1];     //��������
//static unsigned char s_ucCommTest2resendBuff[COMTEST2_MAX_SEND_LEN+1];  //���ͻ���
/////////////////////////
static ST_COMM s_stCommTest2;
//////////////////////////
/****************************************************/
/*                                                  */
/* Local Definitions and macros                     */
/*                                                  */
/****************************************************/
/*************************************************************
** ��������: CommTest2_SendData
** ��������: ��������
** ��ڲ���: pBufferԴ����,BufferLen���ݳ���
** ���ڲ���: ��
** ���ز���: 0:�ɹ���1:ʧ��,0xff:�������泤��
** ȫ�ֱ���: ��
** ����ģ��: ��
*************************************************************/
unsigned char CommTest2_SendData(unsigned char *pBuffer,unsigned short datalen)
{
    return COMM_SendData(TEST_COM2,pBuffer,datalen);
}
/*************************************************************OK
** ��������: CommTest2_ProtocolParse
** ��������: Э�����
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest2_ProtocolParse(unsigned char *pBuffer,unsigned short datalen)
{
    App_DisposeGprsRecvData(pBuffer,datalen);
}
/*************************************************************OK
** ��������: CommTest2_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :20�������1��
*************************************************************/
void CommTest2_CheckReadData(void)
{
    unsigned short datalen;
    datalen=COMM_ReadData(TEST_COM2,&s_stCommTest2.recvBuff[s_stCommTest2.recvlen],COMTEST2_MAX_REC_LEN-s_stCommTest2.recvlen);
    ///////////////////////////////
    s_stCommTest2.recvlen += datalen;
    ///////////////////////////////////
    if(0 == datalen)////��������ݳ���Ϊ0//////////    
    {
        if(s_stCommTest2.recvlen)
        {
            s_stCommTest2.recvfreeCnt++;
            ////////////////////////////////
            if(s_stCommTest2.recvfreeCnt >1)//�������ε���
            {
                CommTest2_ProtocolParse(s_stCommTest2.recvBuff,s_stCommTest2.recvlen);
                s_stCommTest2.recvlen       = 0;
                s_stCommTest2.recvfreeCnt   = 0;//
            }
        }
    }
    else//////////////////
    if(s_stCommTest2.recvlen+10>COMTEST2_MAX_REC_LEN)//����������ʱ��
    {
        CommTest2_ProtocolParse(s_stCommTest2.recvBuff,s_stCommTest2.recvlen);
        s_stCommTest2.recvlen       = 0;
        s_stCommTest2.recvfreeCnt   = 0;
    }
    else//////////////////
    {
        s_stCommTest2.recvfreeCnt = 0;
    }
}
/*************************************************************OK
** ��������: CommTest2_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :20�������1��
*************************************************************/
FunctionalState CommTest2_TimeTask(void)
{
    CommTest2_CheckReadData();
    ////////////////////
    //LZM_PublicTimerHandler(s_stCMTEST2Timer,CMTEST2_TIMERS_MAX);    
    //////////////////////
    return ENABLE;
}
/*************************************************************OK
** ��������: CommTest2Init
** ��������: //���ڳ�ʼ��
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest2Init(void)
{
    //LZM_PublicKillTimerAll(s_stCMTEST2Timer,CMTEST2_TIMERS_MAX); 
    //////////////////
    s_stCommTest2.recvlen       = 0;
    s_stCommTest2.resendlen     = 0;
    s_stCommTest2.resendCnt     = 0;
    s_stCommTest2.recvfreeCnt   = 0;
    s_stCommTest2.recvBuff      = s_ucCommTest2recvBuff;
    //s_stCommTest2.resendBuff    = s_ucCommTest2resendBuff;
    ////////////////////
    COMM_Initialize(TEST_COM2,115200);
    ////////////////////    
//    SetTimerTask(TIME_COM2_TEST, LZM_TIME_BASE); 
    ////////////////////////    
}
/*******************************************************************************
 *                             end of module
 *******************************************************************************/

