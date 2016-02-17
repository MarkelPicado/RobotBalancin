
/*******************************************************************************
 Explorer 16 Demo peripheral File
  Company:    Microchip Technology Inc.
  File Name:    peripheral_string.c
  Summary:    Explorer 16 Demo peripheral strings File.
  Description:
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
 *******************************************************************************/
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "peripheral_string.h"

const Peripheral_Command_Strings_T BTLE_Cmd_Strings[] = {
    {ePERI_INVALID_CMD, ""},
    {ePERI_COMMAND_MODE, ""},
    {ePERI_ENABLE_ECHO, "+\r\n"},
    {ePERI_FACTORY_RESET, "SF,1\r\n"},
    {ePERI_CH_DNAME, "SN,MarkelPi\r\n"}, //MAX 8 Caracteres.
    {ePERI_SR_COMMAND, "SR,32060000\r\n"},
    {ePERI_AUTO_ADVERTISE, "A\r\n"},
    {ePERI_STOP_ADVERTISE_COMMAND, "Y\r\n"},
    {ePERI_REBOOT_COMMAND, "R,1\r\n"},
    {ePERI_PAIR_REQUEST, ""},
    {ePERI_BONDING_REQUEST, "B\r\n"},
    {ePERI_GET_VERSION_COMMAND, "V\r\n"},
    {ePERI_GR_COMMAND, "gr\r\n"},
    {ePERI_GN_COMMAND, "gn\r\n"},
    {ePERI_SN_COMMAND, "sn\r\n"},
    {ePERI_WC_COMMAND, "wc\r\n"},
//    {ePERI_MLDP_COMMAND, "I\r\n"},
//    {ePERI_BAUD_CHANGE_SB_COMMAND, "SB,1\r\n"}, // Reset to 9600.   
};

const Peri_Resp_Strings_T BTLE_CmdResp_Strings[] = {
    {ePERI_RESP_INVALID, " "},
    {ePERI_RESP_ERR, "ERR\r\n"},
    {ePERI_RESP_AOK, "AOK\r\n"},
    {ePERI_RESP_AOK1, "AOK1\r\n"},
    {ePERI_RESP_AOK2, "AOK2\r\n"},
    {ePERI_RESP_CMD, "CMD\r\n"},
    {ePERI_RESP_ECHO_ON, "Echo On\r\n"},
    {ePERI_RESP_ECHO_OFF, "Echo Off\r\n"},
    {ePERI_RESP_REBOOT, "Reboot\r\n"},
    {ePERI_RESP_CONNECTED, "Connected\r\n"},
    {ePERI_RESP_CONNECTION_END, "Connection End\r\n"},
    {ePERI_RESP_BONDED, "Bonded\r\n"},
    {ePERI_RESP_MLDP_MODE, "MLDP\r\n"},
};

unsigned short gusBTLE_Cmd_StructSize = sizeof(BTLE_Cmd_Strings)/sizeof(Peripheral_Command_Strings_T);
unsigned short gusBTLE_CmdResp_StructSize = sizeof(BTLE_CmdResp_Strings)/sizeof(Peri_Resp_Strings_T);


