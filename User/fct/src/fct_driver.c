/********************************************************************
//��Ȩ˵��	:Shenzhen E-EYE Co. Ltd., Copyright 2013- All Rights Reserved.
//�ļ�����	:app_fct.c		
//����		:������
//�汾��	:
//������	:ytl
//����ʱ��	:2013.09
//�޸���	:
//�޸�ʱ��	:
//�޸ļ�Ҫ˵��	:
//��ע		:
***********************************************************************/
#define	_EXT_FCT_DRIVER_

#include "include.h"
#include <rthw.h>
#include <rtthread.h>


//*********************����������*****************
u32	BeepOnTime = 0;
u32	BeepOffTime = 0;
u8	BeepOnOffFlag = 0;//���������ر�־

//*********************ͨ��ģ�飬��λģ��ָʾ�ƿ���************
u32	GprsLedOnTime = 0;
u32	GprsLedOffTime = 0;
u32	GpsLedOnTime = 0;
u32	GpsLedOffTime = 0;
u8	GprsLedOnOffFlag = 0;//���������ر�־
u8	GpsLedOnOffFlag = 0;//���������ر�־
u8	GprsLedState = 0;//GPRS LED��״̬,0��������Ϩ��,1��������˸,2�����ϳ���
u8	GpsLedState = 0;//GPS LED��״̬,0��������Ϩ��,1��������˸,2�����ϳ���


/*
************************************************************************
*	�� �� ��: void Fct_GpioInit(void)
*	����˵��: ��ʼ��GPIO����/�������
*	��    �Σ���
*	�� �� ֵ: ��
**************************************************************************
*/
void Fct_GpioInit(void)
{
	gpio_in_init(PIN_NO_DLIGHTI);
	gpio_in_init(PIN_NO_LLIGHTI);
	gpio_in_init(PIN_NO_BREAK);
	gpio_in_init(PIN_NO_ACC);
	gpio_in_init(PIN_NO_DOORI_N);
	gpio_in_init(PIN_NO_DOORI_P);
	gpio_in_init(PIN_NO_DOORI2);
	gpio_out_init(PIN_NO_LAMP);
	gpio_out_init(PIN_NO_LOCK_OUT);
	gpio_out_init(PIN_NO_UNLOCK_OUT);
	gpio_in_init(PIN_NO_XLIGHTI);
	gpio_in_init(PIN_NO_RLIGHTI);
	gpio_in_init(PIN_NO_BKHI);
	gpio_in_init(PIN_NO_SWITCHI);	
	gpio_in_init(PIN_NO_HORNI); 
	gpio_in_init(PIN_NO_VIRBRATIONI); 
	gpio_out_init(PIN_NO_COIL); 
	gpio_out_init(PIN_NO_HORN_OUT); 
	gpio_out_init(PIN_NO_GSM_PWC);
	gpio_out_init(PIN_NO_GSM_ON);
	
	gpio_in_init(PIN_NO_DETCT1I); 
	gpio_in_init(PIN_NO_DETCT2I); 

	gpio_out_init(PIN_NO_V_COL);

	gpio_out_init(PIN_NO_BUZZER);
	//GpioInInit(MIC_EN);//dxl,2014.9.30ԭ��������Ϊ�������������MIC_INͬʱҲ�������ֽ��ɱ��汾�����������Ϊ���룬
											//�ڼ���꽵�ɱ��汾�������Զ�����Ϊ�����
	gpio_out_init(PIN_NO_MIC_EN);//dxl,2016.3.30
	gpio_out_init(PIN_NO_SD_POWER);//dxl,2013.5.16

	gpio_out_init(PIN_NO_I2S_AD_DA);//dxl,2013.5.23
	gpio_out_init(PIN_NO_I2S_PWDAN);//dxl,2013.5.23
	gpio_out_init(PIN_NO_I2S_PWADN);//dxl,2013.5.23

	gpio_out_init(PIN_NO_PWR_TYPE);//dxl,2013.5.26

	gpio_in_init(PIN_NO_SD_DETECT);//dxl,2013.8.16

	//Io_InitStatusHighValid(); 			 //��ʼ��״̬����Ч��ƽ
	//Io_InitExtCarStatusHighValid();  //��ʼ����չ����״̬����Ч��ƽ
	//Io_InitAlarmHighValid();				 //��ʼ����������Ч��ƽ
	//Io_InitDefine2StatusHighValid();//��ʼ���Զ���״̬��2����Ч��ƽ

}

/*
************************************************************************
*	�� �� ��: void DebugRec_232(void)
*	����˵��: ����DEBUG�������ݣ��ŵ�������
*	��    �Σ���
*	�� �� ֵ: ��
**************************************************************************
*/
void Init_Tim3Pluse(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    NVIC_InitTypeDef NVIC_InitStructure;


    /* TIM1 Peripheral Configuration */ 
    TIM_DeInit(TIM3);
    TIM_DeInit(TIM4);

    /* TIM1 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	

    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 2400-1	;//0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 3;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//TIM_CKD_DIV4;//0x0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;

    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	

    /* TIM IT enable */ 
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 

    TIM_Cmd(TIM3, DISABLE);   //ʹ�ܶ�ʱ����ʱ
    TIM_Cmd(TIM4, DISABLE); 

    /* Enable the TIM1 Trigger and commutation interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;//TIM1_TRG_COM_TIM11_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
}
void Init_ExtPluse(void)
{
#if 0
	EXTI_InitTypeDef   EXTI_InitStructure;
  	GPIO_InitTypeDef   GPIO_InitStructure;
  	NVIC_InitTypeDef   NVIC_InitStructure;

  	/* Enable GPIOE clock */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  	/* Enable SYSCFG clock */
  	//RCC_APB2PeriphClockCmd(RCC_APB1Periph_SYSCFG, ENABLE);
  
  	/* Configure PE2 pin as input floating */
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);

  	/* Connect EXTI Line2 to PE2 pin */
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);

  	/* Configure EXTI Line2 */
  	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);

  	/* Enable and set EXTI2 Interrupt to the lowest priority */
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
	gpio_irq_install(PIN_NO_EXT_PLUSE,PIN_MODE_INPUT,PIN_IRQ_MODE_FALLING,RT_NULL);
} 

/*
************************************************************************
*	�� �� ��: void DebugRec_232(void)
*	����˵��: ����DEBUG�������ݣ��ŵ�������
*	��    �Σ���
*	�� �� ֵ: ��
**************************************************************************
*/
void FCT_AppDisposeDebugRecvData(unsigned char *pBuffer,unsigned short len)
{
    unsigned short i;
    unsigned char *buffer;
    unsigned char tmp;
    unsigned char flag=0;
    buffer=pBuffer;
    for(i=0; i<len-3; i++)
    {
        tmp = buffer[i];
        if('E'==tmp)
        {
            if(strncmp("EYE+",(char const *)&buffer[i],4)==0)
            {
                flag = 1;
                FCT_recv.length = 0;
								memset(FCT_recv.buf,0,sizeof(FCT_recv.buf));
                break;
            }
        }
    }
    ///////////////////////
    if(flag)
    {
        for( ;i<len; i++)
        {
            tmp = buffer[i];
            if(tmp!=0x0d&&FCT_recv.length<FCT_RECV_LEN)
            {
                FCT_recv.buf[FCT_recv.length++]=tmp;
            }
            else
            {
                FCT_recv.buf[FCT_recv.length+1]= '\0'; 
								rt_mq_send(fct_app_msg, "fct_debug", FCT_MSG_LEN);
                //SetEvTask(EV_FCT_CMD);
                break;
            }
        }
    }    
}
/*
************************************************************************
*	�� �� ��: uint8_t	DebugCompareTime(uint32_t souce_time,uint32_t const_time)
*	����˵��: //ʱ���ӳٷ�������������ȡ���� ��׼����ʱ�� 50MSΪ��׼
*	��    �Σ�uint32_t souce_time	��ʼʱ��
						uint32_t const_time���Ӻ�ʱ��
*	�� �� ֵ: ����ʱ�䷵��TRUE ��û�г����ӳ�ʱ�䷵��FALSE 
**************************************************************************
*/
void GnssRecIsr(void)
{
    u8 temp;
    if(USART_GetITStatus(UART4,USART_IT_RXNE)==SET)
    {   
        USART_ClearITPendingBit(UART4,USART_IT_RXNE); 
        temp = USART_ReceiveData(UART4);
        if(temp=='$')//��ʼ��
        {
            gnss_rec.length=0;
            gnss_rec.buf[gnss_rec.length++]=temp;	
        }
        else if(0x0a == temp)//��β��
        {
            gnss_rec.buf[gnss_rec.length++]=temp;	
            if((0 == strncmp("$GPRMC",(char const *)gnss_rec.buf,6))//GPS��ʽ
            ||(0 == strncmp("$GNRMC",(char const *)gnss_rec.buf,6))//GPS+BD��ʽ
            ||(0 == strncmp("$BDRMC",(char const *)gnss_rec.buf,6)))//BD��ʽ
            {
                g_Gnss.gnss_ok=true;

            }
            else if((0 == strncmp("$GPGGA",(char const *)gnss_rec.buf,6))//GPS��ʽ
            ||(0 == strncmp("$GNGGA",(char const *)gnss_rec.buf,6))//GPS+BD��ʽ
            ||(0 == strncmp("$BDGGA",(char const *)gnss_rec.buf,6)))//BD��ʽ
            {
                //memcpy(g_Gnss.gga,gnss_rec.buf,gnss_rec.length);
            }
        }
        else//�����м�����
        {
            if(gnss_rec.length<REC_GNSS_232)
            gnss_rec.buf[gnss_rec.length++]=temp;	
        }
    }
}

//��ʼ�����崫�����ж�
#if 0                                                                             
/*
************************************************************************
*	�� �� ��: uint8_t	DebugCompareTime(uint32_t souce_time,uint32_t const_time)
*	����˵��: //ʱ���ӳٷ�������������ȡ���� ��׼����ʱ�� 50MSΪ��׼
*	��    �Σ�uint32_t souce_time	��ʼʱ��
						uint32_t const_time���Ӻ�ʱ��
*	�� �� ֵ: ����ʱ�䷵��TRUE ��û�г����ӳ�ʱ�䷵��FALSE 
**************************************************************************
*/
uint8_t	DebugCompareTime(uint32_t souce_time,uint32_t const_time)
{
    uint32_t tmp_time;
    tmp_time=rt_tick_get();
    if(tmp_time>souce_time)
    {
        if(tmp_time-souce_time>const_time||tmp_time-souce_time==const_time)
            return true;
        else
            return	false;

    }
    else
    {
        if(souce_time-tmp_time>const_time||souce_time-tmp_time==const_time)
            return true;
        else
            return false;

    }

}
/*
************************************************************************
*	�� �� ��: void Init_Can_1_2(void)
*	����˵��: ��ʼ��CAN�ķ��ͼĴ���
*	��    �Σ�
						
*	�� �� ֵ: 
**************************************************************************
*/
void Init_Can_1_2(void)
{
	g_tCanTxMsg_1.StdId = 0x321;
	g_tCanTxMsg_1.ExtId = 0x01;
	g_tCanTxMsg_1.RTR = CAN_RTR_DATA;
	g_tCanTxMsg_1.IDE = CAN_ID_STD;
	g_tCanTxMsg_1.DLC = 1;
	
	g_tCanTxMsg_2.StdId = 0x321;
	g_tCanTxMsg_2.ExtId = 0x01;
	g_tCanTxMsg_2.RTR = CAN_RTR_DATA;
	g_tCanTxMsg_2.IDE = CAN_ID_STD;
	g_tCanTxMsg_2.DLC = 1;		
	
}
//CAN ����
 void SendCanMsg_1(void)
{
    if(g_recCan_1)
    {
        /* ��CAN���緢��һ������, ��������1���ֽ�ָLED����� */
        // g_tCanTxMsg.Data[0] = 0x11;//g_ucLedNo;
        CAN_Transmit(CAN1, &g_tCanTxMsg_1);	
        g_recCan_1=0;
    }
}
//can ����
 void SendCanMsg_2(void)
{
    if(g_recCan_2)
    {
        /* ��CAN���緢��һ������, ��������1���ֽ�ָLED����� */
        // g_tCanTxMsg.Data[0] = 0x11;//g_ucLedNo;
        CAN_Transmit(CAN2, &g_tCanTxMsg_2);	
        g_recCan_2=0;
    }
}

//CAN1---can2 ��������
void Api_CanSendDate_1_2(void)
{
    SendCanMsg_1();	
}
#endif
