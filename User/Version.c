/*******************************************************************************
 * File Name:           Version.c
 * Function Describe:   
 * Relate Module:		Version.h
 * Writer:              joneming
 * Date:                2014-4-11
 * Rewriter:            joneming
 ******************************************************************************/
#include "include.h"
//////////////////////////
#define SOFTVERSION                 01//�汾��:��λ:��ʾ��ǰ�汾��
/////////////////////////////////////////
#define FIRMWARE_TIME               "201404140940"//����ʱ��
///////////////////////////////////////////////
#define HARDWARE_VERSION             "Ver:1.41"//Ӳ���汾��
///////////////////////////////
#if (MOD_TYPE == GPRS_MODULE_M10)//��������
#define NETWORK_TYPE                11//��λ:��ʾ��������:������ʾG��ͨ�ð汾
#else
#define NETWORK_TYPE                12//��λ:��ʾ��������:ż����ʾG��ͨ�ð汾
#endif
/////////////////////////////////
//////////���º겻��Ҫ�޸�///////
//////////////////////////////////////////////
#define SOFTVERSIONS                STR(SOFTVERSION)
#define NETWORK_TYPES               STR(NETWORK_TYPE)
#define FIRMWARE_VERSION            "2"NETWORK_TYPES""SOFTVERSIONS//�汾�Ź�5λ���֣�//�̼��汾��,2��ʾ702,01��ʾG��ͨ�ð汾,02��ʾC��ͨ�ð�(��Ϊģ��),04��ʾCͨ�ð�(����ģ��)
///////////////////////////////
#define FIRMWARE_INFORMATION        "Ver:"FIRMWARE_VERSION"_"FIRMWARE_TIME//�̼���Ϣ(�����汾�ż�����)
///////////////////////////////////
/********************************************
 * Function: Version_UpdateSoftVersion
 * Describe: ���µ�ǰ����汾��
**********************************************/
void Version_UpdateSoftVersion(void)
{
    EepromPram_WritePram(E2_FIRMWARE_VERSION_ID,(unsigned char *)FIRMWARE_VERSION, E2_FIRMWARE_VERSION_ID_LEN);
}
/********************************************
 * Function: Version_GetFirmwareInformation
 * Describe: ��ȡ��ǰ�̼���Ϣ(�汾��+��������)
 * ����    : ����
**********************************************/
unsigned char Version_GetFirmwareInformation(unsigned char *buffer)
{
    strcpy((char *)buffer,FIRMWARE_INFORMATION);
    return strlen(FIRMWARE_INFORMATION);
}
/********************************************
 * Function: Version_GetFirmwareInformation
 * Describe: ��ȡ��ǰӲ����Ϣ(�汾��)
 * ����    : ����
**********************************************/
unsigned char Version_GetHardwareInformation(unsigned char *buffer)
{
    strcpy((char *)buffer,HARDWARE_VERSION);
    return strlen(HARDWARE_VERSION);
}
/******************************************************************************
								EndModule
******************************************************************************/