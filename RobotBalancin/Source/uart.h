#ifndef _UART_H
#define _UART_H

/*******************************************************************************
 Explorer 16 Demo for UART File

  Company:
    Microchip Technology Inc.

  File Name:
    uart.h

  Summary:
    Explorer 16 Demo for UART File

  Description:
    This is the file for the Explorer 16 Peripheral Node Demo that contains all the variables
    and functions used commonly across the application.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************


//#include "config.h"
#include "config_L_24H.h"


/* Demo Variables and Functions Data Structure

  Summary:
    Defines the data required by the demo in a data structure

  Description:
    This data structure defines the data required by the Explorer 16 Demo

 Remarks:
    None.
*/

#define UART_BUFFER_SIZE   (1024) //Atleast handle 4 message of 256 bytes each.
#define MESSAGE_BUFFER_SIZE (UART_BUFFER_SIZE/4)

typedef struct UART_MOD_SFR_Tag
{
   union
   {
      U1MODEBITS         UMODEBITS;
      unsigned short     UMODE;
   };
   union
   {
      U1STABITS          USTABITS;
      unsigned short     USTA;
   };
   unsigned short     UTXREG;
   unsigned short     URXREG;
   unsigned short     UBRG;
}  UART_MOD_SFR_T;

typedef struct Uart_Message_Buffer_Tag
{
    unsigned char Msg_To_Be_Processed;
    unsigned char Msg_Buff_Ptr;
    unsigned char Message_Buffer[MESSAGE_BUFFER_SIZE];
}   UART_MESSAGE_BUFFER_T;



extern UART_MOD_SFR_T  *gUartModule[];


extern volatile UART_MESSAGE_BUFFER_T Message_Rx_Packet;
extern volatile UART_MESSAGE_BUFFER_T Message_Tx_Packet;


#define mReset_RxMessageTobeProcessedFlag()        (Message_Rx_Packet.Msg_To_Be_Processed = 0)

extern void BTLE_ConfigureUART(unsigned long);
extern void BTLE_UART_TransmitData(unsigned char Data);
extern void BTLE_Uart_Newline_Char(void);
void BTLE_Uart_CarriageReturn_Char(void);
extern unsigned char BTLE_Read_Acknowledgement(unsigned char *Ptr);
extern void EnableUartReceiver(void);
extern void FlushUART_ReceiveBuffer(void);
extern void ClearMessageBuffers(void);
extern void ClearMessageTxBuffer(void);
extern void ClearMessageRxBuffer(void);
extern void Uart_Rcv_Msg_Handler(void);
extern void Uart_Transmit_MessagePacket(void);


#endif
