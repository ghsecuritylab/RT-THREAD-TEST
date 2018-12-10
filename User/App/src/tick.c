/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : timer.c
* Author             : MCD Application Team 
* Version            : V1.0.0
* Date               : 04/07/2009
* Description        : ��ʱ������.
*                      This file provides template for all exceptions handler
*                      and peripherals interrupt service routine.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

//*******************�ⲿ����************************


//*******************ȫ�ֱ���************************
u32  TimerCount = 0;


/*******************************************************************************
* Function Name  : Timer_Val
* Description    : This function .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u32 Timer_Val(void)
{
  return TimerCount; 
}

/*******************************************************************************
* Function Name  : Timer_ISR
* Description    : This function .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer_ISR(void)
{
  TimerCount++; 
}





