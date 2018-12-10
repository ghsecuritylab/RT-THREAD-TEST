#define	_FCT_APP_GLOBALS
#include "include.h"
#include <rthw.h>
#include <rtthread.h>
#include "usart.h"

#define	FCT_APP_THREAD_PRIORITY	12
static rt_uint8_t fct_app_stack[ 1024 ];
static struct rt_thread fct_app_thread;



enum 
{
		CHECK_INPUT_EMPTY=0,					//
		CHECK_INPUT_DOORI_N,					//��״̬�ź�
		CHECK_INPUT_DOOR_TG2, 				//��չ��״̬�ź�		
		CHECK_INPUT_ACC,							//����ź�	
		CHECK_INPUT_BREAK,						//ɲ���ź�
		CHECK_INPUT_HIGH_BEAM,				//Զ���
		CHECK_INPUT_LOW_LIGHT,				//С��
		CHECK_INPUT_LEFT_LIGHT,				//��ת��
		CHECK_INPUT_RIGHT_LIGHT,			//��ת��
		CHECK_INPUT_AIR_CON,					//�յ�
		CHECK_INPUT_SOS,							//��������				
		CHECK_INPUT_KEY,							//һ��ͨ��
		CHECK_INPUT_HORN,							//����		
		CHECK_INPUT_Oil_Pressure, 
		CHECK_INPUT_NEAR_LIGHT,
		CHECK_INPUT_DOORI_P,
		CHECK_INPUT_MAX
}E_CHECK_INPUT;

enum 
{
    CHECK_OUTPUT_EMPTY=0,//
    CHECK_OUTPUT_LCD,//
    CHECK_OUTPUT_CAM,// 
    CHECK_OUTPUT_LED,//    
    CHECK_OUTPUT_MAX
}E_CHECK_OUTPUT;

/*************************************************************************
*	�� �� ��: FCT_AppInit
*	����˵��: FCT��ز�����ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void FCT_AppInit(void)
{
    static unsigned char sucFirstRunflag=0;    

    //��ʼ������
    CommParamInit();
    //CommTest2Init();
    //COMM_Initialize(COM3,9600);
    CommTest4Init();//gps
    CommTest5Init(); //gsm
    //CommTest6Init();     
    //��ʼ����ʱ��3
    Init_Tim3Pluse();
    Init_ExtPluse();
    // ��ʼ��¼��
    //Audio_Record_Init();
    //////////////////
    ReadRtc();
    g_fct.time = RTC_GetCounter();
    g_fct.iis = false;
    g_fct.gprs = false;
    g_fct.debug_f = 0;
    if(0==sucFirstRunflag)
		{			
			#ifdef	RT_USING_CONSOLE		 
			rt_kprintf("EGS701GB-III-FCT��ʼ��...\r\n");
			#endif	 
			//Public_PlayTTSVoiceStr("EGS702FCT��ʼ��");
    }
		sucFirstRunflag = 1;
		rt_thread_delay( RT_TICK_PER_SECOND/2 ); 

		Public_ParameterInitialize();
}

/*************************************************************************
*	�� �� ��: Task_DebugCommstrncmp
*	����˵��: �Ƚ�
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
unsigned char Task_DebugCommstrncmp(char *src)
{
    return strncmp(src,(char const *)FCT_recv.buf,strlen(src));
}
/*************************************************************************
*	�� �� ��: App_EyeDebugAck
*	����˵��: Ӧ�������Ϣ
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void App_EyeDebugAck(void)
{
    char buf[100];
    unsigned char temp[30];
    unsigned char count,len; 
    memset(buf,0,66);
    if(E2_DEVICE_ID_LEN==EepromPram_ReadPram(E2_DEVICE_ID,temp))
    {
        strcpy(buf,"OK,");
        Public_ConvertBcdToAsc((unsigned char *)&buf[3],temp,E2_DEVICE_ID_LEN);
    }
    else
    {
        strcpy(buf,"OK,01721140600001");
    }
    len=strlen(buf);
    E2prom_ReadByte(ADDR_COUNT,&count,1);
    if(0xff==count)count = 1;
    sprintf(&buf[len],",EGS701GB-III-FCT,"FCT_SOFT_VER",%d\r",count);
    
		#ifdef	RT_USING_CONSOLE			
			rt_kprintf("%s",buf);
			//stm32_serial1_write(0,(unsigned char *)buf,strlen(buf));
		#endif
    /////////////
    g_fct.debug_f = 1;
}
/*************************************************************************
*	�� �� ��: App_CheckCount
*	����˵��: ��ȡִ�в��Դ�����
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void App_CheckCount(void)
{
    char buf[20];
    u8 count;    
    E2prom_ReadByte(ADDR_COUNT,&count,1); 
    if(count<0xff)count++;
    else count=1; 
    E2prom_WriteByte(ADDR_COUNT,count);
    sprintf(buf,"OK,%d\r",count);
		#ifdef	RT_USING_CONSOLE			
			rt_kprintf("%s",buf);
		#endif
    ////////////////////    
}
/*************************************************************************
*	�� �� ��: Api_CheckPower
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
//ע�⣬��ʾ�����ַ����� ����ָ��ı�����ֻ�ϰ�ǣ�����ȫ��
*************************************************************************/
void Api_CheckPower(void)
{
    char buf[20];
    float vol;
    vol=Adc_MainPower_Readl(); 
    sprintf(buf,"OK,%.0f\r",vol/1000.0+0.5);
		#ifdef	RT_USING_CONSOLE			
			rt_kprintf("%s",buf);
		#endif
}
/*************************************************************************
*	�� �� ��: Api_CheckBattery
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
//ע�⣬��ʾ�����ַ����� ����ָ��ı�����ֻ�ϰ�ǣ�����ȫ��
*************************************************************************/
void Api_CheckBattery(void)
{
    char buf[10];
    float vol;
    //���
    if(FCT_recv.buf[12]=='1')
    {
        //GpioOutOn(BAT_CHARGE);
        vol=Adc_BatteryPower_Readl();
        sprintf(buf,"OK,%.0f\r",vol/1000);
				#ifdef	RT_USING_CONSOLE			
				rt_kprintf(buf);
				#endif
    }
    else
    //�ŵ�
    if(FCT_recv.buf[12]=='0')
    {    
        //GpioOutOff(BAT_CHARGE);
        vol=Adc_BatteryPower_Readl();
        sprintf(buf,"OK,%.0f\r",vol/1000);
				#ifdef	RT_USING_CONSOLE			
				rt_kprintf(buf);
				#endif
    }
    else
    {
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=5\r");
				#endif
    }
}
/*************************************************************************
*	�� �� ��: App_CheckMyself
*	����˵��: �豸�Լ�
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void App_CheckMyself(void)
{
    unsigned char tmp[8];
    unsigned char flag=0;
    unsigned long addr,val,val1;

    //���25LC320A
    E2prom_ReadByte(EE25LC320A_MAX_ADDR,&tmp[0],1);
    E2prom_WriteByte(EE25LC320A_MAX_ADDR,0xaa);
    E2prom_ReadByte(EE25LC320A_MAX_ADDR,&tmp[1],1);
    //д������
    E2prom_WriteByte(EE25LC320A_MAX_ADDR,tmp[0]);
    if(tmp[1]==0xaa)
    {
        flag&=~0x01;//0K
    }
    else
    {
        flag|=0x01;//ERR
        #ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=1,\"93C86\"\r");
				#endif
        return;		
    }
    /////////////////////
    //��ȡBMA250E  
    flag&=~0x02;//0K
    ///////////////////
    //���FM25C160
    tmp[2]=0x5a;
    tmp[3] = FRAM_ReadStatusRegister();
    //���дæ��־
    FRAM_WriteDisable();
    FRAM_BufferWrite(FM25C160_MAX_ADDR,&tmp[2],1);
    FRAM_BufferRead(&tmp[0], 1, FM25C160_MAX_ADDR);
    if(tmp[0]==0x5a)
    {

        flag&=~0x04;//0K
    }
    else
    {
        flag|=0x04;//ERR
        #ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=1,\"FM25C160\"\r");
				#endif
        return;
    }

    //���FLASH AT25DF321   
    addr=FLASH_DATA_MAX_ADDR;
		sFLASH_EraseSector(addr);
    ///////////////////////////////////
    Public_ConvertLongToBuffer(0x12345678,tmp);
		sFLASH_WriteBuffer(tmp, addr, 4);
    ////////////////
    memset(tmp,0,sizeof(tmp));
    sFLASH_ReadBuffer(tmp,addr,4);
    val1=Public_ConvertBufferToLong(tmp);
    if(0x12345678==val1)
    {
        flag&=~0x08;//0K
    }
    else
    {
        flag|=0x08;//ERR
        #ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=1,\"Flash\"\r");
        #endif
				return;
    }
    //���ʱ����
    //��ȡRTCʱ����
    val= RTC_GetCounter();
    if(val != g_fct.time)
    {
        flag&=~0x10;//0K
    }
    else
    {

        flag|=0x10;//ERR
        #ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=1,\"RTC\"\r");
				#endif
        return;
    }
    /*//IIS��Ƶ¼���Լ�
    if(g_fct.iis)
    {
        flag&=~0x20;//0K
    }
    else
    {
        flag|=0x20;//ERR
        FCT_AppSendString("ERR=1,\"IIS\"\r");
        return;
    }*/
    if(!flag)
    {
    	#ifdef	RT_USING_CONSOLE			
			rt_kprintf("OK\r");
			#endif
		}
}

/*************************************************************************
*	�� �� ��: App_CheckGsmGprsTimeOut
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void App_CheckGsmGprsTimeOut(void)
{
    if(false==g_fct.gprs)return;
    g_fct.gprs=false;
		#ifdef	RT_USING_CONSOLE			
		rt_kprintf("ERR=1,\"GPRS=ERR\"\r");
		#endif
}
/*************************************************************************
*	�� �� ��: App_CheckGsmGprs
*	����˵��: ���GSMģ���ͨѶ���ܣ���ȡ͸��ģʽ��ֱ�Ӵ���AT��GSM��GSM�������ݻش�
*	��    �Σ�GPRS/GSM���ָ�� ���ŷָ� OD 0A 
*	�� �� ֵ: ��
//ע�⣬����ָ��ı�����ֻ�ϰ�ǣ�����ȫ��
***************************************************************************/
void App_CheckGsmGprs(void)
{
    unsigned long timeout;
    u8 buf[40],i=0;//tmp_buf[20];
    //��ȡָ����ʱ���׼
    while(FCT_recv.buf[10+i])
    {
        if(FCT_recv.buf[10+i]==',')
            break;
        if(i>30)
            break;
        buf[i]=FCT_recv.buf[10+i+1];
        i++;
    }
    if(FCT_recv.buf[10]!='"'||FCT_recv.buf[10+i-1]!='"')
    {
        //AT����
        #ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=1,\"\"\"or ,\"\r");
				#endif
        return;
    }
    //�����ӳ�ʱ��
    timeout=atoi((char const *)&FCT_recv.buf[10+i+1]); 
    if(0==timeout)//ʱ��Ĭ��
    {
        timeout=10;
    }	
    buf[i-2]='\r';	
    //����ATָ�GSM-GPRSģ��
    g_fct.gprs=true;
    CommTest5_SendData(buf,i-1);
    Public_SetTaskTimer(App_CheckGsmGprsTimeOut,PUBLICSECS(timeout));
}
/*************************************************************************
*	�� �� ��: App_DisposeGprsRecvData
*	����˵��: GSM���ص����ݻش�FCT,������0x0d,0x0a��0x20����
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void App_DisposeGprsRecvData(unsigned char *pBuffer,unsigned short datalen)
{
    char buffer[100];
    unsigned short i;
    unsigned char temp;
    if(false==g_fct.gprs)return;
    g_fct.gprs = false;
    memset(buffer,0,100);
    memcpy(buffer,"OK,",3);
    if(datalen>95)datalen=95;
    for(i=0;i<datalen;i++)
    {
        temp=pBuffer[i];
        if((0x0d==temp)||(0x0a==temp))temp=0x20;
        ///////////////
        buffer[3+i]=temp;
    }
    buffer[3+i++]=0x0d;
    
		#ifdef	RT_USING_CONSOLE			
			rt_kprintf("%s",buffer);
		#endif
}
/*************************************************************************
*	�� �� ��: App_CheckDigitalInput
*	����˵��: ������������ź�
*	��    �Σ�"EYE+SIN"
*	�� �� ֵ: ��
***************************************************************************/
ErrorStatus App_CheckDigitalInput(void)
{
    char data[4];
    unsigned char temp,channel=0;//,i;
    if(FCT_recv.buf[9]==',')
    {
        temp =1;
    }
    else 
    if(FCT_recv.buf[10]==',')
    {								
        temp =2;
    }
    //ָ����մ���
    else
    {
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=3\r");
        #endif
				return ERROR;
    }
    memcpy(data,&FCT_recv.buf[8],temp);
    data[temp]=0;
    channel=atoi(data);
    ////////////////
    ////////////////////

    switch(channel)
    {
				case CHECK_INPUT_DOORI_N:////�Ÿ�����״̬�ź�,����Ч(�ն�Ĭ�ϸߵ�ƽ)
            temp=gpio_pin_read(PIN_NO_DOORI_N);            
            break;
				case CHECK_INPUT_DOOR_TG2://DOOR_TG2
            temp=gpio_pin_read(PIN_NO_DOORI2);                
            break;
         case CHECK_INPUT_ACC://ACC���
            temp=gpio_pin_read(PIN_NO_ACC);	
            break; 
				case CHECK_INPUT_BREAK://�ƶ���ɲ����
            temp=gpio_pin_read(PIN_NO_BREAK);	
            break;                       
        case CHECK_INPUT_HIGH_BEAM://���Զ�۵�
            temp=gpio_pin_read(PIN_NO_DLIGHTI);
            break;   
				case CHECK_INPUT_LOW_LIGHT:
            temp=gpio_pin_read(PIN_NO_XLIGHTI);
						break;
				case CHECK_INPUT_LEFT_LIGHT://��ת���
            temp=gpio_pin_read(PIN_NO_LLIGHTI);           
            break;
        case CHECK_INPUT_RIGHT_LIGHT://��ת���
            temp=gpio_pin_read(PIN_NO_RLIGHTI);
            break;
				case CHECK_INPUT_AIR_CON://�յ�
            temp=gpio_pin_read(PIN_NO_BKHI);           
            break;
        case CHECK_INPUT_SOS://��������,����Ч(�ն�Ĭ�ϸߵ�ƽ)
            temp=gpio_pin_read(PIN_NO_SWITCHI);	
            break;
				case CHECK_INPUT_KEY:////һ��ͨ��,����Ч(�ն�Ĭ�ϸߵ�ƽ)
            temp=gpio_pin_read(PIN_NO_VIRBRATIONI);
            break;
        case CHECK_INPUT_HORN://����
            temp=gpio_pin_read(PIN_NO_HORNI);
            break;
        case CHECK_INPUT_Oil_Pressure://����ѹ����־λ	
            temp=gpio_pin_read(PIN_NO_COIL);    
            break; 
        case CHECK_INPUT_NEAR_LIGHT://�����
            temp=gpio_pin_read(PIN_NO_DETCT1I);             
            break;      
        case CHECK_INPUT_DOORI_P:////��������״̬�ź�
            temp=gpio_pin_read(PIN_NO_DOORI_P);
            break;        
         default:
         		#ifdef	RT_USING_CONSOLE			
						rt_kprintf("ERR=3,\"channel\"\r");
						#endif
            return ERROR;	
    }
    //���ؼ��״̬
    if(temp)
		{		
				#ifdef	RT_USING_CONSOLE			
				rt_kprintf("OK,+\r");
				#endif
    }
		else
		{
				#ifdef	RT_USING_CONSOLE			
				rt_kprintf("OK,-\r");
				#endif
    }
		return SUCCESS;
}
/*************************************************************************
*	�� �� ��: App_CheckDigitalOutput
*	����˵��: �����������ź�
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void App_CheckDigitalOutput(void)
{
    char data[20];
    u8 tmp,channel;
    if(FCT_recv.buf[10]==',')
    {
        if(FCT_recv.buf[11]=='+')
            tmp=1;
        else
            tmp=0;
    }
    else
    {
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=3\r");
        #endif
				return;
    }
    //ͨ��
    if(FCT_recv.buf[9]>'2'||FCT_recv.buf[9]<'1')
    {
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=3,\"channel\"\r");
        #endif
				return;								
    }
    channel=FCT_recv.buf[9];	
    if(0==tmp)
    {
        if(channel=='1')
        {
            gpio_out_on(PIN_NO_HORN_OUT);   
        }
        else//��·����
        {
            gpio_out_on(PIN_NO_COIL);
        }
        strcpy(data,"OK,-\r");
    }
    else
    {
        if(channel=='1')
        {
            gpio_out_off(PIN_NO_HORN_OUT);   
        }
        else//��·����
        {
            gpio_out_off(PIN_NO_COIL);
        }	
        strcpy(data,"OK,+\r");
    }
    ////////////////
    rt_thread_delay( 20 );
		#ifdef	RT_USING_CONSOLE			
		rt_kprintf(data);
		#endif
}
/*************************************************************************
*	�� �� ��: App_CheckAnalogInput
*	����˵��: ��ȡģ�������źŵ�ѹֵ
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void App_CheckAnalogInput(void)
{
    uchar buf[20];
    float vol;

    memset(buf,0,20);
    if(FCT_recv.buf[9]!=',')
    {//Խ�����
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=3\r");
        #endif
				return;
    }		
    //---------------------------------------------	
    Adc_CollectApp_TimeTask();
    //-------------------------------------------				
    //ͨ��
    if(FCT_recv.buf[8]>'2'||FCT_recv.buf[8]<'1')				
    {
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=3\r");
        #endif
				return;								
    }	
    else
    {
        if(FCT_recv.buf[8]=='1')//adc1
        {
            vol=Adc_ExternInputVoltage_1_Read();
        }
        else//ADC2
        {
            vol=Adc_ExternInputVoltage_2_Read();
        }
        //sprintf((char*)buf,"OK,%.0f\r",vol/1000);
				snprintf((char*)buf,20,"OK,%.0f\r",vol/1000);
        	
        #ifdef	RT_USING_CONSOLE			
				rt_kprintf("%s",(char *)buf);
				#endif
    }
}
/*************************************************************************
*	�� �� ��: App_CheckAnalogOutput
*	����˵��: ��ȡģ�������źŵ�ѹֵ
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void App_CheckAnalogOutput(void)
{
    unsigned char channel,onflag;
    uchar buf[20];
    //��ȡʱ��
    memset(buf,0,20);
    if(FCT_recv.buf[10]!=',')
    {//Խ�����
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=3\r");
        #endif
				return;
    }		
    if(FCT_recv.buf[9]>'4'||FCT_recv.buf[9]<'1')				
    {
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=3\r");
        #endif
				return;								
    }	
    else
    {
        channel=FCT_recv.buf[9]-0x30;
        if(FCT_recv.buf[12]==',')
        {
            onflag = FCT_recv.buf[11]-0x30;
        }
        else
        {
            onflag = 1;
        }
        //////////////
        switch(channel)
        {
            case CHECK_OUTPUT_LCD:
                if(onflag)
                gpio_out_on(PIN_NO_LCD_ON);
                else
                gpio_out_off(PIN_NO_LCD_ON);
                break;
            case CHECK_OUTPUT_CAM:
                if(onflag)
                gpio_out_on(PIN_NO_CAM_POWER);
                else
                gpio_out_off(PIN_NO_CAM_POWER);
                break;
            /*case CHECK_OUTPUT_LED:
                if(onflag)
                gpio_out_on(COMM4_PWR);
                else
                gpio_out_off(COMM4_PWR);
                break;*/
        }
    }
    ////////////////////
    rt_thread_delay(30);
    /////////////
    strcpy((char*)buf,"OK\r");
		#ifdef	RT_USING_CONSOLE			
		rt_kprintf((char *)buf);
		#endif
}
/*************************************************************************
*	�� �� ��: App_CheckAntenna
*	����˵��: ���߼��ָ��
*	��    �Σ���
*	�� �� ֵ: ��
//ע�⣬��ʾ�����ַ����� ����ָ��ı�����ֻ�ϰ�ǣ�����ȫ��
***************************************************************************/
void App_CheckAntenna(void)
{
    uchar tmp=0;
    unsigned char channel;
    rt_thread_delay(20);
    channel = FCT_recv.buf[13]-0x30;    
    if(0==channel)//��·���
    {
        tmp=gpio_pin_read(PIN_NO_GPS_OC);
        if(tmp==1)
        {
        		#ifdef	RT_USING_CONSOLE			
						rt_kprintf("OK,0\r");
            #endif
        }
				else
				{
						#ifdef	RT_USING_CONSOLE			
						rt_kprintf("OK,2\r");
        		#endif
				}
    }
    else 
    if(1==channel)//����·
    {
        tmp=gpio_pin_read(PIN_NO_GPS_SC);
        if(tmp==0)
        {
        		#ifdef	RT_USING_CONSOLE			
						rt_kprintf("OK,1\r");
            #endif
        }
				else
				{
						#ifdef	RT_USING_CONSOLE			
						rt_kprintf("OK,2\r");
        		#endif
				}
    }    
    else     	
    {
        tmp=gpio_pin_read(PIN_NO_GPS_OC);;	
        if(tmp==1)
        {
        		#ifdef	RT_USING_CONSOLE			
						rt_kprintf("OK,0\r");
            #endif
						return;
        }
        /////////////
        tmp=gpio_pin_read(PIN_NO_GPS_SC);
        if(tmp==0)
        {
        		#ifdef	RT_USING_CONSOLE			
						rt_kprintf("OK,1\r");
            #endif
						return;
        }
				#ifdef	RT_USING_CONSOLE			
				rt_kprintf("OK,2\r");
				#endif
    }
}
/*
************************************************************************
*	�� �� ��: App_CheckComunication
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
//ע�⣬��ʾ�����ַ����� ����ָ��ı�����ֻ�ϰ�ǣ�����ȫ��
**************************************************************************/
void App_CheckComunication(void)
{
    unsigned char i=0;
    unsigned char channel;
    while(FCT_recv.buf[8+i])
    {
        if(FCT_recv.buf[8+i]==',')
            break;
        i++;
        if(i>20)break;
    };
    if(FCT_recv.buf[8]!='"'||FCT_recv.buf[8+i-1]!='"')
    {
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=3,\"\"\r");
        #endif
				return;				
    }	
    if(FCT_recv.buf[10+i]==',')
    {
        channel=FCT_recv.buf[9+i]-0x30;
        if(channel>6||channel<1)
        {
        		#ifdef	RT_USING_CONSOLE			
						rt_kprintf("ERR=3,\"Channel\"\r");
            #endif
						return;									
        }
    }
    else
    {
    		#ifdef	RT_USING_CONSOLE			
				rt_kprintf("ERR=3,\"Channel\"\r");
        #endif
				return;					
    }
		#ifdef	RT_USING_CONSOLE			
		rt_kprintf("OK\r");
		#endif
}
/*
************************************************************************
*	�� �� ��: Api_CheckPwm
*	����˵��: 
*	��    �Σ�EYE+PWM=10,125,3,3 ��ʾ��Ƶ��Ϊ1HZ��ռ�ձ�Ϊ12.5%������ʱ��3�룬��ʱʱ��3�롣
*	�� �� ֵ: ��
************************************************************************
*/
void Api_CheckPwm(void)
{
    char buf[30],i=0,len,offset;//,tmp;
    while(FCT_recv.buf[8+i])
    {
        if(FCT_recv.buf[8+i]==',')
            break;
        i++;
    };
    ////////////
    i++;
    ///////////
    offset=i;
    //--ռ�ձȼ���
    while(FCT_recv.buf[8+i])
    {
        if(FCT_recv.buf[8+i]==',')
            break;
        i++;
        if(i>(4+offset))//&&i<(2+4))//20)
        {
        		#ifdef	RT_USING_CONSOLE			
						rt_kprintf("ERR=3,\"width\"\r");
            #endif
						return;
            //break;	
        }
    };
    //
    TIM_Cmd(TIM3, ENABLE);   //ʹ�ܶ�ʱ����ʱ
    g_Pluse.flag=true;
    g_Pluse.time=0;
    g_Pluse.count=0;
    g_Pluse.end=0;
    while(!g_Pluse.end)
    {
        ;
    }
		TIM_Cmd(TIM3, DISABLE);   //ʹ�ܶ�ʱ����ʱ
    g_Pluse.count=g_Pluse.count*10;
    sprintf(buf,"OK,%d,",g_Pluse.count);
    len=strlen(buf);
    memcpy(&buf[len],&FCT_recv.buf[8+offset],i-offset);
    buf[len+i-offset]='\r';
    buf[len+i-offset+1]=0;
    	
		#ifdef	RT_USING_CONSOLE			
		rt_kprintf("%s",(char *)buf);
		#endif 
}

/*************************************************************************
*	�� �� ��: Task_DebugCommIncode
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
***************************************************************************/
void Task_DebugCommIncode(void)
{
		if(Task_DebugCommstrncmp("EYE+RESET")==0)
		{
				#ifdef	RT_USING_CONSOLE			
				rt_kprintf("\nsystem would reset after one second\n");
				#endif
				rt_thread_delay( RT_TICK_PER_SECOND ); 				
				NVIC_SystemReset();
				return;
		}
		if(0==g_fct.debug_f)		
		{
				if(Task_DebugCommstrncmp("EYE+DEBUG")==0)
				{
						Public_SetOperateTimer(FCT_AppInit,PUBLICSECS(2*60));
						Public_SetTestTimer(App_EyeDebugAck,PUBLICSECS(1));
						//App_EyeDebugAck();
				}
		} 	
		else
		{
				Public_SetOperateTimer(FCT_AppInit,PUBLICSECS(2*60));
				////////////
				if(Task_DebugCommstrncmp("EYE+CHECKSELF")==0)
				{
						App_CheckMyself();							 
						return;
				} 				
				else	//3����ȡִ�в��Դ�����
				if(Task_DebugCommstrncmp("EYE+COUNT")==0)
				{
						App_CheckCount(); 							
						return;
				}
				else //4��������������ź�
				if(Task_DebugCommstrncmp("EYE+SIN")==0)
				{
						//Public_SetTestTimer(App_CheckDigitalInput,PUBLICSECS(0.3));
						Timer10msStart(TIMER_10MS_ID_2,30,TIMER_MODE_ONCE,App_CheckDigitalInput);
						return;
				} 
				else //5�������������ź�
				if(Task_DebugCommstrncmp("EYE+SOUT")==0)
				{
						App_CheckDigitalOutput(); 							
						return;
				}
				else //6����ȡģ�������źŵ�ѹֵ
				if(Task_DebugCommstrncmp("EYE+VIN=")==0)
				{
						Public_SetTestTimer(App_CheckAnalogInput,PUBLICSECS(0.5));
						return;
				} 	
				else //6S����ȡģ�������źŵ�ѹֵ
				if(Task_DebugCommstrncmp("EYE+VOUT=")==0)
				{
						App_CheckAnalogOutput();							 
						return;
				}
				else //7�����߼��ָ��
				if(Task_DebugCommstrncmp("EYE+GNSSANTE=")==0)
				{
						Public_SetTestTimer(App_CheckAntenna,PUBLICSECS(0.3));							
						return;
				} 																		
				else //8��GPS_GNSS���ָ��
				if(Task_DebugCommstrncmp("EYE+GNSS=")==0)
				{
						if(g_Gnss.gnss_ok)
						{
							#ifdef	RT_USING_CONSOLE			
							rt_kprintf("OK\r");
							#endif
						}
						else
						{
							#ifdef	RT_USING_CONSOLE			
							rt_kprintf("ERR=1\r");
							#endif
						}
						return;
				} 			
				else	//9��GPRS/GSM���ָ�� ���ŷָ� OD 0A 
				if(Task_DebugCommstrncmp("EYE+MBCOM=")==0)
				{
						App_CheckGsmGprs(); 							
						return;
				}
				else	//10��COMͨѶ��  �޸�0XOD 0A �滻��','
				if(Task_DebugCommstrncmp("EYE+COM=")==0)
				{
						App_CheckComunication();								
						return;
				}
				else	 //11�������ѹ���
				if(Task_DebugCommstrncmp("EYE+POWER=")==0)
				{
						Public_SetTestTimer(Api_CheckPower,PUBLICSECS(0.3));
						return;
				}
				else	//12����س�ŵ���  GB-IIIֻ�ǰ������
				if(Task_DebugCommstrncmp("EYE+BATTERY=")==0)
				{
						Api_CheckBattery(); 							 
						return;
				}
				else	//13��PWM�����⣬�����ռ�ձ�
				if(Task_DebugCommstrncmp("EYE+PWM=")==0)
				{
						Api_CheckPwm(); 						 
						return;
				}
				else
				if(Task_DebugCommstrncmp("EYE+DEBUG")==0)
				{
						App_EyeDebugAck();
						return;
				}
				else	//��������
				{
						#ifdef	RT_USING_CONSOLE			
						rt_kprintf("ERR=3\r");	
						#endif
						return;
				} 	 
		}
		
}

/*************************************************************OK
** ��������: fct_app_thread_entry
** ��������: Ӳ����ʱ���߳����
** ��ڲ���: 
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
static void fct_app_thread_entry(void* parameter)
{     
	char buf[FCT_MSG_LEN];

	FCT_AppInit();
	//Public_ParameterInitialize();
	fct_app_msg = rt_mq_create("fct_app_msg",10,5,RT_IPC_FLAG_FIFO);

	while (1)    
	{        
		/* ����Ϣ�����н�����Ϣ */
		if (rt_mq_recv(fct_app_msg, &buf[0], sizeof(buf), RT_WAITING_FOREVER)
		== RT_EOK)
		{			
			if(strstr("fct_debug",buf))
			{
				Task_DebugCommIncode();
			}		
			//#ifdef	RT_USING_CONSOLE	 
			//	rt_kprintf("%s...\r\n",buf);
			//#endif			
			rt_thread_yield();        
		}
	}
}
/*************************************************************OK
** ��������: fct_app_thread_init
** ��������: 
** ��ڲ���: 
** ���ڲ���: 
** ���ز���: 
** ȫ�ֱ���: ��
** ����ģ��:
*************************************************************/
void fct_app_thread_init(void)
{
	rt_err_t result;
	
	result = rt_thread_init(&fct_app_thread,                            
							"fct_app_task",                            
							fct_app_thread_entry,                            
							RT_NULL,                            
							(rt_uint8_t*)&fct_app_stack[0],                            
							sizeof(fct_app_stack),                            
							FCT_APP_THREAD_PRIORITY,                            
							5);    
	if (result == RT_EOK)    
	{        
		rt_thread_startup(&fct_app_thread);    
	} 
}


