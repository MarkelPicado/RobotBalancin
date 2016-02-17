#ifndef PERIPHERAL_H
#define PERIPHERAL_H
/*******************************************************************************
 Explorer 16 Demo for Peripheral Node Main File
  Company:    Microchip Technology Inc.
  File Name:    peripheral.h
  Summary:    Explorer 16 Demo for Peripheral Node File
  Description:
    This is the file for the Explorer 16 Peripheral Node Demo that contains all the variables
    and functions used commonly across the application.
 *******************************************************************************/
// *****************************************************************************
// Section: Included Files
// *****************************************************************************

#include "uart.h"
#include "lcd1.h"
#include "init.h"
#include "timer.h"
#include "peripheral_string.h"

/* Demo Variables and Functions Data Structure
  Summary:    Defines the data required by the demo in a data structure
  Description:    This data structure defines the data required by the Explorer 16 Demo
 Remarks:    None.
*/

typedef enum BTLE_PERIPHERAL_STATES_Tag
{
    eBTLE_POR_RESET_STATE,
    eBTLE_QUERY_FOR_PAIRING,

}   BTLE_PERIPHERAL_STATES_T;

extern unsigned char gCmdsTobeExecuted_index;
extern unsigned char gBlueToothConnected;

extern void Peripheral_CMD_StateMachine(void);
extern void BTLE_As_PeripheralInit(void);
extern unsigned short GetTheIndexFromBTLECmdArray(P_CMD_Strings_Enum_T leStringEnum);
extern P_RESP_Strings_Enum_T GetBTLE_CmdResponseIndexFrom_BTLE_Resp_Strings(const char *RespString);
extern P_CMD_Strings_Enum_T GetTheIndexFromBTLECmdsTobeExecutedArray(unsigned char lIndex);
extern unsigned char AssignTheIndexUsingtheValueFromCmdTobeExecuted(const P_CMD_Strings_Enum_T lCmdString);

#endif
