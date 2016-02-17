/*******************************************************************************
 Explorer 16 Demo main File
  Company:    Microchip Technology Inc.
  File Name:    init.c
  Summary:    Explorer 16 Demo init.c file.
  Description:
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
 *******************************************************************************/
// *****************************************************************************
// Section: Included Files
// *****************************************************************************

#include "init.h"

HW_SWITCHES_T gHw_Switches;

// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************

/*******************************************************************************
  Function:   void Init_SystemClock(void)
  Summary: This function intiailizes the system clock to 16MIPS..
  Description:
  Precondition:    None.
  Parameters:    None.
  Returns:    None.
  Remarks:
/******************************************************************************/

void Init_SystemClock(void)
/*{
  // Wait for PLL get locked.
   CLKDIVbits.RCDIV = 0; //Devide by 1.
   Nop();
   Nop();
   while(!OSCCONbits.LOCK);
   Nop();
   Nop();
}*/
//void Inic_Oscilador(void)
{
//  Configure Oscillator to operate the device at 40Mhz
//  Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
//  Fosc= 8M*40/(2*2)=80Mhz for 8M input clock
// M=40 --> 80 Mhz	Instrucción 25ns
// M=20 --> 40 Mhz	Instrucción 50ns
// M=10 --> 20 Mhz	Instrucción 100ns (
	PLLFBD= 40-2;				/* M=40 */
	CLKDIVbits.PLLPOST=0;		/* N1=2 */
	CLKDIVbits.PLLPRE=0;		/* N2=2 */
//	OSCTUN=0;					/* Tune FRC oscillator, if FRC is used */

//  Disable Watch Dog Timer
	RCONbits.SWDTEN=0;

//  Clock switch to incorporate PLL
	__builtin_write_OSCCONH(0x03);		// Initiate Clock Switch to Primary
											// Oscillator with PLL (NOSC=0b011)
	__builtin_write_OSCCONL(0x01);		// Start clock switching
// funciones pre-compiladas: MPLAB C30 -DS51284G- apendice B
	while (OSCCONbits.COSC != 0b011);	// Wait for Clock switch to occur

//  Wait for PLL to lock
	while(OSCCONbits.LOCK!=1) {};
}


/*******************************************************************************
  Function:   void Init_XPL16_Board_Switches(void)
  Summary: This function intiailizes Switches of Explorer 16 board.
  Description:
  Precondition:    None.
  Parameters:    None.
  Returns:    None.
  Remarks:
/******************************************************************************/

void Init_XPL16_Board_Switches(void)
{
    SWITCH_S1_TRIS = 1; // Read S2 Switch.
    SWITCH_S2_TRIS = 1;

    gHw_Switches.SwitchStatus = 0xFF; // All the switches are pulled up externally. // Initial state.
}


/*******************************************************************************
  Function:   void Init_XPL16_Board_LEDs(void)
  Summary:  This function intiailizes LEDs of Explorer 16 board.
  Description:
  Precondition:    None.
  Parameters:    None.
  Returns:    None.
  Remarks:
/******************************************************************************/

void Init_XPL16_Board_LEDs(void)
{
    XPL16_D10_LED_LAT = XPL16_D10_LED_TurnOFF;
//    XPL16_D9_LED_LAT = XPL16_D10_LED_TurnOFF;
//    XPL16_D8_LED_LAT = XPL16_D10_LED_TurnOFF;
//    XPL16_D7_LED_LAT = XPL16_D10_LED_TurnOFF;
    XPL16_D9_LED_LAT = XPL16_D9_LED_TurnOFF;
    XPL16_D8_LED_LAT = XPL16_D8_LED_TurnOFF;
    XPL16_D7_LED_LAT = XPL16_D7_LED_TurnOFF;
    XPL16_D5_LED_LAT = XPL16_D5_LED_TurnOFF;
    XPL16_D4_LED_LAT = XPL16_D4_LED_TurnOFF;
    XPL16_D3_LED_LAT = XPL16_D3_LED_TurnOFF;

    XPL16_D10_LED_TRIS = 0;
    XPL16_D7_LED_TRIS = 0;
    XPL16_D8_LED_TRIS = 0;
    XPL16_D9_LED_TRIS = 0;
    XPL16_D5_LED_TRIS = 0;
    XPL16_D4_LED_TRIS = 0;
    XPL16_D3_LED_TRIS = 0;
}