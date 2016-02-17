
#ifndef TIMER_H
#define TIMER_H

/*******************************************************************************
 Explorer 16 Demo for Peripheral Node Main File
  Company:    Microchip Technology Inc.
  File Name:    timer.h
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

extern volatile unsigned short gCounter_50mS;

#define mTurn_On_SystemTimer()          (T1CONbits.TON = 1)
#define mStop_SystemTimer()             (T1CONbits.TON = 0)
#define mTurn_On_SystemTimerInterrupt() (_T1IF = 0, _T1IE = 1)
#define mStop_and_ResetSystemTimer()    (T1CONbits.TON = 0, gCounter_50mS = 0, _T1IF = 0, _T1IE = 0, TMR1 = 0)

void Init_Timer(void);

extern void Schedule_1X_Task(void);
extern void Schedule_2X_Task(void);
extern void Schedule_3X_Task(void);
extern void Schedule_4X_Task(void);
extern void Schedule_5X_Task(void);
extern void Schedule_10X_Task(void);


#endif
