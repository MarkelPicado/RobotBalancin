/*******************************************************************************
 Explorer 16 Demo uart File
  Company:     Microchip Technology Inc.
  File Name:    uart_L.c
  Summary:    Explorer 16 Demo uart File.
  Description:
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
 * COPYA a la UART2 lo de la UART1
 * v 1.0
 *******************************************************************************/

// *****************************************************************************
// Section: Included Files
// *****************************************************************************

#include "uart.h"

UART_MOD_SFR_T  *gUartModule[] = { (UART_MOD_SFR_T*)&U1MODE,
                                   (UART_MOD_SFR_T*)&U2MODE,
                                 };

volatile UART_MESSAGE_BUFFER_T Message_Rx_Packet;
volatile UART_MESSAGE_BUFFER_T Message_Tx_Packet;

volatile unsigned short gUartRxBuff_Rd_Ptr, gUartRxBuff_Wr_Ptr, gUartTxBuff_Rd_Ptr, gUartTxBuff_Wr_Ptr;

volatile unsigned char Uart_Rx_Bytes[UART_BUFFER_SIZE];
volatile unsigned char Uart_Tx_Bytes[UART_BUFFER_SIZE];
volatile unsigned char gUart_Rcvd_Byte;

void ClearUartBuffer(void);

// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************

/*******************************************************************************
  Function:   void BTLE_ConfigureUART(unsigned long lfrequency)
  Summary:   Configures the UART module for 115200 baud.
  Description:
  Precondition:    None.
  Parameters:    unsigned long - frequency.
  Returns:    None.
  Remarks:
/******************************************************************************/

void BTLE_ConfigureUART(unsigned long lfrequency)
{
    // Clear all the pointer of read buffer and write buffer.
      gUartRxBuff_Rd_Ptr = 0;
      gUartRxBuff_Wr_Ptr = 0;
      gUartTxBuff_Rd_Ptr = 0;
      gUartTxBuff_Wr_Ptr = 0;
      Message_Rx_Packet.Msg_Buff_Ptr = 0;
      Message_Rx_Packet.Msg_To_Be_Processed = 0;
      Message_Tx_Packet.Msg_Buff_Ptr = 0;
      Message_Tx_Packet.Msg_To_Be_Processed = 0;

      PIC_U_Tx_BTLE_U_Rx_TRIS_Pin = 0; //Output

//      U2BRG = BRG_115200;                     //Baud rate 115,200 - actually 115,384 baud 0.16% error
        U2BRG = 86;                     //Baud rate 115,200 - actually 115,384 baud 0.16% error
      U2MODE = 0x8008;                        //Enable UART, flow control is enabled, BRGH = 1 for high speed baud mode
      U2STA = 0x0400;

//      U1BRG = BRG_115200;                     //Baud rate 115,200 - actually 115,384 baud 0.16% error
      U1BRG = 86;                     //Baud rate 115,200 - actually 115,384 baud 0.16% error
      U1MODE = 0x8008;                        //Enable UART, flow control is enabled, BRGH = 1 for high speed baud mode
      U1STA = 0x0400;


   // Interrupt Priority
   UART_RX_INT_Priority = 7; // Highest priority.

   while(!gUartModule[PIC_UART_MODULE]->USTABITS.TRMT);
}



/*******************************************************************************

  Function:
   void BTLE_UART_TransmitData(unsigned char Data)

  Summary:
   Transmits a character..

  Description:


  Precondition:
    None.

  Parameters:
    unsigned char -  Data to be transmitted.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/


void BTLE_UART_TransmitData(unsigned char Data)
{
  // U2TXREG = Data;
U2TXREG = Data;
  gUartModule[PIC_UART_MODULE]->UTXREG = Data;
   Nop();
   Nop();
  // while(!U2STAbits.TRMT);
  while(!gUartModule[PIC_UART_MODULE]->USTABITS.TRMT);
}


/*******************************************************************************

  Function:
   void BTLE_Uart_Newline_Char(void)

  Summary:
   Transmits a new line character.

  Description:


  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void BTLE_Uart_Newline_Char(void)
{
   //U2TXREG = '\n';
 U2TXREG = '+'; //LUIS
   gUartModule[PIC_UART_MODULE]->UTXREG = '\n';
   //while(!U2STAbits.TRMT);
   while(!gUartModule[PIC_UART_MODULE]->USTABITS.TRMT);
   Nop();
   Nop();
}

/*******************************************************************************

  Function:
   void BTLE_Uart_CarriageReturn_Char(void)

  Summary:
   Transmits a carriage return character.

  Description:


  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/
void BTLE_Uart_CarriageReturn_Char(void)
{
   Nop();
   Nop();
   //U2TXREG = '\r';
U2TXREG = '+';  //LUIS
   gUartModule[PIC_UART_MODULE]->UTXREG = '\r';
   Nop();
   Nop();
   //while(!U2STAbits.TRMT);
   while(!gUartModule[PIC_UART_MODULE]->USTABITS.TRMT);

}

/*******************************************************************************

  Function:
   void EnableUartReceiver(void)

  Summary:
   Enables the UART receiver.

  Description:


  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/
void EnableUartReceiver(void)
{

}

/*******************************************************************************

  Function:
   void FlushUART_ReceiveBuffer(void)

  Summary:
   Flush/Clears UART receive buffer.

  Description:


  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/
void FlushUART_ReceiveBuffer(void)
{
   volatile unsigned char lReceiveBuffer;

// Delay is provided because the once the receiver is enabled, BTLE will transmit "END" status.
   // To begin allow sufficient time for BTLE to transmit the data. Flush the receive buffer by reading the data.

   __delay_ms(((1000ul * (unsigned long)BAUDRATE * 8)/FCY));
    Nop();
    while(gUartModule[PIC_UART_MODULE]->USTABITS.URXDA)
    {
        lReceiveBuffer = gUartModule[PIC_UART_MODULE]->URXREG;
U2TXREG = lReceiveBuffer;
    }
    // Clear the Error Flags.
    gUartModule[PIC_UART_MODULE]->USTABITS.FERR = 0;
    gUartModule[PIC_UART_MODULE]->USTABITS.OERR = 0;
    gUartModule[PIC_UART_MODULE]->USTABITS.PERR = 0;
    UART_RX_INT_FLAG = 0;
    UART_ERROR_INT_FLAG = 0;

}


/*******************************************************************************

  Function:
   void ClearMessageBuffers(void)

  Summary:
   Clears Tx and Rx Message buffers.

  Description:


  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void ClearMessageBuffers(void)
{
   ClearMessageTxBuffer();
   ClearMessageRxBuffer();
}

/*******************************************************************************

  Function:
   void ClearMessageTxBuffer(void)

  Summary:
   Clears Tx Message buffers.

  Description:


  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/
void ClearMessageTxBuffer(void)
{
   unsigned short loop;
   for (loop = 0; loop < MESSAGE_BUFFER_SIZE; loop++)
   {
      Message_Rx_Packet.Message_Buffer[loop] = 0;
   }
}

/*******************************************************************************

  Function:
   void ClearMessageRxBuffer(void)

  Summary:
   Clears Rx Message buffers.

  Description:


  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/
void ClearMessageRxBuffer(void)
{
   unsigned short loop;
   for (loop = 0; loop < MESSAGE_BUFFER_SIZE; loop++)
   {
      Message_Rx_Packet.Message_Buffer[loop] = 0;
   }
}


/*******************************************************************************

  Function:
   void Uart_Rcv_Msg_Handler(void)

  Summary:
   UART Receive Message Handler.

  Description:


  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void Uart_Rcv_Msg_Handler(void)
{
    if (!Message_Rx_Packet.Msg_To_Be_Processed)
    {
        asm volatile ("disi #0x000A"); // For next 10 cycles there shouldnt be any update on the receive buffer.
        if (gUartRxBuff_Rd_Ptr != gUartRxBuff_Wr_Ptr)
        {
            Message_Rx_Packet.Message_Buffer[Message_Rx_Packet.Msg_Buff_Ptr] = Uart_Rx_Bytes[gUartRxBuff_Rd_Ptr];
            if (Message_Rx_Packet.Message_Buffer[Message_Rx_Packet.Msg_Buff_Ptr] == mEND_OF_PACKET_CHARACTER)
            {
                // Message has been received. Intimate the application to process the message.
                Message_Rx_Packet.Msg_To_Be_Processed = 1;
                Message_Rx_Packet.Msg_Buff_Ptr = 0;
            }
            else
            {
                Message_Rx_Packet.Msg_Buff_Ptr ++;
            }

            gUartRxBuff_Rd_Ptr ++;
            if (gUartRxBuff_Rd_Ptr > (UART_BUFFER_SIZE - 1))
            {
                gUartRxBuff_Rd_Ptr = 0;
            }
        }
    }
}


/*******************************************************************************

  Function:
   void Uart_Transmit_MessagePacket(void)

  Summary:
   UART Transmit Message Handler.

  Description:


  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void Uart_Transmit_MessagePacket(void)
{
    volatile unsigned char lCharTobeTx;
    if (Message_Tx_Packet.Msg_To_Be_Processed)
    {
       //Call the Tx function, which will transmit the data.
       // Disable the Receive interrupt

//LUIS
Nop();
Nop();
U2TXREG = '=';
Nop();
Nop();
while(U2STAbits.TRMT == 0);

     while(1)
        {
            lCharTobeTx = Message_Tx_Packet.Message_Buffer[gUartTxBuff_Wr_Ptr];
            BTLE_UART_TransmitData(lCharTobeTx);
            gUartTxBuff_Wr_Ptr++;
            if (lCharTobeTx == mEND_OF_PACKET_CHARACTER)
            {
                gUartTxBuff_Wr_Ptr = 0;
                break;
            }
        }
        Message_Tx_Packet.Msg_To_Be_Processed = 0;
    }
}

// *****************************************************************************
// *****************************************************************************
// ISR - Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

#if (PIC_UART_MODULE == UART_MOD_3)
void _ISR_NO_AUTO_PSV _U3RXInterrupt(void)
{
#elif (PIC_UART_MODULE == UART_MOD_2)
void _ISR_NO_AUTO_PSV _U2RXInterrupt(void)
{
#elif (PIC_UART_MODULE == UART_MOD_1)
void _ISR_NO_AUTO_PSV _U1RXInterrupt(void)
{
#endif
    UART_RX_INT_FLAG = 0;
    #ifdef DEBUG_BTLE
     DEBUG_PIN_LAT = !DEBUG_PIN_LAT;
    #endif

     gUart_Rcvd_Byte = gUartModule[PIC_UART_MODULE]->URXREG;

//LUIS
if (gUart_Rcvd_Byte == '\0')
{
   U2TXREG= '*';
}
else U2TXREG = gUart_Rcvd_Byte;

     if (gUart_Rcvd_Byte != '\0')
     {
    Uart_Rx_Bytes[gUartRxBuff_Wr_Ptr++] = gUart_Rcvd_Byte;
     }
     if (gUartRxBuff_Wr_Ptr > (UART_BUFFER_SIZE - 1))
     {
         gUartRxBuff_Wr_Ptr = 0;
     }
}
