/********************************************************************
//��Ȩ˵��	:
//�ļ�����	:GPIOControl.h		
//����		:GPIO ����/�������
//�汾��	:
//������	:yjb
//����ʱ��	:2013.03.09
//�޸���	:
//�޸�ʱ��	:
//�޸ļ�Ҫ˵��	:
//��ע		:1)
//               
***********************************************************************/
#ifndef __GPIOCONTROL_H
#define __GPIOCONTROL_H

#ifdef __cplusplus
 extern "C" {
#endif
   
//****************�����ļ�*****************   
#include "stm32f10x.h"
   
 
//****************�궨��********************
   
//**************�����*******************
#define DLIGHTI_PIN                     GPIO_Pin_13
#define DLIGHTI_GPIO_PORT               GPIOE
#define DLIGHTI_GPIO_CLK                RCC_APB2Periph_GPIOE

#define LLIGHTI_PIN                     GPIO_Pin_10
#define LLIGHTI_GPIO_PORT               GPIOE
#define LLIGHTI_GPIO_CLK                RCC_APB2Periph_GPIOE
   
#define BREAK_PIN                       GPIO_Pin_8
#define BREAK_GPIO_PORT                 GPIOE
#define BREAK_GPIO_CLK                  RCC_APB2Periph_GPIOE   
   
#define ACC_PIN                         GPIO_Pin_7
#define ACC_GPIO_PORT                   GPIOE
#define ACC_GPIO_CLK                    RCC_APB2Periph_GPIOE

#define DOORI_N_PIN                         GPIO_Pin_5
#define DOORI_N_GPIO_PORT                   GPIOC
#define DOORI_N_GPIO_CLK                    RCC_APB2Periph_GPIOC

#define DOORI_P_PIN                         GPIO_Pin_1
#define DOORI_P_GPIO_PORT                   GPIOG
#define DOORI_P_GPIO_CLK                    RCC_APB2Periph_GPIOG

#define DOORI2_PIN                         GPIO_Pin_15//dxl,2013.11.5,ԭ����PE15,������PF15
#define DOORI2_GPIO_PORT                   GPIOF
#define DOORI2_GPIO_CLK                    RCC_APB2Periph_GPIOF

#define LAMP_PIN                            GPIO_Pin_4
#define LAMP_GPIO_PORT                      GPIOC
#define LAMP_GPIO_CLK                       RCC_APB2Periph_GPIOC  

#define LOCK_OUT_PIN                         GPIO_Pin_0
#define LOCK_OUT_GPIO_PORT                   GPIOB
#define LOCK_OUT_GPIO_CLK                    RCC_APB2Periph_GPIOB     

#define UNLOCK_OUT_PIN                         GPIO_Pin_1
#define UNLOCK_OUT_GPIO_PORT                   GPIOB
#define UNLOCK_OUT_GPIO_CLK                    RCC_APB2Periph_GPIOB    
   
#define XLIGHTI_PIN                         GPIO_Pin_14
#define XLIGHTI_GPIO_PORT                   GPIOE
#define XLIGHTI_GPIO_CLK                    RCC_APB2Periph_GPIOE    

#define RLIGHTI_PIN                         GPIO_Pin_12
#define RLIGHTI_GPIO_PORT                   GPIOE
#define RLIGHTI_GPIO_CLK                    RCC_APB2Periph_GPIOE    


#define BKHI_PIN                         GPIO_Pin_9
#define BKHI_GPIO_PORT                   GPIOE
#define BKHI_GPIO_CLK                    RCC_APB2Periph_GPIOE     

#define SWITCHI_PIN                GPIO_Pin_14
#define SWITCHI_GPIO_PORT          GPIOF
#define SWITCHI_GPIO_CLK           RCC_APB2Periph_GPIOF  
   
#define HORNI_PIN                GPIO_Pin_0
#define HORNI_GPIO_PORT          GPIOG
#define HORNI_GPIO_CLK           RCC_APB2Periph_GPIOG    

#define VIRBRATIONI_PIN                GPIO_Pin_13
#define VIRBRATIONI_GPIO_PORT          GPIOF
#define VIRBRATIONI_GPIO_CLK           RCC_APB2Periph_GPIOF      

#define COIL_PIN                GPIO_Pin_2
#define COIL_GPIO_PORT          GPIOB
#define COIL_GPIO_CLK           RCC_APB2Periph_GPIOB   

#define HORN_OUT_PIN                GPIO_Pin_11
#define HORN_OUT_GPIO_PORT          GPIOF
#define HORN_OUT_GPIO_CLK           RCC_APB2Periph_GPIOF   

#define DETCT1I_PIN                GPIO_Pin_11
#define DETCT1I_GPIO_PORT          GPIOB
#define DETCT1I_GPIO_CLK           RCC_APB2Periph_GPIOB  
   
#define DETCT2I_PIN                GPIO_Pin_15
#define DETCT2I_GPIO_PORT          GPIOE
#define DETCT2I_GPIO_CLK           RCC_APB2Periph_GPIOE     


#define GPS_OC_PIN                GPIO_Pin_2
#define GPS_OC_GPIO_PORT          GPIOF
#define GPS_OC_GPIO_CLK           RCC_APB2Periph_GPIOF     

#define GPS_SC_PIN                GPIO_Pin_13
#define GPS_SC_GPIO_PORT          GPIOC
#define GPS_SC_GPIO_CLK           RCC_APB2Periph_GPIOC    

#define GPS_CTR_PIN                GPIO_Pin_6
#define GPS_CTR_GPIO_PORT          GPIOE
#define GPS_CTR_GPIO_CLK           RCC_APB2Periph_GPIOE      

#define MEM_WP_PIN                GPIO_Pin_15
#define MEM_WP_GPIO_PORT          GPIOA
#define MEM_WP_GPIO_CLK           RCC_APB2Periph_GPIOA    
   
#define FLASH_CS_PIN                GPIO_Pin_4
#define FLASH_CS_GPIO_PORT          GPIOA
#define FLASH_CS_GPIO_CLK           RCC_APB2Periph_GPIOA      

#define FR_CS_PIN                GPIO_Pin_8
#define FR_CS_GPIO_PORT          GPIOG
#define FR_CS_GPIO_CLK           RCC_APB2Periph_GPIOG   

#define EPROM_CS_PIN                GPIO_Pin_4
#define EPROM_CS_GPIO_PORT          GPIOG
#define EPROM_CS_GPIO_CLK           RCC_APB2Periph_GPIOG  

#define GSM_ON_PIN                GPIO_Pin_4
#define GSM_ON_GPIO_PORT          GPIOD
#define GSM_ON_GPIO_CLK           RCC_APB2Periph_GPIOD  
   
#define GSM_PWC_PIN                GPIO_Pin_10
#define GSM_PWC_GPIO_PORT          GPIOC
#define GSM_PWC_GPIO_CLK           RCC_APB2Periph_GPIOC    
   
#define GSM_DTR_PIN                GPIO_Pin_5
#define GSM_DTR_GPIO_PORT          GPIOG
#define GSM_DTR_GPIO_CLK           RCC_APB2Periph_GPIOG    
   
#define GSM_RI_PIN                GPIO_Pin_13
#define GSM_RI_GPIO_PORT          GPIOG
#define GSM_RI_GPIO_CLK           RCC_APB2Periph_GPIOG     
   
#define CAM_POWER_PIN                GPIO_Pin_12
#define CAM_POWER_GPIO_PORT          GPIOF
#define CAM_POWER_GPIO_CLK           RCC_APB2Periph_GPIOF       
   
#define CAM_RD_PIN                GPIO_Pin_10
#define CAM_RD_GPIO_PORT          GPIOD
#define CAM_RD_GPIO_CLK           RCC_APB2Periph_GPIOD       
   
#define TTS_RDY_PIN                GPIO_Pin_6
#define TTS_RDY_GPIO_PORT          GPIOG
#define TTS_RDY_GPIO_CLK           RCC_APB2Periph_GPIOG   

#define TTS_P_PIN                GPIO_Pin_7
#define TTS_P_GPIO_PORT          GPIOG
#define TTS_P_GPIO_CLK           RCC_APB2Periph_GPIOG     
  

#define LCD_ON_PIN                GPIO_Pin_11
#define LCD_ON_GPIO_PORT          GPIOC
#define LCD_ON_GPIO_CLK           RCC_APB2Periph_GPIOC      

#define LCD_CS_PIN                GPIO_Pin_15
#define LCD_CS_GPIO_PORT          GPIOG
#define LCD_CS_GPIO_CLK           RCC_APB2Periph_GPIOG    

#define LCD_RST_PIN                GPIO_Pin_8
#define LCD_RST_GPIO_PORT          GPIOA
#define LCD_RST_GPIO_CLK           RCC_APB2Periph_GPIOA    
   
#define LCD_AO_PIN                GPIO_Pin_3
#define LCD_AO_GPIO_PORT          GPIOD
#define LCD_AO_GPIO_CLK           RCC_APB2Periph_GPIOD    
   
#define LCD_SPI_SCK_PIN                GPIO_Pin_0
#define LCD_SPI_SCK_GPIO_PORT          GPIOE
#define LCD_SPI_SCK_GPIO_CLK           RCC_APB2Periph_GPIOE       

#define LCD_SPI_MISO_PIN                GPIO_Pin_8
#define LCD_SPI_MISO_GPIO_PORT          GPIOC
#define LCD_SPI_MISO_GPIO_CLK           RCC_APB2Periph_GPIOC 
   
#define LCD_SPI_MOSI_PIN                GPIO_Pin_1
#define LCD_SPI_MOSI_GPIO_PORT          GPIOE
#define LCD_SPI_MOSI_GPIO_CLK           RCC_APB2Periph_GPIOE    

#define CAN_CTR_MOSI_PIN                GPIO_Pin_15
#define CAN_CTR_MOSI_GPIO_PORT          GPIOD
#define CAN_CTR_MOSI_GPIO_CLK           RCC_APB2Periph_GPIOD    

#define SHOCK_CS_MOSI_PIN                GPIO_Pin_7
#define SHOCK_CS_MOSI_GPIO_PORT          GPIOD
#define SHOCK_CS_MOSI_GPIO_CLK           RCC_APB2Periph_GPIOD   
 
#define V_COL_MOSI_PIN                GPIO_Pin_7
#define V_COL_MOSI_GPIO_PORT          GPIOC
#define V_COL_MOSI_GPIO_CLK           RCC_APB2Periph_GPIOC    

#define IC_P_MOSI_PIN                GPIO_Pin_9
#define IC_P_MOSI_GPIO_PORT          GPIOC
#define IC_P_MOSI_GPIO_CLK           RCC_APB2Periph_GPIOC     
   
#define BUZZER_PIN                      GPIO_Pin_12
#define BUZZER_GPIO_PORT                GPIOG
#define BUZZER_GPIO_CLK                 RCC_APB2Periph_GPIOG
   
#define	MIC_EN_PIN			GPIO_Pin_5//dxl,2013.5.15,PD5��IC�����ڹ���
#define MIC_EN_GPIO_PORT                GPIOD
#define MIC_EN_GPIO_CLK                 RCC_APB2Periph_GPIOD 
	 
#define	I2S_AD_DA_PIN			GPIO_Pin_2//dxl,2013.5.16,PG2
#define I2S_AD_DA_GPIO_PORT             GPIOG
#define I2S_AD_DA_GPIO_CLK              RCC_APB2Periph_GPIOG 
	 
#define	I2S_PWDAN_PIN			GPIO_Pin_12//dxl,2013.5.16,PD12
#define I2S_PWDAN_GPIO_PORT             GPIOD
#define I2S_PWDAN_GPIO_CLK              RCC_APB2Periph_GPIOD 
	 
#define	I2S_PWADN_PIN			GPIO_Pin_11//dxl,2013.5.16,PD11
#define I2S_PWADN_GPIO_PORT             GPIOD
#define I2S_PWADN_GPIO_CLK              RCC_APB2Periph_GPIOD 
	 
#define	SD_POWER_PIN			GPIO_Pin_3//dxl,2013.5.16,PG3
#define SD_POWER_GPIO_PORT             GPIOG
#define SD_POWER_GPIO_CLK              RCC_APB2Periph_GPIOG 
   
#define PWR_TYPE_PIN                    GPIO_Pin_3//dxl,2013.5.26,PF3  
#define PWR_TYPE_GPIO_PORT             GPIOF
#define PWR_TYPE_GPIO_CLK              RCC_APB2Periph_GPIOF 
	 
#define SD_DETECT_PIN                    GPIO_Pin_13//dxl,2013.8.16,PD13 
#define SD_DETECT_GPIO_PORT             GPIOD
#define SD_DETECT_GPIO_CLK              RCC_APB2Periph_GPIOD 
	 
//****************�ṹ����*******************   
//�����,����ű��
typedef enum 
{
  //CON5�ӿ�,32PIN�ӿ�
  DLIGHTI = 0,         //���(Զ���),����,����Ч(������),����[BIG_LIGHT]E13
  LLIGHTI,             //��ת��,����,����Ч(������),����[RIGHT_LIGHT]E10
  BREAK,               //ɲ��,����,����Ч(������)E8
  ACC,                 //ACC,����,����Ч(������)E7
  DOORI_N,             //����1,����,����Ч(������)C5
  DOORI_P,             //����1,����,����Ч(������)G1
  DOORI2,              //����2,����,������,Ĭ�ϵ���Ч(������)F15
  LAMP,                //ת���,���,����[TURN_LIGHT]C4
  LOCK_OUT,            //�п���-��,���,B0
  UNLOCK_OUT,          //�п���-��,���,B1
  XLIGHTI,             //С��,����,����Ч,����[LITTLE_LIGHT]E14
  RLIGHTI,             //��ת��,����,����Ч(������)E12
  BKHI,                //�յ�,����,����Ч(������),����[AIR_CONDITION]  E9
  SWITCHI ,            //��������,����,  F14
  HORNI,               //��������,����,Ĭ�ϸ���Ч(������)G0
  VIRBRATIONI,         //һ��ͨ��,����,F13
  COIL,                //����·,���,����[OIL_CUT]B2
  HORN_OUT,            //��������,���,F11
  //CON6,16PIN�ӿ�
  DETCT1I,             //�����,����,,����[NEAR_LIGHT]B11
  DETCT2I,             //����ѹ��,����,,����[GAS_PRESS]E15
  //GNSSģ��
  GPS_OC,              //���߶Ͽ�,����,����[ANT_SHUT]F2
  GPS_SC,              //���߶�·,����,����[ANT_SHORT]C13
  GPS_CTR,             //GPS��Դ���ƽ�,���E6
  //�洢Ƭѡ�ߺ�ʹ����
  MEM_WP,             //�洢д����ʹ����,���A15
  FLASH_CS,           //FlashƬѡ��,���A4
  FR_CS,              //����Ƭѡ��,���G8
  EPROM_CS,           //EEPROMƬѡ��,���G4
  //ͨѶģ����ƽ�
  GSM_ON,             //ͨѶģ�鿪����,���D4
  GSM_PWC,            //ͨѶģ���Դ���ƽ�,���C10
  GSM_DTR,            //ͨѶģ��DTR��,���G5
  GSM_RI,             //ͨѶģ�������,����G13
  //����ͷ���ƽ�
  CAM_POWER,          //����ͷ��Դ���ƽ�,���F12
  CAM_RD,             //����ͷ485��д����,���   D10
  //TTS���ƽ�
  TTS_RDY,            //TTS��������������,����G6
  TTS_P,              //TTS��Դ���ƽ�,���G7
  //LCD���ƽ�
  LCD_ON,             //LCD��Դ���ƽ�,���C11
  LCD_CS,             //LCDƬѡ��,���G15
  LCD_RST,             //LCD��λA8
  LCD_AO,             //LCD�Ĵ���ѡ��,���D3
  LCD_SPI_SCK,        //LCD SPIʱ���ź�,���E0
  LCD_SPI_MISO,       //LCD SPI�ź�����,����C8
  LCD_SPI_MOSI,       //LCD SPI�ź����,���E1
  //CAN����
  CAN_CTR,            //CAN��Դ����,���  D15
  //BMA220�𶯴�����
  SHOCK_CS,           //�𶯴�������ַѡ��  D7
  //���ȿ���
  V_COL,//C7
  //ic ����Դ����
  IC_P,//C9
  //����
  BUZZER ,             //������,���,G12
  //��˷�ʹ�ܿ���D5
  MIC_EN,
  //I2S_AD/DA  G2
  I2S_AD_DA,
  //I2S_PWDAN  D12
  I2S_PWDAN,
    //I2S_PWADN D11
   I2S_PWADN,
   //SD������� G3
   SD_POWER,
   //POWER TYPE  F3
   PWR_TYPE,
   //SD������  D13
   SD_DETECT,
  
  GPIO_OUT_IN_MAX,
} GPIO_OUT_IN_NUM;   

//����ģʽ
typedef enum 
{  
  GPIO_IN_MODE_GPIO = 0,   // ��ͨģʽ
  GPIO_IN_MODE_EXTI = 1    // �ⲿ�ж�ģʽ
} GPIO_IN_Mode;

//****************�ⲿ����*******************

//****************ȫ�ֱ���*******************

//****************��������*******************
void GpioOutInit(GPIO_OUT_IN_NUM IoNum);
void GpioOutOn(GPIO_OUT_IN_NUM IoNum);
void GpioOutOff(GPIO_OUT_IN_NUM IoNum);
void GpioOutToggle(GPIO_OUT_IN_NUM IoNum);

void GpioInInit(GPIO_OUT_IN_NUM IoNum);
u8 GpioInGetState(GPIO_OUT_IN_NUM IoNum);

#ifdef __cplusplus
}
#endif

#endif /* __GPIOCONTROL_H */