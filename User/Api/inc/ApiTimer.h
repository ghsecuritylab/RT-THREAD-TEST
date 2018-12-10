#ifndef APITIMER_H
    #define APITIMER_H

#ifdef  __APITIMER_C__
    #define APITIMER_EXT
#else
    #define APITIMER_EXT extern
#endif

#include <rtdef.h>
#define TIMR_ON         		( E_EYE_ENABLE )
#define TIMR_OFF        		( E_EYE_DISABLE )
#define TIMEER_1S_ENABLE       	( E_EYE_ENABLE )
#define TIMEER_10MS_ENABLE     	( E_EYE_ENABLE )

#define TIMER_WORDTYPE  		u16
#define TIMER_MODE_ONCE         							0
#define TIMER_MODE_CONTINUE     							1
#define TIMER_MODE_STOP_WHEN_SUCCESS         	0xff

typedef  ErrorStatus	(*PEFUNCTION)(void);
typedef  struct TIMERINF        
{
  u8 number:6;               //��ʱ�����
  u8 timeswitch:1;           //��ʱ������
  u8 timerMode:1;            //��ʱ��ģʽ   0:once   1:continue
  void* msg;              //��ʱ������
  TIMER_WORDTYPE timeLen;       //��ʱ����
  TIMER_WORDTYPE timeCount;     //��ʱ����
  PEFUNCTION callback;          //�ص�����
}STR_TIMER;

typedef enum
{
    TIMER_1S_ID_0 = 0,
    TIMER_1S_ID_1,  
    TIMER_1S_ID_2,
    TIMER_1S_ID_3,
    TIMER_1S_ID_4,
    TIMER_1S_ID_5, 
    MAX_TIMENUM_1S
}TIMER_1S_ID;

typedef enum
{
    TIMER_10MS_ID_COMM_REV = 0,
    TIMER_10MS_ID_COMM_RESEND,
    TIMER_10MS_ID_2,
    TIMER_10MS_ID_3,
    TIMER_10MS_ID_4,
    TIMER_10MS_ID_5,
    MAX_TIMENUM_10MS,
}TIMER_10MS_ID;

#define	PRESCALER_VAL		(12 - 1)		//Ԥ��ƵֵΪ15��Ƶ��Ϊ72/12=6M
#define T2CCR_VAL_10MS  	(60000)      //6MƵ����10ms��Ҫ��ʱ����


#if TIMEER_10MS_ENABLE  
    APITIMER_EXT void TimerManage10ms(void);
    APITIMER_EXT u8 Timer10msStart(u8 timeNumber, TIMER_WORDTYPE timeLen, u8 mode, PEFUNCTION callBack);    
    APITIMER_EXT u8 CloseTime10ms(u8 timeNumber);
    #define StartTime10ms(id, len, cb)      Timer10msStart((id), (len), TIMER_MODE_CONTINUE, (cb))
#endif

#if TIMEER_1S_ENABLE  
    APITIMER_EXT void TimerManage1s(void);
    APITIMER_EXT u8 Timer1sStart(u8 timeNumber, TIMER_WORDTYPE timeLen, u8 mode,/* void* msg,*/PEFUNCTION callBack);  
    APITIMER_EXT u8 CloseTime1s(u8 timeNumber);
	#define StartTime1s(id, len,/* msg,*/cb)      Timer1sStart((id), (len), TIMER_MODE_CONTINUE,/* msg,*/(cb))
#endif  
	APITIMER_EXT void TimerInit(void);

#endif


