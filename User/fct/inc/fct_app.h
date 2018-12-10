#ifndef	_FCT_APP_H_
#define	_FCT_APP_H_

#ifdef	_FCT_APP_GLOBALS
#define	_FCT_APP_EXT	
#else
#define	_FCT_APP_EXT	extern
#endif

#include <rtdef.h>

#define ADDR_COUNT              0x08

#define FM25C160_MAX_ADDR       (2048-1)//2K
#define EE25LC320A_MAX_ADDR     (2048-1)//2K

#define FLASH_DATA_MAX_ADDR     (1024*1024*4-6)//4M

#define AT25DF321_ID            0X1F4700//0X1F470000

#define	FCT_MSG_LEN							10

typedef struct	_DEBUG_FCT_
{
    uint32_t time;
    uint8_t debug_f;
    uint8_t	gprs;
    uint8_t iis;
}_APP_DEBUG_FCT;

_FCT_APP_EXT	_APP_DEBUG_FCT	g_fct;
_FCT_APP_EXT  rt_mq_t fct_app_msg;

/*************************************************************************
*	�� �� ��: FCT_AppInit
*	����˵��: FCT��ز�����ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
_FCT_APP_EXT void FCT_AppInit(void);
/*************************************************************************
*	�� �� ��: App_DisposeGprsRecvData
*	����˵��: GSM���ص����ݻش�FCT,������0x0d,0x0a��0x20����
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
_FCT_APP_EXT void App_DisposeGprsRecvData(unsigned char *pBuffer,unsigned short datalen);
/*************************************************************************
*	�� �� ��: Task_DebugCommIncode
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
_FCT_APP_EXT void Task_DebugCommIncode(void);
/*************************************************************OK
** ��������: fct_app_thread_init
** ��������: 
** ��ڲ���: 
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
_FCT_APP_EXT void fct_app_thread_init(void);

#endif





