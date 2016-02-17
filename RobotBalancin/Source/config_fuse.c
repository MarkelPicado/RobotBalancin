/*******************************************************************************
 Explorer 16 Demo config_fuse File

  Company:
    Microchip Technology Inc.

  File Name:
    config_fuse.c

  Summary:
    Explorer 16 Demo config_fuse File.

  Description:
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
 *******************************************************************************/



// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "config_L_24H.h"
//#include "config.h"

/*
#if defined (__24FJ128GA010_H)

    _CONFIG2(FNOSC_PRIPLL & FCKSM_CSECME & OSCIOFNC_OFF & POSCMOD_XT  & IESO_OFF )
    _CONFIG1( WDTPS_PS32768  & FWPSA_PR128 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx2 &
            COE_OFF & BKBUG_OFF & GWRP_OFF & GCP_OFF & JTAGEN_OFF)

#endif
*/

_FOSCSEL(FNOSC_PRIPLL);		//Primary oscillator (XT, HS, EC) w/ PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);	//Clock switching and clock monitor:Both disabled,OSC2 is clock O/P,XT oscillator
_FWDT(FWDTEN_OFF); //Watchdog Timer:Disabled
