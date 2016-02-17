// Oscilador
// Selecciona la frecuencia del Oscilador Principal

#include <p24HJ256GP610A.h>
//** Only one invocation of FOSCSEL, FOSC, FWDT should appear in a project,
//** at the top of a C source file (outside of any function).

//**   Oscillator Source Selection:
//**     FNOSC_FRC            Fast RC oscillator
//**     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
//**     FNOSC_PRI            Primary oscillator (XT, HS, EC)
//**     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
//**     FNOSC_SOSC           Secondary oscillator
//**     FNOSC_LPRC           Low power RC oscillator
//**     FNOSC_FRCDIV16       Fast RC oscillator w/ divide by 16
//**     FNOSC_LPRCDIVN        Low power Fast RC oscillator w/divide by N

//**   Clock switching and clock monitor:
//**     FCKSM_CSECME         Both enabled
//**     FCKSM_CSECMD         Only clock switching enabled
//**     FCKSM_CSDCMD         Both disabled
//**
//**   OSC2 Pin function:
//**     OSCIOFNC_ON          Digital I/O
//**     OSCIOFNC_OFF         OSC2 is clock O/P
//**
//**   Oscillator Selection:
//**     POSCMD_EC            External clock
//**     POSCMD_XT            XT oscillator
//**     POSCMD_HS            HS oscillator
//**     POSCMD_NONE          Primary disabled


_FOSCSEL(FNOSC_PRIPLL);		//Primary oscillator (XT, HS, EC) w/ PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);	//Clock switching and clock monitor:Both disabled,OSC2 is clock O/P,XT oscillator
_FWDT(FWDTEN_OFF); //Watchdog Timer:Disabled
//void Inic_Oscilador(void);


void Inic_Oscilador(void)
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
