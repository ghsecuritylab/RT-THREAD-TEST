#define	_WDOGMANAGE_GLOBALS
#include "include.h"
#include <rthw.h>
#include <rtthread.h>



#define	WDOG_THREAD_PRIORITY	10
static rt_uint8_t watchDog_stack[ 512 ];
static struct rt_thread watchDog_thread;

/*************************************************************OK
** ��������: watchDog_thread_entry
** ��������: ���Ź��߳����
** ��ڲ���: 
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
static void watchDog_thread_entry(void* parameter)
{     
	rt_uint32_t rcvEvt;
	wdog_event = rt_event_create ("wdog_event", RT_IPC_FLAG_FIFO);
	
	#if E_EYE_ENABLE == CONFIG_IWDG  ////�������Ź�
		IDWG_Configuration(); 
	#endif
	while (1)    
	{        
		/* waitting watchDog  all event arrive... */
		if (rt_event_recv(wdog_event, WDOG_EVENT_FLAG,
				RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
				RT_WAITING_FOREVER, &rcvEvt) == RT_EOK)
		{
			
			#ifdef	RT_USING_CONSOLE	 
					//rt_kprintf("��Ҫ�̶߳����й��˲���ι��...\r\n");
			#endif		  
			#if E_EYE_ENABLE == CONFIG_IWDG
				IWDG_ReloadCounter();
			#endif
			rt_thread_yield();       
			//rt_thread_delay( RT_TICK_PER_SECOND*5 );   
		}
	}
}
/*************************************************************OK
** ��������: watchDog_thread_init
** ��������: ���Ź��̳߳�ʼ��
** ��ڲ���: 
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void watchDog_thread_init(void)
{
	rt_err_t result;
	
	result = rt_thread_init(&watchDog_thread,                            
							"watchDog_task",                            
							watchDog_thread_entry,                            
							RT_NULL,                            
							(rt_uint8_t*)&watchDog_stack[0],                            
							sizeof(watchDog_stack),                            
							WDOG_THREAD_PRIORITY,                            
							5);    
	if (result == RT_EOK)    
	{        
		rt_thread_startup(&watchDog_thread);    
	} 
}


