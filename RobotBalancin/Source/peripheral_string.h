#ifndef PERIPHERAL_STRING_H
#define PERIPHERAL_STRING_H
/*******************************************************************************
 Explorer 16 Demo for Peripheral Node Main File
  Company:    Microchip Technology Inc.
  File Name:    peripheral_string.h
  Summary:    Explorer 16 Demo for Peripheral Node File
  Description:
    This is the file for the Explorer 16 Peripheral Node Demo that contains all the variables
    and functions used commonly across the application.
 *******************************************************************************/
// *****************************************************************************
// Section: Included Files
// *****************************************************************************

#include "config_L_24H.h"

/* Demo Variables and Functions Data Structure
  Summary:   Defines the data required by the demo in a data structure
  Description:    This data structure defines the data required by the Explorer 16 Demo
 Remarks:    None.
*/

typedef enum P_RESP_Strings_Enum_Tag
{
    ePERI_RESP_INVALID,
    ePERI_RESP_ERR,
    ePERI_RESP_AOK,
    ePERI_RESP_AOK1,
    ePERI_RESP_AOK2,
    ePERI_RESP_CMD,
    ePERI_RESP_ECHO_ON,
    ePERI_RESP_ECHO_OFF,
    ePERI_RESP_REBOOT,
    ePERI_RESP_CONNECTED,
    ePERI_RESP_CONNECTION_END,
    ePERI_RESP_BONDED,
    ePERI_RESP_MLDP_MODE,
    ePERI_RESP_NOT_FOUND_IN_THE_LIST,   
} P_RESP_Strings_Enum_T;

typedef enum
{
    NO,
    YES
} Boolean_T;

typedef struct Peripheral_Command_Strings_Tag
{
   P_CMD_Strings_Enum_T enumeration;
   const char *command;

}Peripheral_Command_Strings_T;


typedef struct Peri_Resp_Strings_Tag
{
    P_RESP_Strings_Enum_T resp_enum;
    const char *Response;
} Peri_Resp_Strings_T;

extern const Peripheral_Command_Strings_T BTLE_Cmd_Strings[];
extern unsigned short gusBTLE_Cmd_StructSize;
extern unsigned short gusBTLE_CmdResp_StructSize;
extern const Peri_Resp_Strings_T BTLE_CmdResp_Strings[];
extern const Peri_Resp_Strings_T BTLE_SW_LEDResp_Strings[];
extern unsigned short gusBTLE_NumOfCmdsToBeExecuted;
extern const P_CMD_Strings_Enum_T gCommands_ToBeExecuted[];

#endif
