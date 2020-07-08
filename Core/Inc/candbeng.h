/**
  ******************************************************************************
  * @file    CanDbEng.h
  * @author  Margit R�bert
  * @version 0.0.0
  * @date    2019.05.30
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 Konvol�ci�</center></h2>
  *******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CAN_DB_ENG__H_
#define _CAN_DB_ENG__H_ 1
/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#define CANDBENG_DEBUG_LEVEL      3
/* Public define -------------------------------------------------------------*/

#define CANDBENG_OK               0
#define CANDBENG_FAIL             1
#define CANDBENG_NOT_IMPLEMENTED  2
#define CANDBENG_MSG_TX_FAIL      3
#define CANDBENG_UNIT_NAME_SIZE   8
#define CANDBENG_SIGNAL_NAME_SIZE 32
#define CANDBENG_BROADCAST_MSG  0x01


/* Debug Macros --------------------------------------------------------------*/
#if (CANDBENG_DEBUG_LEVEL > 0)
#define  CanDbEngUsrLog(...)  {printf(__VA_ARGS__);\
                             printf("\r\n");}
#else
#define CanDbEngUsrLog(...)
#endif

#if (CANDBENG_DEBUG_LEVEL > 1)

#define  CanDbEngErrLog(...)  {printf("ERROR.CANDBENG:") ;\
                             printf(__VA_ARGS__);\
                             printf("\r\n");}
#else
#define CanDbEngErrLog(...)
#endif

#if (CANDBENG_DEBUG_LEVEL > 2)
#define  CanDbEngDbgLog(...)  {printf("DEBUG.CANDBENG:") ;\
                             printf(__VA_ARGS__);\
                             printf("\r\n");}
#else
#define CanDbEngDbgLog(...)
#endif

/* Public typedef ------------------------------------------------------------*/
typedef enum _CanDbEngDataType
{
  CANDBENG_UNSIGNED,
  CANDBENG_SIGNED,
  CANDBENG_FLOAT,
}CanDbEngDataType_Type;

typedef struct _CanDbEngMessageItem
{
  char Name[CANDBENG_SIGNAL_NAME_SIZE];
  uint32_t Id;
  uint8_t DLC;
  uint8_t IsTx;
  uint8_t IsPeriod;
  uint32_t PeriodTime;
  void (*pInComeNotify)();
  uint64_t Data;
  uint8_t DataArray[8];
  int32_t LastSentTimestamp;
  uint8_t SingleTxRequied;
}CanDbEngMessageItem_Type;

typedef struct _CanDbEngSignalItem
{
  char Name[CANDBENG_SIGNAL_NAME_SIZE];
  uint32_t MsgId;
  void (*pValue);
  int StartBit;
  int Bits;
  CanDbEngDataType_Type Type;
  double Factor;
  double Offset;
  char Unit[CANDBENG_UNIT_NAME_SIZE];
  void (*pChangeNotify)();
  uint32_t Cnt;

}CanDbEngSignalItem_Type;


typedef  struct _CanDbEng_Type
{
  CanDbEngMessageItem_Type *pMsg;
  uint8_t MsgCount;

  CanDbEngSignalItem_Type *pSig;
  uint8_t SigCount;

}CanDbEng_Type;

/* Exported functions --------------------------------------------------------*/
extern uint32_t HAL_GetTick(void);

uint8_t CanDbEngInit(CanDbEng_Type *context, uint8_t nodeTypeId,
                                         CanDbEngMessageItem_Type *msg,
                                         uint8_t msgCount ,
                                         CanDbEngSignalItem_Type *sig,
                                         uint8_t sigCount);
uint8_t CanDbEngTask(CanDbEng_Type *context);
uint8_t CanDbEngSendMessage(CanDbEng_Type *context, uint32_t arbId);

uint8_t CanDbEngReadMsgLowLevel(CanDbEng_Type *context, uint32_t arbId, uint8_t *data, size_t size);
__weak uint8_t CanDbEngWriteMsgLowLevel(uint32_t arbId, uint8_t *data, size_t size);

#endif //_CAN_DB_ENG__H_
/************************ (C) COPYRIGHT Konvol�ci� **********END OF FILE****/
