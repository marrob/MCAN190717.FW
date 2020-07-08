/**
  ******************************************************************************
  * @file    can_net.c
  * @author  Margit R�bert
  * @version 0.0.1
  * @date    2019.05.30

  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "candbeng.h"
#include <stdio.h>
#include "main.h"

static void ConvertVarToCanMsg(void *pVar, uint8_t startBit, uint8_t bits, uint8_t data[]);
static void ConvertCanMsgToVar(void * pValue, uint8_t startBit, uint8_t bits, uint8_t data[]);

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
/**@brief Eszk�z incializ�l�sa
  *@retval status
  */
uint8_t CanDbEngInit(  CanDbEng_Type *hnet, 
                     uint8_t nodeType,
                     CanDbEngMessageItem_Type *msg,
                     uint8_t msgCount ,
                     CanDbEngSignalItem_Type *sig,
                     uint8_t sigCount)
{
  hnet->pMsg = msg;
  hnet->MsgCount = msgCount;

  hnet->pSig = sig;
  hnet->SigCount = sigCount;

  return CANDBENG_OK;
}
/**@brief Task
  *@retval status
  */
uint8_t CanDbEngTask(CanDbEng_Type *hnet)
{
  uint8_t status = CANDBENG_OK;

  for(uint8_t i = 0; i < hnet->MsgCount; i++)
  {
    CanDbEngMessageItem_Type *msg;
    msg = &((CanDbEngMessageItem_Type*)(hnet->pMsg))[i];
    
    if((msg->IsPeriod == 1 && msg->IsTx == 1) || (msg->IsPeriod == 0 && msg->IsTx == 1 && msg->SingleTxRequied == 1) )
    {
      int32_t now = HAL_GetTick();
      if(((now - msg->LastSentTimestamp) >= msg->PeriodTime) || msg->SingleTxRequied == 1 )
      {
        msg->LastSentTimestamp = now;
        msg->Data = 0;
        for(uint8_t j = 0; j < hnet->SigCount; j++)
        {
          CanDbEngSignalItem_Type *sig;
          sig = &((CanDbEngSignalItem_Type*)hnet->pSig)[j];
          if (msg->Id == sig->MsgId)
          {
            ConvertVarToCanMsg(sig->pValue,sig->StartBit, sig->Bits, msg->DataArray);
#if (CANDBENG_DEBUG_LEVEL > 0)
            if(sig->Type == CANDBENG_FLOAT)
            {
            CanDbEngDbgLog("TX: %s.%s %f %ld",
                         msg->Name,
                         sig->Name, 
                         *(double*)sig->pValue, 
                         sig->Cnt++);
            }
            else if(sig->Type == CANDBENG_UNSIGNED)
            {
              CanDbEngDbgLog("TX: %s.%s %d %ld",
                           msg->Name,
                           sig->Name, 
                           *(uint16_t*)sig->pValue, 
                           sig->Cnt++);
            }
#endif
          }
        }
        status = CanDbEngWriteMsgLowLevel(msg->Id, (uint8_t*)&msg->DataArray, msg->DLC);
        if(status != CANDBENG_OK)
        {
            CanDbEngErrLog("TX %s",msg->Name);
            break;
        }
        else
        {
          if(msg->SingleTxRequied)
            msg->SingleTxRequied = 0;
        }
      }
    }
  }
return status;
}
/*ToDO Weak nem mÜködik... megoldást kellne rá találni
 * __weak uint8_t CanDbEngWriteMsgLowLevel(uint32_t arbId, uint8_t *data, size_t size)
{
  return CANDBENG_NOT_IMPLEMENTED;
}
*/

uint8_t CanDbEngReadMsgLowLevel(CanDbEng_Type *context, uint32_t arbId, uint8_t *data, size_t size)
{
  for(uint8_t i=0; i<context->MsgCount; i++)
  {
    CanDbEngMessageItem_Type *msg;
    msg = &((CanDbEngMessageItem_Type*)(context->pMsg))[i];

    if( (msg->Id == arbId) && (msg->IsTx == 0))
    {
         if(msg->pInComeNotify != NULL)
            msg->pInComeNotify();
        /*** Look for signals to Message ***/
        for(uint8_t j = 0; j < context->SigCount; j++)
        {      
          CanDbEngSignalItem_Type *sig;
          sig = &((CanDbEngSignalItem_Type*)context->pSig)[j];

          if (msg->Id == sig->MsgId) /*** Keresem a bejovo uzenethez a signalokat ***/
          {
              ConvertCanMsgToVar(sig->pValue,sig->StartBit,sig->Bits, data);
              if(sig->Type == CANDBENG_FLOAT)
              {
                CanDbEngDbgLog("RX: 0x%x",*(uint16_t*)sig->pValue);
                *((double*)sig->pValue) = *(uint16_t*)sig->pValue * sig->Factor;
                *((double*)sig->pValue) += sig->Offset;
              }
              else
              {
                *((uint16_t*)sig->pValue) =  *(uint16_t*)sig->pValue;
                *((uint8_t*)sig->pValue) += sig->Offset;
              }

#if (CANDBENG_DEBUG_LEVEL > 0)
            if(sig->Type == CANDBENG_FLOAT)
            {
              CanDbEngDbgLog("RX: %s.%s %f%s %ld",
                           msg->Name,
                           sig->Name, 
                           *(double*)sig->pValue, 
                           sig->Unit,
                           sig->Cnt++);
            }
            else if(sig->Type == CANDBENG_UNSIGNED)
            {
              CanDbEngDbgLog("RX: %s.%s %d%s %ld",
                           msg->Name,
                           sig->Name, 
                           *(uint16_t*)sig->pValue,
                           sig->Unit, 
                           sig->Cnt++);
            }
#endif
             if(sig->pChangeNotify!= NULL)
               sig->pChangeNotify();
          }
        }
    }
  }
  return CANDBENG_OK ;
}


uint8_t CanDbEngSendMessage(CanDbEng_Type *context, uint32_t arbId)
{
  for(uint8_t i=0; i<context->MsgCount; i++)
  {
    CanDbEngMessageItem_Type *msg;
    msg = &((CanDbEngMessageItem_Type*)(context->pMsg))[i];

    if( (msg->Id == arbId) && (msg->IsTx == 1) && (msg->IsPeriod == 0) )
    {
      msg->SingleTxRequied = 1;
    }
  }
  return CANDBENG_OK ;
}
void ConvertVarToCanMsg(void *pValue, uint8_t startBit, uint8_t bits, uint8_t data[])
{
  uint8_t byteIndex = startBit / 8;
  uint8_t byteLen = bits / 8;
  uint8_t bitLen = bits % 8;
  uint8_t mask;

  for(int i = 0; i < byteLen; i++)
  {
    data[byteIndex] = 0;
    data[byteIndex--] = *((uint8_t*)(pValue)+i);
  }

  if(bitLen)
  {
     mask = 1;
     for(int i = 0; i < bitLen; i++)
     {
       data[byteIndex] &= (uint8_t)~(mask << startBit % 8);
       mask <<= 1;
     }
     mask = 1;
     for(int i = 0; i < bitLen; i++)
     {
       data[byteIndex] |= (*((uint8_t*)(pValue))& mask) << startBit % 8;
       mask <<=1;
     }
  }
}
static void ConvertCanMsgToVar(void * pValue, uint8_t startBit, uint8_t bits, uint8_t data[])
{
  uint8_t byteIndex = startBit / 8;
  uint8_t byteLen = bits / 8;
  uint8_t bitLen = bits % 8;

  for(int i = 0; i < byteLen; i++)
  {
    uint8_t dbg = 0;
    if(byteIndex != 0)
      dbg = data[byteIndex--];
    else
      dbg = data[0];

    *((uint8_t*)(pValue ) + i) =  dbg;
  }

  if(bitLen)
  {
     uint8_t mask = 1 << startBit%8;
     uint8_t temp = 0;
     for(int i = 0; i < bitLen; i++)
     {
       temp |= data[byteIndex] & mask;
       mask<<=1;
     }
     temp >>= startBit % 8;
     *((uint8_t*)(pValue)) = temp;
  }
}
/************************ (C) COPYRIGHT Konvol�ci� **********END OF FILE****/

