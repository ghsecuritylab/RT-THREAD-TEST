#ifndef	_SYSTEM_CFG_H_
#define	_SYSTEM_CFG_H_

#ifdef	_SYSTEM_CFG_GLOBALS
#define	_SYSTEM_CFG_EXT	
#else
#define	_SYSTEM_CFG_EXT	extern
#endif

//#include <rtdef.h>

#define E_EYE_DISABLE				(0)
#define E_EYE_ENABLE				(1)

// �Ƿ����ģʽ  ��ģʽ��ϵӲ�����ܣ���ʽ������ش��� E_EYE_DISABLE ״̬
#define CONFIG_DEBUG_MODE  			E_EYE_ENABLE

#define CONFIG_IWDG     			E_EYE_ENABLE
#define IWDENDataAddr 				0x1FFFF802

#define	MCU_STM32F1XX				(0)
#define	MCU_STM32L1XX				(1)
#define	MCU_TYPE					MCU_STM32F1XX

//ʱ������ģʽ
#define	CLOCK_MODE_MANUAL		(0)
#define	CLOCK_MODE_SYSTEM		(1)
#define	CLOCK_CONFIG_MODE		CLOCK_MODE_MANUAL

//���Ź�ʹ������
#define	IWDOG_MODE		E_EYE_ENABLE
#define	WWDOG_MODE		E_EYE_DISABLE

//���Ź�����ʹ��
#define	WDOG_TASK_EN		E_EYE_DISABLE

//ʱ�Ӱ�ȫϵͳ����
#define	RCC_CSS_MODE		E_EYE_DISABLE


//��������ģʽ
#define	OSC_MODE_INTERNAL			(0)//ʹ���ڲ�����
#define	OSC_MODE_EXTERNAL			(1)//ʹ���ⲿ����
#define	OSC_CONFIG_MODE				OSC_MODE_INTERNAL

#define WAKEUP_ON_SPEED                 (4)   
#define POWERON_ON_SYSSPEED             (48)
#define POWEROFF_ON_SYSSPEED            (8)

//�Զ����豸
//#define	CUSTOM_USING_TEMPLATE
#define CUSTOM_DEVICE_NAME_ID1	 "template"


#endif
