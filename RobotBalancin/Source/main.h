#ifndef MAIN_H
#define MAIN_H
/*******************************************************************************
 Explorer 16 Demo for Peripheral Node Main File
  Company:    Microchip Technology Inc.
  File Name:    main.h
  Summary:    Explorer 16 Demo for Peripheral Node File
  Description:
    This is the file for the Explorer 16 Peripheral Node Demo that contains all the variables
    and functions used commonly across the application.
 *******************************************************************************/
// *****************************************************************************
// Section: Included Files
// *****************************************************************************

#include "uart.h"
#include "peripheral.h"

/* Demo Variables and Functions Data Structure
  Summary:    Defines the data required by the demo in a data structure
  Description:    This data structure defines the data required by the Explorer 16 Demo
 Remarks:    None.
*/

extern void Port_Configuration(void);
//extern void Process_Switches(void);
extern void Process_LEDs(P_BTLE_PERI_SW_LED_T lBTLE_Resp);
extern unsigned char GetBTLE_Connected_Status(void);


//Control remoto

extern void Process_Control(P_BTLE_PERI_CONTROL_T lBTLE_Resp);
extern int velExtra_RI;
extern int velExtra_RD;

#endif
