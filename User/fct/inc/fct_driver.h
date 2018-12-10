/********************************************************************
//��Ȩ˵��	:
//�ļ�����	:FCT_driver.h	
//����		:�������ͷ�ļ�
//�汾��	:
//������	:yjb
//����ʱ��	:2012.6
//�޸���	:
//�޸�ʱ��	:
//�޸ļ�Ҫ˵��	:
//��ע		:
***********************************************************************/
#ifndef __FCT_DRIVER__
#define __FCT_DRIVER__

#ifndef	_EXT_FCT_DRIVER_
	#define	_EXT_FCT_DR_		extern
#else
	#define	_EXT_FCT_DR_
#endif

#include <rtthread.h>
//#include "GPIOControl.h"
#include "pin.h"
#include "gpio.h"

extern u8 	BeepOnOffFlag;
extern u8	GprsLedOnOffFlag;
extern u8	GpsLedOnOffFlag;

extern u32	BeepOnTime;
extern u32	BeepOffTime;
extern u32	GprsLedOnTime;
extern u32	GprsLedOffTime;
extern u32	GpsLedOnTime;
extern u32	GpsLedOffTime;

//************����������************
#define  BEEP_ON()  		gpio_out_on(PIN_NO_BUZZER);BeepOnOffFlag = 1;BeepOnTime=rt_tick_get()
#define  BEEP_OFF()     gpio_out_off(PIN_NO_BUZZER);BeepOnOffFlag = 0;BeepOffTime=rt_tick_get()
//*************����������*********
#define SPEAKER_ON()            gpio_out_on(PIN_NO_V_COL);
#define SPEAKER_OFF()           gpio_out_off(PIN_NO_V_COL);
//*************���ƫ�õ�ѹ����*********
#define MIC_BASE_ON()       GPIO_WriteBit(GPIOD,GPIO_Pin_5,Bit_SET);MicBaseOnOffFlag = 1
#define MIC_BASE_OFF()      GPIO_WriteBit(GPIOD,GPIO_Pin_5,Bit_RESET);MicBaseOnOffFlag = 0
//*************���2����*********
#define OUTPUT2_SET()       GPIO_WriteBit(GPIOF,GPIO_Pin_2,Bit_SET)
#define OUTPUT2_RESET()     GPIO_WriteBit(GPIOF,GPIO_Pin_2,Bit_RESET)
//*************SD����Դ��ѹ����*********
#define  SD_POWER_ON()      gpio_out_off(PIN_NO_SD_POWER)
#define  SD_POWER_OFF()     gpio_out_on(PIN_NO_SD_POWER)
//*************��·����*********
#define  OIL_CUT_ON()       gpio_out_off(PIN_NO_COIL)  //ͨ��
#define  OIL_CUT_OFF()      gpio_out_on(PIN_NO_COIL)   //����,�ߵ�ƽ���
//**************12V/24V�������***************
#define   PWR_TYPE_24V()    gpio_out_on(PIN_NO_PWR_TYPE)
#define   PWR_TYPE_12V()    gpio_out_off(PIN_NO_PWR_TYPE)

//-------------------------------------------------------
#define FCT_RECV_LEN 128
//���ս�������
typedef struct _DEBUG_REC_
{
	uint8_t	state;
	uint8_t	length;
	uint8_t	buf[FCT_RECV_LEN+1];
}PRTL_REC_DEBUG;

//���ս�������
typedef struct _GNSS_
{
	uint32_t	time;
	uint8_t		gnss;
	uint8_t		gnss_ok;
}_API_GNSS_;


_EXT_FCT_DR_	PRTL_REC_DEBUG	FCT_recv;

_EXT_FCT_DR_		_API_GNSS_	g_Gnss;

//GSM-232�ռ仮��
#define REC_GNSS_232		100		
#define SEND_GNSS_232		100		

//��ʱ���ջ�����
typedef struct _GNSS_REC_
{
	uint8_t	state;
	uint8_t	length;
	uint8_t	buf[REC_GNSS_232];
}PRTL_REC_GNSS;

_EXT_FCT_DR_	PRTL_REC_GNSS 	gnss_rec;	



//IO��ʼ��
void Fct_GpioInit(void);
void GnssRecIsr(void);
//����50MSΪ��׼��ʱ��ȽϺ���
//����ʱ�䷵��TRUE ��û�г����ӳ�ʱ�䷵��FALSE 
uint8_t	DebugCompareTime(uint32_t souce_time,uint32_t const_time);
void FCT_AppDisposeDebugRecvData(unsigned char *pBuffer,unsigned short len);


typedef struct	__PLUSE_TIM3__
{
	uint32_t time;
	uint32_t count;
	uint8_t flag;
	uint8_t end;
	
}_API_PLUSE_T_;

_EXT_FCT_DR_	_API_PLUSE_T_		g_Pluse;
//��ʼ����ʱ��3
void Init_Tim3Pluse(void);
//��ʼ�����崫�����ж�
void Init_ExtPluse(void);

#endif
