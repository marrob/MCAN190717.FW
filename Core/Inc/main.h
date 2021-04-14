/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LiveLed.h"
#include "led.h"
#include "candb.h"
#include "candbeng.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef enum _DebugStateTypeDef
{
  SDBG_IDLE,                    //0x00
  SDBG_USBD_OUT_MSG_PREPARE_NEXT,
  SDBG_USBD_OUT_ATTR_PREPARE_NEXT,
  SDBG_USBD_ATTR_IN_FLUSH,
  SDG_USBD_ATTR_IN_STALL,
}DebugStateTypeDef;

typedef enum _CtrlStatesTypeDef
{
  SDEV_NONE,
  SDEV_START,     //Ide soha nem kerülhet...
  SDEV_STOP,
  SDEV_RESET,
  SDEV_FAIL,
  SDEV_IDLE,      //Itt várakozik, kódolvasó élesítve...
}CtrlStateTypeDef;

typedef struct _State
{
  CtrlStateTypeDef Next;
  CtrlStateTypeDef Curr;
  CtrlStateTypeDef Pre;
}StateTypeDef;

#define CANNET_VCELLS_COUNT   144

typedef struct _DeviceTypeDef
{
  uint8_t Address;
  DebugStateTypeDef DebugState;
  CanDbEng_Type CanDbEng;
  uint32_t TestMsgCounter;
  struct
  {
    char TxLine[80];
    uint8_t TxRequest;
    uint8_t TxCounter;
    size_t  TxSize;
    char RxLine[80];
    uint8_t RxRequest;
    uint8_t RxCounter;
    size_t RxSize;
  }UART;

  struct
  {
    uint16_t SW_VERSION_SFTY;
    uint8_t HEVC_WakeUpSleepCommand;
    uint8_t ETS_SleepMode;
    uint8_t LBCPRUNKey;
    uint8_t OperatingTypeRequest;
    uint8_t IgnitionSupplyConfirmation_HV;
    uint8_t PowerRelayState;
    uint8_t GADE_HV;
    uint8_t SHDN_MCU_ASIC;
    uint8_t IMMEDITATE_APPLY;
    uint8_t SHDN_MCU_ASIC_SFTY;
    uint8_t IMMEDITATE_APPLY_SFTY;
    double ASIC_VCELL_DATA;
    double ASIC0_CELL1;
    double ASIC0_CELL2;
    double ASIC0_CELL3;
    double ASIC0_CELL4;
    double ASIC0_CELL5;
    double ASIC0_CELL6;
    double ASIC0_CELL7;
    double ASIC0_CELL8;
    double ASIC0_CELL9;
    double ASIC0_CELL10;
    double ASIC0_CELL11;
    double ASIC0_CELL12;

    uint8_t AISC_REG_ID;
    uint16_t ASIC_REG_DATA;
    uint8_t ASIC_R_W;

    double ASIC1_CELL1;
    double ASIC1_CELL2;
    double ASIC1_CELL3;
    double ASIC1_CELL4;
    double ASIC1_CELL5;
    double ASIC1_CELL6;
    double ASIC1_CELL7;
    double ASIC1_CELL8;
    double ASIC1_CELL9;
    double ASIC1_CELL10;
    double ASIC1_CELL11;
    double ASIC1_CELL12;
  }BMS;
}DeviceTypeDef;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/* Debug ---------------------------------------------------------------------*/
  #define DEVICE_DEBUG_LEVEL    3


/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */


#if (DEVICE_DEBUG_LEVEL > 0)
#define  DeviceUsrLog(...)  {printf(__VA_ARGS__);\
                             printf("\r\n");}
#else
#define DeviceUsrLog(...)
#endif

#if (DEVICE_DEBUG_LEVEL > 1)

#define  DeviceErrLog(...)  {printf("ERROR.DEVICE:") ;\
                             printf(__VA_ARGS__);\
                             printf("\r\n");}
#else
#define DeviceErrLog(...)
#endif

#if (DEVICE_DEBUG_LEVEL > 2)
#define  DeviceDbgLog(...)  {printf("DEBUG.DEVICE:") ;\
                             printf(__VA_ARGS__);\
                             printf("\r\n");}
#else
#define DeviceDbgLog(...)
#endif
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern DeviceTypeDef Device;
extern LedHandle_Type hLed;
void CmdLineMainMenu(char *request, char* response);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TERM_Pin GPIO_PIN_12
#define TERM_GPIO_Port GPIOB
#define LIVE_LED_Pin GPIO_PIN_15
#define LIVE_LED_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_12
#define LED_R_GPIO_Port GPIOC
#define LED_Y_Pin GPIO_PIN_4
#define LED_Y_GPIO_Port GPIOB
#define LED_G_Pin GPIO_PIN_5
#define LED_G_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
/* Generic  -------------------------------------------------------------------*/
  #define DEVICE_NAME             "MCAN190717"    /*!< Eszk�z neve pl.:MDIO130204*/
  #define DEVICE_NAME_SIZE        sizeof(DEVICE_NAME)
  #define DEVICE_FW               "0"   /*!< Eszk�z Firmware verzi�sz�ma pl.:"1.0.0.0"*/
  #define DEVICE_FW_SIZE          sizeof(DEVICE_FW)
  #define DEVICE_PCB              "00"            /*!< Eszk�z PCB verzi�sz�ma pl.:"A0"*/
  #define DEVICE_PCB_SIZE         sizeof(DEVICE_PCB)
  #define DEVICE_MNF              "KONVOLUCIO"
  #define DEVICE_MNF_SIZE         sizeof(DEVICE_MNF)

  #define HMI_LED_ORANGE  0
  #define HMI_LED_GREEN   1
  #define HMI_LED_RED     2

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
