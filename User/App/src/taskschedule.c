/********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS 
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#define	_TASKSCHEDULE_GLOBALS
#include "stm32f10x.h"
#include "include.h"
#include <rthw.h>
#include <rtthread.h>

#define	TASK_SCHEDULE_THREAD_PRIORITY	11
static rt_uint8_t task_schedule_stack[ 1024 ];
static struct rt_thread task_schedule_thread;

rt_mailbox_t task_mailBox = RT_NULL;

/* extern function -----------------------------------------------------------*/
void EvNopHandleTask(void);
FunctionalState TimerNopHandleTask(void);

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIME_TASK MyTimerTask[MAX_TIMETASK] = {  
	{DISABLE,0,	10,	 LZM_PublicTimerTask},                 //48:����
	{DISABLE,0, 10,  CommParam_TimeTask},                  //48:���� ����1
	//{DISABLE,0, 10,  CommTest2_TimeTask},                  //48:����
	//{DISABLE,0, 10,  CommTest4_TimeTask},                  //48:����
	{DISABLE,0, 10,  CommTest5_TimeTask},                  //48:���� ����5 GSM
	{ENABLE,0,2,Adc_CollectApp_TimeTask},                      //48:����
	{ENABLE, 0, 100, TimerNopHandleTask},                  //48:����
};
			
EVEN_TASK MyEvTask[MAX_EVENTASK] = {                                 
	{DISABLE, EvNopHandleTask},          // 0:����CAN����SendCanData_EvTask
	{DISABLE, EvNopHandleTask},          // 1:CAN�������ݴ��� ,DecodeCan_EvTask

};
                                               
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Function Name  : InitTimerTask
* Description    : Initialize Schedule Timer task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void InitTimerTask(void)
{
  //u8 i;
  /*
  for(i = 1; i < MAX_TIMETASK; i++)
  {
    MyTimerTask[i].TaskTimerState = DISABLE;
  }
  */
  //���ӳ�ʼ������,��������ִ�к���ʱ��  
}

/*******************************************************************************
* Function Name  : SetTimerTask
* Description    : Setup timer task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SetTimerTask(TIMERTASK task, u32 time)
{
  MyTimerTask[task].TaskTimerState = ENABLE;
  MyTimerTask[task].TaskExTimer = time;
  MyTimerTask[task].TaskTimerCount = time + rt_tick_get();
}

/*******************************************************************************
* Function Name  : ClrTimerTask
* Description    : Cancel timer task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ClrTimerTask(TIMERTASK task)
{
  MyTimerTask[task].TaskTimerState = DISABLE;
}
/*******************************************************************************
* Function Name  : TimerTaskScheduler
* Description    : Schedule Timer task .running in idle thread 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TimerTaskScheduler(void)  
{
  u8 i;
  u32 nowtimer;
  //FunctionalState validflag;
  nowtimer = rt_tick_get();
  for(i = 0; i < MAX_TIMETASK; i++)
  {
     if(MyTimerTask[i].TaskTimerState != ENABLE) 
     {
         continue;
     }

    if(nowtimer >= MyTimerTask[i].TaskTimerCount)
    {
        MyTimerTask[i].TaskTimerCount = nowtimer + MyTimerTask[i].TaskExTimer;
				rt_mb_send (task_mailBox, i);
        //validflag = MyTimerTask[i].operate();
        //MyTimerTask[i].TaskTimerState = validflag; 
    }
  }
}


/*******************************************************************************
* Function Name  : InitEvTask
* Description    : Initialize Schedule Timer task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void InitEvTask(void)
{
  u8 i;
  
  for(i = 0; i < MAX_EVENTASK; i++)
  {
    MyEvTask[i].evTaskOnState = DISABLE;
  }
  //���ӳ�ʼ������
}

/*******************************************************************************
* Function Name  : SetEvTask
* Description    : Setup even task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SetEvTask(u8 ev)
{
  MyEvTask[ev].evTaskOnState = ENABLE;
}

/*******************************************************************************
* Function Name  : EvTaskScheduler
* Description    : Schedule even task .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EvTaskScheduler(void) 
{
  u8 i;

  for(i = 0; i < MAX_EVENTASK; i++)
  {
    if(MyEvTask[i].evTaskOnState != ENABLE)
      continue;
    MyEvTask[i].evTaskOnState = DISABLE;
    MyEvTask[i].operate();
   
  }
} 
/*******************************************************************************
* Function Name  : EvNopHandleTask
* Description    : ���¼����� .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
FunctionalState TimerNopHandleTask()
{
  
  return ENABLE;
}

/*******************************************************************************
* Function Name  : EvNopHandleTask
* Description    : ���¼����� .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EvNopHandleTask()
{

}
/*******************************************************************************
* Function Name  : SendCanData_EvTask
* Description    : ����CAN����
* Input          : None
* Output         : None
* Return         : None
* Note           :��Ҫ���͵�CAN���ݷ���RadioProtocolMiddleBuffer,����ΪRadioProtocolMiddleLen
*******************************************************************************/
void SendCanData_EvTask(void)
{
        //���÷���CAN���ݵĺ���
        
}
/*************************************************************OK
** ��������: watchDog_thread_entry
** ��������: ��������߳����
** ��ڲ���: 
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
static void task_schedule_thread_entry(void* parameter)
{     
	rt_uint32_t mail;
	task_mailBox = rt_mb_create ("task_mailbox", MAX_TIMETASK, RT_IPC_FLAG_FIFO);;
	
	while (1)    
	{        
		/* waitting mail arrive... */
		if (rt_mb_recv (task_mailBox, &mail, RT_WAITING_FOREVER) == RT_EOK)
		{
			MyTimerTask[mail].TaskTimerState = MyTimerTask[mail].operate();
		}
		rt_event_send(wdog_event, (0x1 << mail));
		#ifdef	RT_USING_CONSOLE	 
				//rt_kprintf("\r\nmail is arrived...%d\r\n",mail);
		#endif		  
		rt_thread_yield();          
	}
}
/*************************************************************OK
** ��������: task_schedule_thread_init
** ��������: �̳߳�ʼ��
** ��ڲ���: 
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void task_schedule_thread_init(void)
{
	rt_err_t result;
	
	result = rt_thread_init(&task_schedule_thread,                            
							"task_schedule_task",                            
							task_schedule_thread_entry,                            
							RT_NULL,                            
							(rt_uint8_t*)&task_schedule_stack[0],                            
							sizeof(task_schedule_stack),                            
							TASK_SCHEDULE_THREAD_PRIORITY,                            
							5);    
	if (result == RT_EOK)    
	{        
		rt_thread_startup(&task_schedule_thread);    
	} 
}

