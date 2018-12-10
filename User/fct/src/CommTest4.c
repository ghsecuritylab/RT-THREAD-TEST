/*******************************************************************************
 * File Name:			CommTest4.c 
 * Function Describe:	
 * Relate Module:		�������Э�顣
 * Writer:				Joneming
 * Date:				2011-09-08
 * ReWriter:			
 * Date:				
 *******************************************************************************/
#include "include.h"
#include "board.h"
///////////////////////
#define TEST_COM4               COM4//����ʹ�õĴ���
//////////////////////////
#define COMTEST4_MAX_REC_LEN    128 //�������ݵĳ���
#define COMTEST4_MAX_SEND_LEN   COM4_MAX_LEN_TX //�������ݵĳ���
///////////////////////
static unsigned char s_ucCommTest4recvBuff[COMTEST4_MAX_REC_LEN+1];     //��������
//static unsigned char s_ucCommTest4resendBuff[COMTEST4_MAX_SEND_LEN+1];  //���ͻ���
/////////////////////////
static ST_COMM s_stCommTest4;
//////////////////////////
/****************************************************/
/*                                                  */
/* Local Definitions and macros                     */
/*                                                  */
/****************************************************/
/*************************************************************
** ��������: CommTest4_SendData
** ��������: ��������
** ��ڲ���: pBufferԴ����,BufferLen���ݳ���
** ���ڲ���: ��
** ���ز���: 0:�ɹ���1:ʧ��,0xff:�������泤��
** ȫ�ֱ���: ��
** ����ģ��: ��
*************************************************************/
unsigned char CommTest4_SendData(unsigned char *pBuffer,unsigned short datalen)
{
    return COMM_SendData(TEST_COM4,pBuffer,datalen);
}
/*************************************************************OK
** ��������: CommTest4_ProtocolParse
** ��������: Э�����
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest4_ProtocolParse(unsigned char *pBuffer,unsigned short datalen)
{
    unsigned short i;
    for(i=0; i<datalen; i++)
    {
        if(0x0d==pBuffer[i])
        {
            CommTest4_SendData(pBuffer,i+1);
            break;
        }
    }
}
/*************************************************************OK
** ��������: CommTest4_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :50�������1��
*************************************************************/
void CommTest4_CheckReadData(void)
{
    unsigned short datalen;
    datalen=COMM_ReadData(TEST_COM4,&s_stCommTest4.recvBuff[s_stCommTest4.recvlen],COMTEST4_MAX_REC_LEN-s_stCommTest4.recvlen);
    ///////////////////////////////
    s_stCommTest4.recvlen += datalen;
    ///////////////////////////////////
    if(0 == datalen)////��������ݳ���Ϊ0//////////    
    {
        if(s_stCommTest4.recvlen)
        {
            s_stCommTest4.recvfreeCnt++;
            ////////////////////////////////
            if(s_stCommTest4.recvfreeCnt >1)//�������ε���
            {
                CommTest4_ProtocolParse(s_stCommTest4.recvBuff,s_stCommTest4.recvlen);
                s_stCommTest4.recvlen       = 0;
                s_stCommTest4.recvfreeCnt   = 0;//
            }
        }
    }
    else//////////////////
    if(s_stCommTest4.recvlen+10>COMTEST4_MAX_REC_LEN)//����������ʱ��
    {
        CommTest4_ProtocolParse(s_stCommTest4.recvBuff,s_stCommTest4.recvlen);
        s_stCommTest4.recvlen       = 0;
        s_stCommTest4.recvfreeCnt   = 0;
    }
    else//////////////////
    {
        s_stCommTest4.recvfreeCnt = 0;
    }
}
/*************************************************************OK
** ��������: CommTest4_TimeTask
** ��������: ���ڽ������ݴ���ʱ������ӿ�
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
**  �� ע  :50�������1��
*************************************************************/
FunctionalState CommTest4_TimeTask(void)
{
    CommTest4_CheckReadData();
    return ENABLE;
}
/*************************************************************OK
** ��������: CommTest4RecvEnable
** ��������: 
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest4RecvEnable(void)
{
    gpio_out_on(PIN_NO_GPS_CTR);                                //��ʼ�ر�GPS��Դ    
    rt_hw_us_delay(0x1000);
}
/*************************************************************OK
** ��������: CommTest4SendEnable
** ��������: 
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest4SendEnable(void)
{
	gpio_out_off(PIN_NO_GPS_CTR);                                //��ʼ����GPS��Դ
    rt_hw_us_delay(0x1000);
}
/*************************************************************OK
** ��������: CommTest4Init
** ��������: //���ڳ�ʼ��
** ��ڲ���:  
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void CommTest4Init(void)
{
    s_stCommTest4.recvlen       = 0;
    s_stCommTest4.resendlen     = 0;
    s_stCommTest4.resendCnt     = 0;
    s_stCommTest4.recvfreeCnt   = 0;
    s_stCommTest4.recvBuff      = s_ucCommTest4recvBuff;
    //s_stCommTest4.resendBuff    = s_ucCommTest4resendBuff;
    ////////////////////
    COMM_Initialize(TEST_COM4,9600);
    ////////////////////
    gpio_out_init(PIN_NO_GPS_CTR);		
    COMM_CtrlEnableInitialize(TEST_COM4,CommTest4RecvEnable,CommTest4SendEnable);
}
/*******************************************************************************
 *                             end of module
 *******************************************************************************/

