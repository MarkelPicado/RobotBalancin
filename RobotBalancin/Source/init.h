#ifndef INIT_H
#define INIT_H

/*******************************************************************************
 Explorer 16 Demo for Peripheral Node Init File
  Company:    Microchip Technology Inc.
  File Name:    init.h
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
  Summary:    Defines the data required by the demo in a data structure
  Description:    This data structure defines the data required by the Explorer 16 Demo
 Remarks:    None.
*/

extern HW_SWITCHES_T gHw_Switches;

extern void Init_SystemClock(void);
extern void Init_XPL16_Board_Switches(void);
extern void Init_XPL16_Board_LEDs(void);

#endif
