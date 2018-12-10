/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_dma.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      DMA firmware library.
********************************************************************************

*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TASKSCHEDULE_H
#define _TASKSCHEDULE_H

#ifdef	_TASKSCHEDULE_GLOBALS
#define	_TASKSCHEDULE_EXT	
#else
#define	_TASKSCHEDULE_EXT	extern
#endif

#include <rtdef.h>

//#define	WDOG_EVENT_FLAG_1		(0x1 << 0)
//#define	WDOG_EVENT_FLAG_2		(0x1 << 1)
//#define	WDOG_EVENT_FLAG_3		(0x1 << 2)

_TASKSCHEDULE_EXT rt_mailbox_t task_mailBox;


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
//*****************�¼�����**************************
typedef enum 
{
    EV_FCT_CMD = 0,               //0:����CAN����
    EV_CANREC,                          //1:CAN�������ݴ���
    EV_SEND_RS485,                       //2:GPS���ݴ���
    EV_SEND_DISPLAY,                          //3:�ϱ�һ��λ����Ϣ
    EV_GET_LOGIN_PASSWORD,              //4: ��ȡ��Ȩ������
    EV_LINK_GOV_SERVER,                 //5: �л����������ƽ̨
    EV_FTP_UPDATA,                      //6: FTP��������
    EV_CALLING,                         //7: һ��ͨ��
    EV_SEV_CALL,                        //8: �������ذε绰����
    EV_RING,                            //9:�����¼���   
    EV_RING_OVER,                       //10:ֹͣ����
    EV_SHOW_TEXT,			    //11:�ı���ʾ
    MAX_EVENTASK

}EVENTTASK;

//******************ʱ������***********************
typedef enum 
{
    TIME_PUBLIC,                    //48:����
    TIME_COM_PARAM,                 //47:��������
    //TIME_COM2_TEST,
    //TIME_COM4_TEST,
    TIME_COM5_TEST,
    //TIME_USB,                       //22:USB
    //TIME_TTSDELAY,                  //23:TTS
    TIME_AD,                        //27:AD����       
    //TIME_COM6_TEST,
    TIME_NOP, 							//������
    MAX_TIMETASK      		//60
}TIMERTASK;
/*------------------------ Execute task by timer--------------------------------
Max task is 32. when power on dev this task is init.
Include 
------------------------------------------------------------------------------*/
typedef struct{
  FunctionalState TaskTimerState;       //task valid,1:valid;0:invalid
  u32 TaskTimerCount;           //variables task time count
  u32 TaskExTimer;              //set fixed param by independently funtion module
  FunctionalState (* operate)();     //handle independtly funtion
  //rt_uint32_t	mail;     
}TIME_TASK;

typedef struct{
  FunctionalState evTaskOnState;       //task valid,1:valid;0:invalid
  void (*operate)();     //handle independtly funtion
}EVEN_TASK;

/* Private define ------------------------------------------------------------*/



/*******************************************************************************
* Function Name  : InitTimerTask
* Description    : Initialize Schedule Timer task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void InitTimerTask(void);

/*******************************************************************************
* Function Name  : TimerTaskScheduler
* Description    : Schedule Timer task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TimerTaskScheduler(void);

/*******************************************************************************
* Function Name  : SetTimerTask
* Description    : Setup timer task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SetTimerTask(TIMERTASK task, u32 time);

/*******************************************************************************
* Function Name  : ClrTimerTask
* Description    : Cancel timer task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ClrTimerTask(TIMERTASK task);

/*******************************************************************************
* Function Name  : InitEvTask
* Description    : Initialize Schedule Timer task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void InitEvTask(void);
/*******************************************************************************
* Function Name  : SetEvTask
* Description    : Setup even task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SetEvTask(u8 ev);
/*******************************************************************************
* Function Name  : EvTaskScheduler
* Description    : Schedule even task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EvTaskScheduler(void);
/*******************************************************************************
* Function Name  : SendCanData_EvTask
* Description    : ����CAN����
* Input          : None
* Output         : None
* Return         : None
* Note           :��Ҫ���͵�CAN���ݷ���RadioProtocolMiddleBuffer,����ΪRadioProtocolMiddleLen
*******************************************************************************/
void SendCanData_EvTask(void);

_TASKSCHEDULE_EXT void task_schedule_thread_init(void);

#endif
