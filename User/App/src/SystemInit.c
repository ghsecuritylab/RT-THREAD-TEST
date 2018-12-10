/********************************************************************
//��Ȩ˵��  :Shenzhen E-EYE Co. Ltd., Copyright 2009- All Rights Reserved.
//�ļ�����  :SystemInit.c       
//����      :ϵͳ��ʼ�� 
//�汾��    :
//������    :dxl
//����ʱ��  :2012.4
//�޸���    :
//�޸�ʱ��  :
//�޸ļ�Ҫ˵��  :
//��ע      :
***********************************************************************/
//***************�����ļ�*****************
#include "include.h"
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "gpio.h"

//***************���ر���******************
//***************�ⲿ����*****************

//**************��������*******************

/*********************************************************************
//��������  :MemoryChipSelfCheck
//����      :�ϵ�洢оƬ�Լ�
//����      :
//���      :
//ʹ����Դ  :
//ȫ�ֱ���  :   
//���ú���  :
//�ж���Դ  :  
//����      :
//��ע      :�Լ�Ĵ洢оƬ�У�FRAM��FLASH��EEPROM
*********************************************************************/
void MemoryChipSelfCheck(void)
{

}
/*********************************************************************
//��������	:PowerOnUpdata
//����		:�ϵ���±���
//����		:
//���		:
//ʹ����Դ	:
//ȫ�ֱ���	:   
//���ú���	:
//�ж���Դ	:  
//����		:
//��ע		:���µı����У�IO��GPS��λ�û㱨������ͷ
*********************************************************************/
void PowerOnUpdata(void)
{
 
    /////////////////////
    //BEEP_ON();
    //����IO����
    //Io_UpdataPram();
    //����GPS����
    //����������ʱ����
    //HeartBeat_UpdatePram();
    //�����������
    
    //����ϵ��У׼��ʼ��
    //Adjust_Init();       
    //�����ֻ�����
    //RadioProtocol_UpdateTerminalPhoneNum();
    //����λ�û㱨����
    //Report_UpdataPram();
    //��������ͷ����
    //Camera_StartCheck();
    //Camera_UpdataPram();
    //Camera_PowerOnSelfCheck();//���485�������ж��ٸ�����ͷ,ȥ���ϵ��⣬��������ʱ��
    //Photo_UpdataPram();//���������Ķ�ʱ�������ղ�������
    //////////////////
   // Report_ParameterInitialize();
    //¼�������ʼ��   
    //////////////////
    //GPS_POWER_ON();
    
    //�����12V���绹��24V����
    //Io_PowerOnDetectMainPower();     
    ////////////////////////
    FCT_AppInit();
    ////////////    
    ////////////////////////////
    Public_ParameterInitialize();
    //���³��ٱ���
    //BEEP_OFF();
   
}

ErrorStatus hd_timer_callback_0(void)
{	
	#ifdef	RT_USING_CONSOLE	 
		rt_kprintf("hd_timer_callback_0...\r\n");
	#endif	
	return SUCCESS;
}
ErrorStatus hd_timer_callback_1(void)
{	
	#ifdef	RT_USING_CONSOLE	 
		rt_kprintf("hd_timer_callback_1...\r\n");
	#endif	
	return SUCCESS;
}
void pin_irq_hdr_acc(void *args)
{
	args = args;	
#ifdef	RT_USING_CONSOLE			
	rt_kprintf("pin_acc�жϲ���...\r\n");
#endif 
}
/*********************************************************************
//��������  :PeripheralInit
//����      :�����ʼ��
//����      :
//���      :
//ʹ����Դ  :
//ȫ�ֱ���  :   
//���ú���  :
//�ж���Դ  :  
//����      :
//��ע      :��ʼ���������У�GPS��GPRS��FRAM��FLASH��EEPROM������ͷ
*********************************************************************/
void PeripheralInit(void)
{
	
	//GPIO��ʼ��
  Fct_GpioInit(); 
	
	InitRtc();
	    
	Ad_Init();

	TimerInit();

	//SD_POWER_OFF();//�ȹر�SD����Դ����
	//Io_Init();
	    
	//Ӳ����λ��ʾ��,ʹ�õ���USB��Դ��������
	USB_SW_Init();
	USB_SW_0();
	rt_thread_delay( RT_TICK_PER_SECOND/2 );  
	
	USB_SW_1();

	rt_thread_delay( RT_TICK_PER_SECOND/2 );        

	BEEP_ON();

	//FLASHģ���ʼ�� 
  //sFLASH_DeInit();
  //sFLASH_Init();
  //sFLASH_AllUnprotect();

	//EEPROMģ���ʼ��
	//E2prom_InitIO(); 

  FRAM_Init();
	
	//SD_POWER_ON();//��SD������
	rt_thread_delay( RT_TICK_PER_SECOND/2 ); 
	// SD SPI��ʼ
        
  //Media_CheckSdOnOff();//dxl,2014.6.18,���SD���ڲ�����Ҫ����InitSDFile֮ǰ,��Ϊ��InitSDFile���滹����SD���Ƿ��𻵣������˵�ͬ�ڲ���
  //SPIx_Init(); 
  //f_mount(1,&fs);
  //InitSDFile();//�����ڴ˴������ν�����������ˣ�ż���ο���
    
	BEEP_OFF();

	//USB_AppInitialize();
	
	//װ��gpio�ܽ��жϻص�����
	gpio_irq_install_callback(PIN_NO_ACC,PIN_MODE_INPUT_PULLDOWN,pin_irq_hdr_acc,PIN_IRQ_MODE_RISING,RT_NULL);
	gpio_irq_install(PIN_NO_SWITCHI,PIN_MODE_INPUT,PIN_IRQ_MODE_FALLING,RT_NULL);

	
	#if 0//TIMEER_1S_ENABLE 
	Timer1sStart(TIMER_1S_ID_0,10,TIMER_MODE_ONCE,hd_timer_callback_0);
	StartTime1s(TIMER_1S_ID_1,10,hd_timer_callback_1);
	#endif
}

/*******************************************************************************
* Function Name  : IDWG_Configuration
* Description    : Configures IDWG clock source and prescaler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IDWG_Configuration(void)
{
#if E_EYE_ENABLE == CONFIG_IWDG
/* Enable the LSI oscillator ************************************************/
  RCC_LSICmd(ENABLE);
  
  /* Wait till LSI is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {}
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* IWDG counter clock: 40KHz(LSI) / 32 = 1.25 KHz */
  //IWDG_SetPrescaler(IWDG_Prescaler_32);
    IWDG_SetPrescaler(IWDG_Prescaler_128);/*40KHz(LSI) / 128 = 320Hz */
    
  /* Set counter reload value to 2500 */
  IWDG_SetReload(0x9c4);//2��
    //IWDG_SetReload(0x4E2);//1��
  //IWDG_SetReload(0x271);//0.5��
  //IWDG_SetReload(0xFA);//0.2��


  /* Reload IWDG counter */
  IWDG_ReloadCounter();

  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();  
#endif
}

/*******************************************************************************
* Function Name  : PWR_PVDInit
* Description    : ��ԴPVD��ʼ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PWR_PVDInit(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    
    PWR_PVDLevelConfig(PWR_PVDLevel_2V9);
    PWR_PVDCmd(ENABLE);
    EXTI_StructInit(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line = EXTI_Line16;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
}

/*******************************************************************************
* Function Name  : USB_SW_Init
* Description    : USB�������ų�ʼ��������������Ӳ����λLCD��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void   USB_SW_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  
/******************************IO***********************************/    
    RCC_APB2PeriphClockCmd(  RCC_USB_SW , ENABLE);         /* ��GPIOʱ�� */

    GPIO_InitStructure.GPIO_Pin = PIN_USB_SW  ;
    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        /* ����ģʽ */ 
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;             /* ���/���� */
    
    //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           /* ��© */
    
  //  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             /* ���� */
    
    GPIO_Init( GPIO_USB_SW , &GPIO_InitStructure);
    
    USB_SW_1();
}
