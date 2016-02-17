
/*******************************************************************************
 Explorer 16 Demo peripheral File
  Company:    Microchip Technology Inc.
  File Name:    config.c
  Summary:    Explorer 16 Demo config.c File.
  Description:
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
 *******************************************************************************/
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
#include "peripheral_string.h"

const P_CMD_Strings_Enum_T gCommands_ToBeExecuted[]= {
    ePERI_INVALID_CMD,
    ePERI_COMMAND_MODE,
    ePERI_FACTORY_RESET,
    ePERI_GET_VERSION_COMMAND,
    ePERI_GR_COMMAND,
    ePERI_GN_COMMAND,
    ePERI_SR_COMMAND,
    ePERI_CH_DNAME,
    ePERI_REBOOT_COMMAND,
    ePERI_PAIR_REQUEST,
};

/*******************************************************************************************
* Configuracion control remoto.
********************************************************************************************/

const BTLE_Peri_Control_T  BTLE_CONTROL_Strings[] = {
    
    {ePERI_CONTROL_NOT_IN_THE_LIST, " "},
    {ePERI_GO_FORDWARD, "S3GF\r\n"},
    {ePERI_GO_BACK, "S6GB\r\n"},
    {ePERI_TURN_RIGHT, "S4TR\r\n"},
    {ePERI_TURN_LEFT, "S5TL\r\n"},
    {ePERI_STOP, "STOP\r\n"},
};

unsigned short gusBTLE_Control_StructSize = sizeof(BTLE_CONTROL_Strings)/sizeof(BTLE_Peri_Control_T);
int velExtra_RD;
int velExtra_RI;

/*******************************************************************************************
* GA010 configuration of Switches and LEDs.
********************************************************************************************/

const BTLE_Peri_Sw_LED_T  BTLE_SW_LED_Strings[] = {
    
    {ePERI_LED_SW_NOT_IN_THE_LIST, " "},
    {ePERI_LED_D1_ON, "D1ON\r\n"},
    {ePERI_LED_D1_OFF, "D1OFF\r\n"},
    {ePERI_LED_D2_ON, "D2ON\r\n"},
    {ePERI_LED_D2_OFF, "D2OFF\r\n"},
    {ePERI_SW_S1_PRESSED, "S1ON\r\n"},
    {ePERI_SW_S1_RELEASED, "S1OFF\r\n"},
    {ePERI_SW_S2_PRESSED, "S2ON\r\n"},
    {ePERI_SW_S2_RELEASED, "S2OFF\r\n"},
};

unsigned short gusBTLE_SW_LED_StructSize = sizeof(BTLE_SW_LED_Strings)/sizeof(BTLE_Peri_Sw_LED_T);
unsigned short gusBTLE_NumOfCmdsToBeExecuted = sizeof(gCommands_ToBeExecuted)/sizeof (P_CMD_Strings_Enum_T);


/*******************************************************************************
  Function:   P_RESP_Strings_Enum_T GetBTLE_CmdResponseIndexFrom_BTLE_Resp_Strings(const char *RespString)
  Summary:
  Description:   returns the index of the Response Array string for the given input string.
  Precondition:    None.
  Parameters:    const char * - Response string.
  Returns:
    Returns the enum of the Response string from Response String Array.
 If the input string is not found in the Response string,
 then returns ePERI_LED_SW_NOT_IN_THE_LIST
  Remarks:
/******************************************************************************/

P_BTLE_PERI_CONTROL_T GetBTLE_ResponseIndexFrom_BTLE_CONTROL_Strings(const char *RespString)
{
    P_BTLE_PERI_CONTROL_T index;

    for (index = ePERI_CONTROL_NOT_IN_THE_LIST; index < gusBTLE_Control_StructSize; index++)
    {
        if (!strcmp(RespString, BTLE_CONTROL_Strings[index].String))
            return index;
    }
    return ePERI_CONTROL_NOT_IN_THE_LIST;
}



/*******************************************************************************
  Function:   const char *GetBTLE_RespStringFrom_BTLE_SW_LEDResp_Strings(P_BTLE_PERI_SW_LED_T lenum)
  Summary:
  Description:   returns the Response Array string for the given index.
  Precondition:    None.
  Parameters:    P_BTLE_PERI_SW_LED_T - Index
  Returns:    const char * - Returns the string for the given index
  Remarks:
/******************************************************************************/

const char *GetBTLE_RespStringFrom_BTLE_SW_LEDResp_Strings(P_BTLE_PERI_SW_LED_T lenum)
{
    P_BTLE_PERI_SW_LED_T index;

    for (index = ePERI_LED_SW_NOT_IN_THE_LIST; index < gusBTLE_SW_LED_StructSize; index++)
    {
        if (lenum == BTLE_SW_LED_Strings[index].ePeri_Sw_LED_enumeration)
            return BTLE_SW_LED_Strings[index].String;

    }
    return 0;
}




