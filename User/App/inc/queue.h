/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2012; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*
*           (2) This file and its dependencies requires IAR v6.20 or later to be compiled.
*
*********************************************************************************************************
*/
#ifndef __QUEUE_H
#define __QUEUE_H


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "stm32f10x.h"


/*
*********************************************************************************************************
*                                             define
*********************************************************************************************************
*/
#define MIN_QUEUE_SIZE  ( 10 )
#define MAX_QUEUE_SIZE  ( 2000 )

//#define CIRQUEUE_SELF_TEST

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
typedef u8 ElementType;

//#define	QUEUE_HAVE_NODE		//�нڵ㹦��
//ѭ������

typedef struct
{
	u16					lens;
}Q_NODE;
typedef struct CirQueueDef
{
  int 				m_iHead;            //����ͷ       
  int 				m_iTail;            //����β
  int 				m_iQueueLenth;      //���г���
  int 				m_iQueueCapacity;   //��������
  #ifdef	QUEUE_HAVE_NODE
  int					m_iNodeHead;				//�ڵ�ͷ
  int					m_iNodeTail;				//�ڵ�β
  int					m_iNodeNum;					//�ڵ���
  int					m_iMaxNodeNum;			//���ڵ���
  Q_NODE			*m_pNode;						//�ڵ�ָ��
  #endif
  ElementType *m_pQueue;          //����ָ��
}xCIRQUEUE;
typedef xCIRQUEUE	CirQueue_t;
typedef void * CirQueueHandle_t;

typedef enum q_state
{
	Q_STATE_SUCCESS =					0u,
	Q_STATE_FAILED,									
	Q_STATE_ENQUEUE_OVERFLOW,				//������,��ӳ��ȳ�����������
	Q_STATE_DEQUEUE_OVERFLOW,				//�������,���ӳ��ȳ�����������
}Q_STATE;

/*********************************************************************************************************
*                                          IsCirQueueEmpty
*
* Description : �����пգ��������=0��Ϊ�գ���ʱû��Ԫ�ؿ��Գ���
*
* Argument(s) : ѭ������ָ��
*
* Return(s)   : ����״̬
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
Q_STATE IsCirQueueEmpty(CirQueueHandle_t xCirQueue);
/*********************************************************************************************************
*                                          IsCirQueueFull
*
* Description : �����������������=���������ʱ������Ԫ�����
*
* Argument(s) : ѭ������ָ��
*
* Return(s)   : ����״̬
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
Q_STATE IsCirQueueFull(CirQueueHandle_t xCirQueue);
/*********************************************************************************************************
*                                          GetCirQueueLength
*
* Description : ��ȡ���г���
*
* Argument(s) : ѭ������ָ��
*
* Return(s)   : ���г���
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
int	GetCirQueueLength(CirQueueHandle_t xCirQueue);
/*********************************************************************************************************
*                                          EnCirQueue
*
* Description : Ԫ�����
*
* Argument(s) : element:����ӵ�Ԫ��   
*								pQ:ѭ������ָ��
*
* Return(s)   : ����״̬
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
Q_STATE EnCirQueue(ElementType element,CirQueueHandle_t xCirQueue);
/*********************************************************************************************************
*                                          BufferEnCirQueue
*
* Description : ��Ԫ�����
*
* Argument(s) : pBuffer:����ӵ�����ָ�� 
*								BufferLen:������ݳ���
*								pQ:ѭ������ָ��
*
* Return(s)   : ����״̬
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
int BufferEnCirQueue(ElementType *pBuffer, int BufferLen, CirQueueHandle_t xCirQueue);

/*********************************************************************************************************
*                                          DeCirQueue
*
* Description : Ԫ�س���
*
* Argument(s) : element:���ӵ�����ָ�� 
*								pQ:ѭ������ָ��
*
* Return(s)   : ����״̬
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
Q_STATE DeCirQueue(ElementType *element,CirQueueHandle_t xCirQueue);
/*********************************************************************************************************
*                                          BufferDeCirQueue
*
* Description : ��Ԫ�س���
*
* Argument(s) : pBuffer:�����ӵ�����ָ�� 
*								BufferLen:�������ݳ���
*								pQ:ѭ������ָ��
*
* Return(s)   : ����״̬
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
int BufferDeCirQueue(ElementType *pBuffer, int BufferLen, CirQueueHandle_t xCirQueue);
/*********************************************************************************************************
*                                          AllBufferDeCirQueue
*
* Description : ����Ԫ�س���
*
* Argument(s) : pBuffer:�����ӵ�����ָ�� 
*								pQ:ѭ������ָ��
*
* Return(s)   : ����״̬
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
int AllBufferDeCirQueue(ElementType *pBuffer,CirQueueHandle_t xCirQueue);
/*********************************************************************************************************
*                                          vCirQueueGenericClear
*
* Description :�������
*
* Argument(s) : pQ:ѭ������ָ��
*
* Return(s)   : none
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
void vCirQueueGenericClear(CirQueueHandle_t xCirQueue);
/*********************************************************************************************************
*                                          xCirQueueGenericCreate
*
* Description :���г�ʼ����ȷ�϶��������������ڴ档ͷβ�ͳ���Ϊ0
*
* Argument(s) : queueCapacity:��������
*
* Return(s)   : ����Ķ���ָ��
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
CirQueueHandle_t xCirQueueGenericCreate(const u32 uxQueueLength);
/*********************************************************************************************************
*                                          xCirQueueGenericStaticCreate
*
* Description :���г�ʼ����ȷ�϶�����������̬�ڴ档ͷβ�ͳ���Ϊ0
*
* Argument(s) : uxQueueLength:�������� pxQueueBuffer :���л���ָ��
*
* Return(s)   : ����Ķ���ָ��
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
CirQueueHandle_t	xCirQueueGenericStaticCreate(const u32 uxQueueLength,ElementType pxQueueBuffer[]);

#ifdef	QUEUE_HAVE_NODE
CirQueueHandle_t xCirQueueGenericDynamicCreate(int queueCapacity, int nodeNum);
#define vDynamicCirQueueCreate( xCirQueue,queueCapacity, nodeNum)											\
	{																																			\
		( xCirQueue ) = xCirQueueGenericDynamicCreate(queueCapacity, nodeNum);						\
	}
#endif
/*********************************************************************************************************
*                                          DestroyCirQueue
*
* Description :���й���
*
* Argument(s) : pQ:ѭ������ָ��
*
* Return(s)   : none
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************/
void DestroyCirQueue(CirQueueHandle_t xCirQueue);

#ifdef CIRQUEUE_SELF_TEST
void CirQueue_Self_Test(void);
#endif

#endif

