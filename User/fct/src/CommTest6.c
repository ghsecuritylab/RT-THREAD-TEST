/*******************************************************************************
 * File Name:			CommTest6.c 
 * Function Describe:	
 * Relate Module:		�������Э�顣
 * Writer:				Joneming
 * Date:				2011-09-08
 * ReWriter:			
 * Date:				
 *******************************************************************************/
#include "include.h"
///////////////////////
#define TEST_COM6               COM6//����ʹ�õĴ���
//////////////////////////
#define COMTEST6_MAX_REC_LEN    128 //�������ݵĳ���
#define COMTEST6_MAX_SEND_LEN   COM6_MAX_LEN_TX //�������ݵĳ���
///////////////////////
static unsigned char s_ucCommTest6recvBuff[COMTEST6_MAX_REC_LEN+1];     //��������
//static unsigned char s_ucCommTest6resendBuff[COMTEST6_MAX_SEND_LEN+1];  //���ͻ���
/////////////////////////
static ST_COMM s_stCommTest6;
//////////////////////////
/****************************************************/
/*                                                  */
/* Local Definitions and macros                     */
/*                                                  */
/****************************************************/
/*************************************************************
** ��������: CommTest6_SendData
** ��������: ��������
** ��ڲ���: pBufferԴ����,BufferLen���ݳ���
** ���ڲ���: ��
** ���ز���: 0:�ɹ���1:ʧ��,0xff:�������泤��
** ȫ�ֱ���: ��
** ����ģ��: ��
*************************************************************/
unsigned char CommTest6_SendData(unsigned char *pBuffer,unsigned short datalen)
{
    return COMM_SendData(TEST_COM6,pBuffer,datalen);
}
/*************************************************************OK
** ��������: CommTest6_ProtocolParse
** ��������: Э�����
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest6_ProtocolParse(unsigned char *pBuffer,unsigned short datalen)
{
    unsigned short i;
    for(i=0; i<datalen; i++)
    {
        if(0x0d==pBuffer[i])
        {
            CommTest6_SendData(pBuffer,i+1);
            break;
        }
    }
}
/*************************************************************OK
** ��������: CommTest6_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :50�������1��
*************************************************************/
void CommTest6_CheckReadData(void)
{
    unsigned short datalen;
    datalen=COMM_ReadData(TEST_COM6,&s_stCommTest6.recvBuff[s_stCommTest6.recvlen],COMTEST6_MAX_REC_LEN-s_stCommTest6.recvlen);
    ///////////////////////////////
    s_stCommTest6.recvlen += datalen;
    ///////////////////////////////////
    if(0 == datalen)////��������ݳ���Ϊ0//////////    
    {
        if(s_stCommTest6.recvlen)
        {
            s_stCommTest6.recvfreeCnt++;
            ////////////////////////////////
            if(s_stCommTest6.recvfreeCnt >1)//�������ε���
            {
                CommTest6_ProtocolParse(s_stCommTest6.recvBuff,s_stCommTest6.recvlen);
                s_stCommTest6.recvlen       = 0;
                s_stCommTest6.recvfreeCnt   = 0;//
            }
        }
    }
    else//////////////////
    if(s_stCommTest6.recvlen+10>COMTEST6_MAX_REC_LEN)//����������ʱ��
    {
        CommTest6_ProtocolParse(s_stCommTest6.recvBuff,s_stCommTest6.recvlen);
        s_stCommTest6.recvlen       = 0;
        s_stCommTest6.recvfreeCnt   = 0;
    }
    else//////////////////
    {
        s_stCommTest6.recvfreeCnt = 0;
    }
}
/*************************************************************OK
** ��������: CommTest6_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :50�������1��
*************************************************************/
FunctionalState CommTest6_TimeTask(void)
{
    CommTest6_CheckReadData();
    ////////////////////
    //LZM_PublicTimerHandler(s_stCMTEST6Timer,CMTEST6_TIMERS_MAX);    
    //////////////////////
    return ENABLE;
}
/*************************************************************OK
** ��������: CommTest6RecvEnable
** ��������: 
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest6RecvEnable(void)
{
    GpioOutOff(CAM_RD);
    Delay_uS(0x1000);
}
/*************************************************************OK
** ��������: CommTest6SendEnable
** ��������: 
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest6SendEnable(void)
{
    GpioOutOn(CAM_RD);
    Delay_uS(0x1000);
}
/*************************************************************OK
** ��������: CommTest6Init
** ��������: //���ڳ�ʼ��
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest6Init(void)
{
    //LZM_PublicKillTimerAll(s_stCMTEST6Timer,CMTEST6_TIMERS_MAX); 
    //////////////////
    s_stCommTest6.recvlen       = 0;
    s_stCommTest6.resendlen     = 0;
    s_stCommTest6.resendCnt     = 0;
    s_stCommTest6.recvfreeCnt   = 0;
    s_stCommTest6.recvBuff      = s_ucCommTest6recvBuff;
    //s_stCommTest6.resendBuff    = s_ucCommTest6resendBuff;
    ////////////////////
    COMM_Initialize(TEST_COM6,9600);
    ////////////////////
    GpioOutInit(CAM_RD);
    GpioOutInit(CAM_PWR);
    GpioOutOn(CAM_PWR);
    COMM_CtrlEnableInitialize(TEST_COM6,CommTest6RecvEnable,CommTest6SendEnable);
    SetTimerTask(TIME_COM6_TEST, LZM_TIME_BASE); 
    ////////////////////////    
}
/*******************************************************************************
 *                             end of module
 *******************************************************************************/

