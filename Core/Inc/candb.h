
#ifndef _CANDB__H_
#define _CANDB__H_ 1
/* Includes ------------------------------------------------------------------*/
#include "candbeng.h"

/* Public define -------------------------------------------------------------*/
#define NODE_PC           0x01
#define NODE_BMS          0x05

#define MSG_BMS2_RN1                    0x36C
#define MSG_HEVC_RN4                    0x373
#define MSG_SW_VERSION_SFTY             0x6BF
#define MSG_LOGICAL_OUTPUTS_SFTY        0x6CF
#define MSG_ASIC0_DATA_1_MAIN           0x710
#define MSG_ASIC0_DATA_2_MAIN           0x711
#define MSG_ASIC0_DATA_3_MAIN           0x712
#define MSG_ASIC_VCELL_MAIN             0x73D
#define MSG_LOGICAL_OUTPUTS_MAIN        0x7CF
#define MSG_ASIC_REGISTER_MAIN          0x73C

/* Public variables ----------------------------------------------------------*/
extern CanDbEngMessageItem_Type CanDbMessages[];
extern CanDbEngSignalItem_Type CanDbSignals[];


/* Exported functions --------------------------------------------------------*/
int CanDbGetMessagesCount(void);
int CanDbGetSignalsCount(void);

#endif //_CANDB__H_
/************************ (C) COPYRIGHT Konvolúció **********END OF FILE****/
