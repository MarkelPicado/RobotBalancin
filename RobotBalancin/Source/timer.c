/*******************************************************************************
 Explorer 16 Demo main File
  Company:    Microchip Technology Inc.
  File Name:    timer.c
  Summary:    Explorer 16 Demo adc File.
  Description:
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
 *******************************************************************************/

// *****************************************************************************
// Section: Included Files
// *****************************************************************************

#include "timer.h"

volatile unsigned short gCounter_50mS;

void Init_Timer(void)
{
    T1CONbits.TON = 0;
    TMR1 = 0;
    T1CONbits.TCKPS = 0b11; // divide by 256.
    T1CONbits.TCS = 0;
    PR1 = TimeOut_XmS;
    _T1IF = 0;
    _T1IP = mTimer_INTR_Priority;
    _T1IE = 1;
    gCounter_50mS = 0;
}


void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    _T1IF = 0;
    gCounter_50mS ++;
 
    if (!(gCounter_50mS % 2))
    {
        //Schedule_1X_Task(); // 100mS
    }
    if (!(gCounter_50mS % 4))
    {
        Schedule_2X_Task(); // 200mS
    }
    if (!(gCounter_50mS % 6))
    {
        Schedule_3X_Task(); // 300mS
    }
    if (!(gCounter_50mS % 8))
    {
        Schedule_4X_Task(); // 400mS
    }
    if (!(gCounter_50mS % 10))
    {
        Schedule_5X_Task(); // 500mS
    }
    if (!(gCounter_50mS % 20))
    {
        Schedule_10X_Task(); // 1Sec
        gCounter_50mS = 0;
    }
}


