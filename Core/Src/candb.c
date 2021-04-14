/* Includes ------------------------------------------------------------------*/
#include "candb.h"
#include "main.h"

CanDbEngMessageItem_Type CanDbMessages[] = 
{
  /*  Name                  Id,                       DLC, IsTx, IsPeriod, PeriodTime, pInComeNotify       */
  /*01234567890123456                                                                         */
  /*** Tx by RBMS ***/
  { "BMS2_RN1",              MSG_BMS2_RN1,             8,   0,   0,        0,        NULL               },
  { "SW_VERSION_SFTY",       MSG_SW_VERSION_SFTY,      8,   0,   0,        0,        NULL               },
  { "ASIC0_DATA_1_MAIN",     MSG_ASIC0_DATA_1_MAIN,    8,   0,   0,        0,        NULL               },
  { "ASIC0_DATA_2_MAIN",     MSG_ASIC0_DATA_2_MAIN,    8,   0,   0,        0,        NULL               },
  { "ASIC0_DATA_3_MAIN",     MSG_ASIC0_DATA_3_MAIN,    8,   0,   0,        0,        NULL               },

  /*** Tx by PC ***/
  { "HEVC_RN4",              MSG_HEVC_RN4,             8,   1,   /*1*/1,   100,      NULL               }, /*Message HEVC_RN4 transmitted on CAN ETS from HEVC*/
  { "LOGICAL_OUTPUTS_MAIN",  MSG_LOGICAL_OUTPUTS_MAIN, 1,   1,   /*1*/1,   100,      NULL               },
  { "LOGICAL_OUTPUTS_SFTY",  MSG_LOGICAL_OUTPUTS_SFTY, 2,   1,   /*1*/1,   100,      NULL               },
  { "ASIC_VCELL_MAIN",       MSG_ASIC_VCELL_MAIN,      2,   1,   /*1*/1,   100,      NULL               },
  { "ASIC_REGISTER_MAIN",    MSG_ASIC_REGISTER_MAIN,   4,   1,   0,        0,        NULL               },
}; 


CanDbEngSignalItem_Type CanDbSignals[] = 
{

  /*Name,                            MsgId,                    pValue,                                   StartBit, Bits, Type,              Factor,       Offset, Unit,  pChangeNotify */
  /*01234567890123456,               01234567890123456                                                                                                                           */
  /*** Tx by MCEL ***/
  { "SW_VERSION_SFTY",               MSG_SW_VERSION_SFTY,      &Device.BMS.SW_VERSION_SFTY,               0,      16,    CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "HEVC_WakeUpSleepCommand",       MSG_HEVC_RN4,             &Device.BMS.HEVC_WakeUpSleepCommand,       6,      2,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "ETS_SleepMode",                 MSG_HEVC_RN4,             &Device.BMS.ETS_SleepMode,                 8,      2,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "LBCPRUNKey",                    MSG_HEVC_RN4,             &Device.BMS.LBCPRUNKey,                    16,     8,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "OperatingTypeRequest",          MSG_HEVC_RN4,             &Device.BMS.OperatingTypeRequest,          37,     3,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "IgnitionSupplyConfirmation_HV", MSG_HEVC_RN4,             &Device.BMS.IgnitionSupplyConfirmation_HV, 40,     1,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "PowerRelayState",               MSG_HEVC_RN4,             &Device.BMS.PowerRelayState,               62,     2,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "GADE_HV",                       MSG_HEVC_RN4,             &Device.BMS.GADE_HV,                       56,     3,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "SHDN_MCU_ASIC",                 MSG_LOGICAL_OUTPUTS_MAIN, &Device.BMS.SHDN_MCU_ASIC,                 6,      1,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "IMMEDITATE_APPLY",              MSG_LOGICAL_OUTPUTS_MAIN, &Device.BMS.IMMEDITATE_APPLY,              0,      1,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "SHDN_MCU_ASIC_SFTY",            MSG_LOGICAL_OUTPUTS_SFTY, &Device.BMS.SHDN_MCU_ASIC_SFTY,            0,      1,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "IMMEDITATE_APPLY_SFTY",         MSG_LOGICAL_OUTPUTS_SFTY, &Device.BMS.IMMEDITATE_APPLY_SFTY,         7,      1,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "ASIC_VCELL_DATA",               MSG_ASIC_VCELL_MAIN,      &Device.BMS.ASIC_VCELL_DATA,               8,      16,    CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "ASIC0_CELL1",                   MSG_ASIC0_DATA_1_MAIN,    &Device.BMS.ASIC0_CELL1,                   8,      16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL2",                   MSG_ASIC0_DATA_1_MAIN,    &Device.BMS.ASIC0_CELL2,                   24,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL3",                   MSG_ASIC0_DATA_1_MAIN,    &Device.BMS.ASIC0_CELL3,                   40,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL4",                   MSG_ASIC0_DATA_1_MAIN,    &Device.BMS.ASIC0_CELL4,                   56,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL5",                   MSG_ASIC0_DATA_2_MAIN,    &Device.BMS.ASIC0_CELL5,                   8,      16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL6",                   MSG_ASIC0_DATA_2_MAIN,    &Device.BMS.ASIC0_CELL6,                   24,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL7",                   MSG_ASIC0_DATA_2_MAIN,    &Device.BMS.ASIC0_CELL7,                   40,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL8",                   MSG_ASIC0_DATA_2_MAIN,    &Device.BMS.ASIC0_CELL8,                   56,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL9",                   MSG_ASIC0_DATA_3_MAIN,    &Device.BMS.ASIC0_CELL9,                   8,      16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL10",                  MSG_ASIC0_DATA_3_MAIN,    &Device.BMS.ASIC0_CELL10,                  24,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL11",                  MSG_ASIC0_DATA_3_MAIN,    &Device.BMS.ASIC0_CELL11,                  40,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC0_CELL12",                  MSG_ASIC0_DATA_3_MAIN,    &Device.BMS.ASIC0_CELL12,                  56,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC_REG_ID",                   MSG_ASIC_REGISTER_MAIN,   &Device.BMS.AISC_REG_ID,                   0,      8,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "ASIC_REG_DATA",                 MSG_ASIC_REGISTER_MAIN,   &Device.BMS.ASIC_REG_DATA,                 16,     16,    CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "ASIC_R_W",                      MSG_ASIC_REGISTER_MAIN,   &Device.BMS.ASIC_R_W,                      31,     1,     CANDBENG_UNSIGNED,  1,            0,     "-",   NULL },
  { "ASIC1_CELL1",                   MSG_ASIC1_DATA_1_MAIN,    &Device.BMS.ASIC1_CELL1,                   8,      16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL2",                   MSG_ASIC1_DATA_1_MAIN,    &Device.BMS.ASIC1_CELL2,                   24,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL3",                   MSG_ASIC1_DATA_1_MAIN,    &Device.BMS.ASIC1_CELL3,                   40,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL4",                   MSG_ASIC1_DATA_1_MAIN,    &Device.BMS.ASIC1_CELL4,                   56,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL5",                   MSG_ASIC1_DATA_2_MAIN,    &Device.BMS.ASIC1_CELL5,                   8,      16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL6",                   MSG_ASIC1_DATA_2_MAIN,    &Device.BMS.ASIC1_CELL6,                   24,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL7",                   MSG_ASIC1_DATA_2_MAIN,    &Device.BMS.ASIC1_CELL7,                   40,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL8",                   MSG_ASIC1_DATA_2_MAIN,    &Device.BMS.ASIC1_CELL8,                   56,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL9",                   MSG_ASIC1_DATA_3_MAIN,    &Device.BMS.ASIC1_CELL9,                   8,      16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL10",                  MSG_ASIC1_DATA_3_MAIN,    &Device.BMS.ASIC1_CELL10,                  24,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL11",                  MSG_ASIC1_DATA_3_MAIN,    &Device.BMS.ASIC1_CELL11,                  40,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
  { "ASIC1_CELL12",                  MSG_ASIC1_DATA_3_MAIN,    &Device.BMS.ASIC1_CELL12,                  56,     16,    CANDBENG_FLOAT,     0.0009765625, 0,     "V",   NULL },
};

int CanDbGetMessagesCount(void)
{
  return sizeof(CanDbMessages)/sizeof(CanDbEngMessageItem_Type);
}

int CanDbGetSignalsCount(void)
{
 return sizeof(CanDbSignals)/sizeof(CanDbEngSignalItem_Type);
}

/******************* (C) COPYRIGHT Konvolucio Design *****END OF FILE******/
