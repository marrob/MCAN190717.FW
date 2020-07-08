/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "usbd_cdc_if.h"


#define CMDLINE_PARAMETER_COUNT_ERROR      "!PARAMTER COUNT ERROR, REQUIED %d, CURRENT IS %d."
#define CMDLINE_UNKNOWN_COMMAND_ERROR      "!UNKNOWN COMMAND ERROR, COMMAND WAS '%s'."
#define CMDLINE_UNKNOWN_PARAMETER_ERROR    "!UNKNOWN PARAMETER ERROR '%s'"
#define CMDLINE_PARAM_TOO_HIGH_ERROR       "!PARAMETER TOO HIGH ERROR, MAX IS %d."
#define CMDLINE_PARAM_TOO_LOW_ERROR        "!PARAMETER TOO LOW ERROR, MIN IS %d."
#define CMDLINE_COMPLETE                   "COMPLETE"

/* Cmd Line -------------------------------------------------------------------*/
char Temp [APP_TX_DATA_SIZE];
void USBD_CDC_DataRecivedCallback(char *rx)
{
  static uint8_t toogle;
  CmdLineMainMenu(rx, Temp);
  int respLen=strlen(Temp);

  memcpy(Temp + respLen, (uint8_t[]) { '\n', 0x00 }, 2 );

  CDC_Transmit_FS((uint8_t*)Temp, strlen(Temp));

  if(toogle)
  {
    LedOn(&hLed, HMI_LED_ORANGE);
    toogle = 0;
  }
  else
  {
    LedOff(&hLed, HMI_LED_ORANGE);
    toogle = 1;
  }
}



/**
  * @brief Command Execute
  */
void CmdLineMainMenu(char *request, char* response)
{

//  char cmd[APP_TX_DATA_SIZE/4];
//  sscanf(request, "%s", cmd);
//  DeviceDbgLog("%s", request);

   char strtmp[APP_TX_DATA_SIZE/4];
   char cmd[APP_TX_DATA_SIZE/4];
   char cmdtmp[APP_TX_DATA_SIZE/4];

   sscanf(request, "%s", cmd);
   //DeviceDbgLog("%s", request);

  if(!strcmp(cmd, "*OPC?")) 
  {
    strcpy(response, "*OPC");
  }
  else if(!strcmp(cmd, "*RDY?"))
  {
    strcpy(response, "*RDY");
  }
  else if(!strcmp(cmd, "*WHOIS?"))
  {
    strcpy(response, DEVICE_NAME);
  }
  else if(!strcmp(cmd, "*VER?"))
  {
    strcpy(response, DEVICE_FW);
  }
  else if(!strcmp(cmd, "*UID?"))
  {
    sprintf(response, "SN:%4X%4X%4X",HAL_GetUIDw0(),HAL_GetUIDw1(),HAL_GetUIDw2());
  }
  else if(!strcmp(cmd, "VCELLS?"))
  {
    sprintf(response,"%04f,%04f,%04f,%04f,%04f,%04f,%04f,%04f,%04f,%04f,%04f,%04f", 
            Device.BMS.ASIC0_CELL1,
            Device.BMS.ASIC0_CELL2,
            Device.BMS.ASIC0_CELL3,
            Device.BMS.ASIC0_CELL4,
            Device.BMS.ASIC0_CELL5,
            Device.BMS.ASIC0_CELL6,
            Device.BMS.ASIC0_CELL7,
            Device.BMS.ASIC0_CELL8,
            Device.BMS.ASIC0_CELL9,
            Device.BMS.ASIC0_CELL10,
            Device.BMS.ASIC0_CELL11,
            Device.BMS.ASIC0_CELL12);
  }
  else if(!strcmp(cmd, "BALANCING"))
  { /*BALANCING FFF*/
    int args_req = 2;
    uint8_t args_cnt;
    int code = 0;
    
    if((args_cnt = sscanf(request,"%s %X", cmdtmp, &code))!= args_req)
    {
      sprintf(response,CMDLINE_PARAMETER_COUNT_ERROR, args_req, args_cnt);
    }
    else
    {
      Device.BMS.AISC_REG_ID = 0x1A;
      Device.BMS.ASIC_REG_DATA = code;
      Device.BMS.ASIC_R_W = 1;
      CanDbEngSendMessage(&Device.CanDbEng, MSG_ASIC_REGISTER_MAIN);
      strcpy(response, "OK");
    }

  }
  else
  {
    sprintf(response, CMDLINE_UNKNOWN_COMMAND_ERROR, cmd);
    cmd[0] = 0;
    strtmp[0] = 0;
    cmdtmp[0] = 0;
  } 

}
/************************ (C) COPYRIGHT Konvol�ci� **********END OF FILE****/
