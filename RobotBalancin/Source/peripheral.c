/*******************************************************************************
 Explorer 16 Demo Peripheral File
  Company:    Microchip Technology Inc.
  File Name:    peripheral.c
  Summary:    Explorer 16 Demo peripheral File.
  Description:
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
 *******************************************************************************/
// *****************************************************************************
// Section: Included Files
// *****************************************************************************

#include "peripheral.h"

//P_CMD_Strings_Enum_T gePeri_CMD_State;
unsigned char gCmdsTobeExecuted_index;
unsigned char gBlueToothConnected;

// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
static unsigned char gBTLE_Version[50];

/*******************************************************************************
  Function:   void BTLE_As_PeripheralInit(void)
  Summary:    .
  Description: Initialize the module as Peripheral Node.
  Precondition:    None.
  Parameters:    None.
  Returns:    None.
  Remarks:
/******************************************************************************/

void BTLE_As_PeripheralInit(void)
{
   BTLE_To_PIC_CMD_DATA_PIO4_LAT = 0;
   BTLE_To_PIC_SWAKE_PIO3_LAT = 0;

   EnableUartReceiver();
   
   BTLE_To_PIC_CMD_DATA_PIO4_TRIS = 0;
   BTLE_To_PIC_SWAKE_PIO3_TRIS = 0; // In disable Mode
   BTLE_PAIRED_PIO5_TRIS = 1;
   BTLE_ACTIVE_PIO7_TRIS = 1;
   gBlueToothConnected = 0;

   FlushUART_ReceiveBuffer();
   UART_RX_INT_FLAG = 0;
   UART_RX_INT_ENABLE = 1;
   gCmdsTobeExecuted_index = AssignTheIndexUsingtheValueFromCmdTobeExecuted(ePERI_COMMAND_MODE);
   __delay_ms(100);
   BTLE_To_PIC_SWAKE_PIO3_LAT = 1; // BTLE is set in "ACTIVE" Mode.
}


/*******************************************************************************
  Function:   void Peripheral_CMD_StateMachine (void)
  Summary:  
  Description:   Peripheral Node state machine.
  Precondition:    None.
  Parameters:    None.
  Returns:    None.
  Remarks:
/******************************************************************************/

void Peripheral_CMD_StateMachine (void)
{
   unsigned short lCmdVal;
   unsigned char lValue = 0;

   P_RESP_Strings_Enum_T lBTLE_Resp =
     GetBTLE_CmdResponseIndexFrom_BTLE_Resp_Strings((const char *)Message_Rx_Packet.Message_Buffer);
   // Decode the response
   P_CMD_Strings_Enum_T lLastExecutedCmd =
     GetTheIndexFromBTLECmdsTobeExecutedArray(gCommands_ToBeExecuted[gCmdsTobeExecuted_index]);
   Nop();
   Nop();

   if (lBTLE_Resp != ePERI_RESP_NOT_FOUND_IN_THE_LIST)
   {
       if (lLastExecutedCmd != ePERI_INVALID_CMD)
       {
           if (ePERI_COMMAND_MODE == lLastExecutedCmd)
           {
               // Check whether the BTLE response was proper for ACTIVE mode.
               // Add as many conditions here.
               __delay_ms(2); // Allow the RN to set the port pin high.
               if (ePERI_RESP_CMD == lBTLE_Resp && BTLE_ACTIVE_PIO7_PORT)
               {
                   lValue = 1; // No error
               }
               else
               {
                   lValue = 2; // Port is not set high.
               }
           }
           else if (ePERI_ENABLE_ECHO == lLastExecutedCmd)
           {
               if ((ePERI_RESP_ECHO_ON == lBTLE_Resp) || (ePERI_RESP_ECHO_OFF == lBTLE_Resp))
               {
                   lValue = 1; // No error
               }
               else
               {
                   lValue = 3; // Error in enabling the echo feature.
               }
           }
           else if (ePERI_FACTORY_RESET == lLastExecutedCmd)
           {
               if ((ePERI_RESP_AOK == lBTLE_Resp) || (ePERI_RESP_AOK1 == lBTLE_Resp) ||
                   (ePERI_RESP_AOK2 == lBTLE_Resp))
               {
                   lValue = 1; // No error
               }
               else
               {
                   lValue = 4; // Error during Factory Reset.
               }
           }
           else if (ePERI_SR_COMMAND == lLastExecutedCmd)
           {
               if ((ePERI_RESP_AOK == lBTLE_Resp) || (ePERI_RESP_AOK1 == lBTLE_Resp) ||
                   (ePERI_RESP_AOK2 == lBTLE_Resp))
               {
                   lValue = 1; // No error
                   LCD_CursorToLine2();               //Cursor to start of line 2
                   LCD_WriteString((char *)"Auto Advertise..");
                   XPL16_D5_LED_LAT = XPL16_D5_LED_TurnON;
               }
               else
               {
                   lValue = 0; // Some error condition.
               }
           }
           else if (ePERI_CH_DNAME == lLastExecutedCmd)
           {
               if ((ePERI_RESP_AOK == lBTLE_Resp) || (ePERI_RESP_AOK1 == lBTLE_Resp) ||
                   (ePERI_RESP_AOK2 == lBTLE_Resp))
               {
                   lValue = 1; // No error
               }
               else
               {
                   lValue = 0; // Some error condition.
               }
           }
           else if (ePERI_REBOOT_COMMAND == lLastExecutedCmd)
           {
               if ((ePERI_RESP_REBOOT == lBTLE_Resp))
               {
                   lValue = 2; // Reboot command is not completed. Wait for "CMD" .
                               // So dont send the next command.
               }
               else if ((ePERI_RESP_AOK == lBTLE_Resp) || (ePERI_RESP_AOK1 == lBTLE_Resp) ||
                        (ePERI_RESP_AOK2 == lBTLE_Resp) || (ePERI_RESP_CMD == lBTLE_Resp))
               {
                   lValue = 1; // No error.
               }
               else
               {
                   lValue = 0; // Error
               }

           }
           else if (ePERI_AUTO_ADVERTISE == lLastExecutedCmd)
           {
               if ((ePERI_RESP_AOK == lBTLE_Resp) || (ePERI_RESP_AOK1 == lBTLE_Resp) ||
                   (ePERI_RESP_AOK2 == lBTLE_Resp))
               {
                   lValue = 1; // No Error.
               }
               else
               {
                   lValue = 0; // Error
               }
           }
           else if (ePERI_PAIR_REQUEST == lLastExecutedCmd)
           {
               __delay_ms(2); // Allow the RN to set the port pin high.
               if ((ePERI_RESP_CONNECTED == lBTLE_Resp) && (BTLE_PAIRED_PIO5_PORT))
               {
                   lValue = 2; // No Error.
                   gBlueToothConnected = 1;
                   BTLE_To_PIC_CMD_DATA_PIO4_LAT = 1;
                   mTurn_On_SystemTimerInterrupt();
                   mTurn_On_SystemTimer();
                   LCD_CursorToLine2();         //Cursor to start of line 2
                   LCD_WriteString((char *)"Connected..     ");
                   XPL16_D4_LED_LAT = XPL16_D4_LED_TurnON;
                   XPL16_D5_LED_LAT = XPL16_D5_LED_TurnON;
               }
               else if ((ePERI_RESP_CONNECTION_END == lBTLE_Resp) && (!BTLE_PAIRED_PIO5_PORT))
               {
                   lValue = 2; // No Error.
                   gBlueToothConnected = 0;
                   BTLE_To_PIC_CMD_DATA_PIO4_LAT = 0;
                   Init_XPL16_Board_LEDs();
                   Init_XPL16_Board_Switches();
                   mStop_and_ResetSystemTimer();
                   LCD_CursorToLine2();      //Cursor to start of line 2
                   LCD_WriteString((char *)"Disconnected..  ");
                   XPL16_D5_LED_LAT = XPL16_D5_LED_TurnOFF;
                   XPL16_D4_LED_LAT = XPL16_D4_LED_TurnOFF;
               }
               else
               {
                   lValue = 0; // Error
               }
           }
           else if (ePERI_BONDING_REQUEST == lLastExecutedCmd)
           {
               if ((ePERI_RESP_AOK == lBTLE_Resp))
               {
                   lValue = 2; // No Error.
               }
               else if (ePERI_RESP_BONDED == lBTLE_Resp)
               {
                   lValue = 1;
               }
               else
               {
                   lValue = 0; // Probably its not bonded. Need to restart the whole process.??
               }
           }
           else if (ePERI_STOP_ADVERTISE_COMMAND == lLastExecutedCmd)
           {
               if ((ePERI_RESP_AOK == lBTLE_Resp) || (ePERI_RESP_AOK1 == lBTLE_Resp) ||
                   (ePERI_RESP_AOK2 == lBTLE_Resp))
               {
                   lValue = 1; // No Error.
                }
               else
               {
                   lValue = 0; // Probably its not bonded. Need to restart the whole process.??
               }
           }
       }
   }
   else
   {
       // Print the debug message saying The response is not in the list.
       if (ePERI_GET_VERSION_COMMAND == lLastExecutedCmd)
       {
           memcpy(gBTLE_Version,
                  (const char*)Message_Rx_Packet.Message_Buffer,
                  strlen((const char*)Message_Rx_Packet.Message_Buffer));
           lValue = 1;
       }
       else if (ePERI_GN_COMMAND == lLastExecutedCmd)
       {
           lValue = 1; // No error
       }
       else if (ePERI_GR_COMMAND == lLastExecutedCmd)
       {
           lValue = 1; // No error
       }
   }
   //Check whether the next command should be ignored or not.
   if (lValue == 1)
   {
       if (gCmdsTobeExecuted_index < (gusBTLE_NumOfCmdsToBeExecuted - 1))
       {
           gCmdsTobeExecuted_index++;
           lCmdVal = GetTheIndexFromBTLECmdArray(gCommands_ToBeExecuted[gCmdsTobeExecuted_index]);
           strcpy((char *)Message_Tx_Packet.Message_Buffer, BTLE_Cmd_Strings[lCmdVal].command);
           Message_Tx_Packet.Msg_To_Be_Processed = 1;
       }
   }
}


/*******************************************************************************
  Function:   unsigned short GetTheIndexFromBTLECmdArray(P_CMD_Strings_Enum_T leStringEnum)
  Summary:
  Description:   returns the index of the CmdArray.
  Precondition:    None.
  Parameters:    P_CMD_Strings_Enum_T - Input string.
  Returns:    unsigned short - returns the index of CMD Array for the given input string.
  Remarks:
/******************************************************************************/

unsigned short GetTheIndexFromBTLECmdArray(P_CMD_Strings_Enum_T leStringEnum)
{
    unsigned short index;
    for (index = 0; index < gusBTLE_Cmd_StructSize; index++)
    {
        if (leStringEnum == BTLE_Cmd_Strings[index].enumeration)
           return index;
    }
    return ePERI_INVALID_CMD;
}

/*******************************************************************************
  Function:   P_CMD_Strings_Enum_T GetTheIndexFromBTLECmdsTobeExecutedArray(unsigned char lIndex)
  Summary:
  Description:   returns the command string index to be executed of the CmdArray.
  Precondition:    None.
  Parameters:    unsigned char lIndex- Index of the command to be executed.
  Returns:    returns the enum of the command string to be executed.
  Remarks:
/******************************************************************************/

P_CMD_Strings_Enum_T GetTheIndexFromBTLECmdsTobeExecutedArray(unsigned char lIndex)
{
    unsigned short index;
    for (index = 0; index < gusBTLE_NumOfCmdsToBeExecuted; index++)
    {
        if (lIndex == gCommands_ToBeExecuted[index])
           return gCommands_ToBeExecuted[index];
    }
    return ePERI_INVALID_CMD;
}

/*******************************************************************************
  Function:   P_RESP_Strings_Enum_T GetBTLE_CmdResponseIndexFrom_BTLE_Resp_Strings(const char *RespString)
  Summary:
  Description:   returns the index of the Response Array string.
  Precondition:    None.
  Parameters:    const char * - Response string.
  Returns:    Returns the enum of the Response string from Response String Array.
  Remarks:
/******************************************************************************/

P_RESP_Strings_Enum_T GetBTLE_CmdResponseIndexFrom_BTLE_Resp_Strings(const char *RespString)
{
    P_RESP_Strings_Enum_T index;

    for (index = ePERI_RESP_INVALID; index < gusBTLE_CmdResp_StructSize; index++)
    {
        if (!strcmp(RespString, BTLE_CmdResp_Strings[index].Response))
            return index;

    }
    return ePERI_RESP_NOT_FOUND_IN_THE_LIST;
}


/*******************************************************************************
  Function:
    unsigned char AssignTheIndexUsingtheValueFromCmdTobeExecuted(const P_CMD_Strings_Enum_T lCmdString)
  Summary:
  Description:   returns the index of the CmdArray.
  Precondition:    None.
  Parameters:    None.
  Returns:    unsigned char.
  Remarks:
/******************************************************************************/

unsigned char AssignTheIndexUsingtheValueFromCmdTobeExecuted(const P_CMD_Strings_Enum_T lCmdString)
{
    unsigned char lIndex;
    for (lIndex = ePERI_INVALID_CMD; lIndex < gusBTLE_NumOfCmdsToBeExecuted; lIndex++)
    {
        if (lCmdString == gCommands_ToBeExecuted[lIndex])
        {
            return lIndex;
        }
    }
    return ePERI_INVALID_CMD; // Shouldnt come here at all.
}


/*******************************************************************************
  Function:   unsigned char GetBTLE_Connected_Status(void)
  Summary: This function returns the status of BLE connected status.
  Description:
     returns 1 when BLE peripheral is connected.
     return 0 when BLE peripheral is not connected.
  Precondition:    None.
  Parameters:    None.
  Returns:    None.
  Remarks:
/******************************************************************************/

unsigned char GetBTLE_Connected_Status(void)
{
    volatile unsigned char Status;
    Status = BTLE_Connected_Status;
    __delay_ms(1);
    if (Status && (BTLE_Connected_Status == Status) && gBlueToothConnected)
    {
        return 1;
    }
    return 0;
}

