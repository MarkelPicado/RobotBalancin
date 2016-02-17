#ifndef CONFIG_H
#define CONFIG_H

/*******************************************************************************
 Explorer 16 Demo for Peripheral Node config File
  Company:    Microchip Technology Inc.
  File Name:    config.h
  Summary:    Explorer 16 Demo for Peripheral Node
  Description:
    This is the file for the Explorer 16 Peripheral Node Demo that contains all the variables
    and functions used commonly across the application.
 *******************************************************************************/
// *****************************************************************************
// Section: Included Files
// *****************************************************************************

/** Preprocessor Macros **********************************************************/

/*******************************************************************************************
* Device Configuration.
********************************************************************************************/

//#include <p24fxxxx.h>
#include <p24hxxxx.h>

//#define FCY_IN_Mhz                        (16)
#define FCY_IN_Mhz                        (40)
#define FCY                               (FCY_IN_Mhz * 1000000ul)

#include <libpic30.h>
#include <string.h>


/* Demo Variables and Functions Data Structure
  Summary:
    Defines the data required by the demo in a data structure
  Description:
    This data structure defines the data required by the Explorer 16 Demo
 Remarks:
    None.
*/

#define _ISR_NO_AUTO_PSV __attribute__((interrupt,no_auto_psv))

#define mEND_OF_PACKET_CHARACTER       ('\n')


/*******************************************************************************************
* Timeout macro.
********************************************************************************************/
#define TimeOut_XmS                         ((FCY/256) * 0.050) // 50mS timeout
#define mTimer_INTR_Priority                 (4)

/*******************************************************************************************
* UART Baud Configuration.
********************************************************************************************/
#define BAUDRATE            (115200)
#define BRG_115200          ((FCY + 230400ul) / 460800ul - 1)
#define BRGVAL              ((FCY/BAUDRATE)/4)-1

/*******************************************************************************************
* Control Remoto.
********************************************************************************************/

typedef enum 
{
    ePERI_CONTROL_NOT_IN_THE_LIST,
    ePERI_GO_FORDWARD,
    ePERI_GO_BACK,
    ePERI_TURN_RIGHT,
    ePERI_TURN_LEFT,
    ePERI_STOP,
}   P_BTLE_PERI_CONTROL_T;

typedef struct 
{
    P_BTLE_PERI_CONTROL_T ePeri_Control_enumeration;
    const char *String;
}   BTLE_Peri_Control_T;

typedef enum BTLE_PERI_SW_LED_Tag
{
    ePERI_LED_SW_NOT_IN_THE_LIST,
    ePERI_LED_D1_ON,
    ePERI_LED_D1_OFF,
    ePERI_LED_D2_ON,
    ePERI_LED_D2_OFF,
    ePERI_SW_S1_PRESSED,
    ePERI_SW_S1_RELEASED,
    ePERI_SW_S2_PRESSED,
    ePERI_SW_S2_RELEASED,
}   P_BTLE_PERI_SW_LED_T;

typedef struct BTLE_Peri_Sw_LED_Tag
{
    P_BTLE_PERI_SW_LED_T ePeri_Sw_LED_enumeration;
    const char *String;
}   BTLE_Peri_Sw_LED_T;

typedef enum P_CMD_Strings_Enum_Tag
{
    ePERI_INVALID_CMD,
    ePERI_COMMAND_MODE,
    ePERI_ENABLE_ECHO,
    ePERI_GET_VERSION_COMMAND,
    ePERI_GR_COMMAND,
    ePERI_GN_COMMAND,
    ePERI_SN_COMMAND,
    ePERI_WC_COMMAND,
    ePERI_CH_DNAME,
    ePERI_FACTORY_RESET,
    ePERI_SR_COMMAND,
    ePERI_STOP_ADVERTISE_COMMAND,
    ePERI_REBOOT_COMMAND,
    ePERI_AUTO_ADVERTISE,
    ePERI_PAIR_REQUEST,
    ePERI_BONDING_REQUEST,
}P_CMD_Strings_Enum_T;

typedef union
{
    struct
    {
        unsigned char s1_sw_Old        :1;
        unsigned char s1_sw_current    :1;
        unsigned char s2_sw_Old        :1;
        unsigned char s2_sw_current    :1;
        unsigned char s3_sw_Old        :1;
        unsigned char s3_sw_current    :1;
        unsigned char s4_sw_Old        :1;
        unsigned char s4_sw_current    :1;
    };
    unsigned char SwitchStatus;
} HW_SWITCHES_T;


extern const P_CMD_Strings_Enum_T gCommands_ToBeExecuted[];
extern P_BTLE_PERI_SW_LED_T GetBTLE_ResponseIndexFrom_BTLE_SW_LEDResp_Strings(const char *);
extern const char *GetBTLE_RespStringFrom_BTLE_SW_LEDResp_Strings(P_BTLE_PERI_SW_LED_T lenum);


/*******************************************************************************************
 * PIC24FJ128GA010 Configuration
 * *****************************************************************************************/
#define ANALOG                            (0)

typedef union
{
    HW_SWITCHES_T Hw_Sw;
    struct
    {
        unsigned char s3_sw_Old        :1;
        unsigned char s3_sw_current    :1;
        unsigned char s6_sw_Old        :1;
        unsigned char s6_sw_current    :1;
        unsigned char s5_sw_Old        :1;
        unsigned char s5_sw_current    :1;
        unsigned char s4_sw_Old        :1;
        unsigned char s4_sw_current    :1;
    };
} EXP16_SWITCHES;


/******************************************************************************************
* BTLE UART interface to PIC module
******************************************************************************************/
#define PIC_TO_BTLE_UART_MODULE_1
//#define PIC_TO_BTLE_UART_MODULE_2
//#define PIC_TO_BTLE_UART_MODULE_3

#define UART_MOD_1 (0)
#define UART_MOD_2 (1)
#define UART_MOD_3 (2)

#define PIC_U_Tx_BTLE_U_RX_ANALOG_BIT ()
#define PIC_U_Tx_BTLE_U_Rx_TRIS_Pin   (_TRISF3)

#define PIC_U_Rx_BTLE_U_Tx_ANALOG_BIT ()
#define PIC_U_Rx_BTLE_U_Tx_TRIS_Pin   (_TRISF2)

#if defined (PIC_TO_BTLE_UART_MODULE_1)
    #define PIC_UART_MODULE                (UART_MOD_1)
    #define UART_RX_INT_FLAG               (_U1RXIF)
    #define UART_RX_INT_Priority           (_U1RXIP)
    #define UART_RX_INT_ENABLE             (_U1RXIE)
//   #define UART_ERROR_INT_FLAG            (_U1ERIF)
    #define UART_ERROR_INT_FLAG            (_U1EIF)
    #define UART_TX_INT_FLAG               (_U1TXIF)

    #elif defined (PIC_TO_BTLE_UART_MODULE_2)

      #define PIC_UART_MODULE                (UART_MOD_2)
      #define UART_RX_INT_FLAG               (_U2RXIF)
      #define UART_RX_INT_Priority           (_U2RXIP)
      #define UART_RX_INT_ENABLE             (_U2RXIE)
      #define UART_ERROR_INT_FLAG            (_U2ERIF)
      #define UART_TX_INT_FLAG               (_U2TXIF)

    #elif defined (PIC_TO_BTLE_UART_MODULE_3)

      #define PIC_UART_MODULE                (UART_MOD_3)
      #define UART_RX_INT_FLAG               (_U3RXIF)
      #define UART_RX_INT_Priority           (_U3RXIP)
      #define UART_RX_INT_ENABLE             (_U3RXIE)
      #define UART_ERROR_INT_FLAG            (_U3ERIF)
      #define UART_TX_INT_FLAG               (_U3TXIF)

    #endif


/******************************************************************************************
    * BTLE IO interface to PIC module
******************************************************************************************/

#define BTLE_To_PIC_SWAKE_PIO3_TRIS          (_TRISF1)
#define BTLE_To_PIC_SWAKE_PIO3_LAT           (_LATF1)
#define BTLE_To_PIC_SWAKE_PIO3_PORT          (_RF1)
//#define BTLE_To_PIC_SWAKE_PIO3_ANALOG      ()

#define BTLE_To_PIC_CMD_DATA_PIO4_TRIS       (_TRISF0)
#define BTLE_To_PIC_CMD_DATA_PIO4_LAT        (_LATF0)
#define BTLE_To_PIC_CMD_DATA_PIO4_PORT       (_RF0)
//#define BTLE_To_PIC_CMD_DATA_PIO4_ANALOG     ()


#define BTLE_PAIRED_PIO5_TRIS                (_TRISF6)
#define BTLE_PAIRED_PIO5_LAT                 (_LATF6)
#define BTLE_PAIRED_PIO5_PORT                (_RF6)
#define BTLE_Connected_Status                (BTLE_PAIRED_PIO5_PORT)
//#define BTLE_To_PIC_PIO5_ANALOG            ()

#define BTLE_ACTIVE_PIO7_TRIS                (_TRISF8)
#define BTLE_ACTIVE_PIO7_LAT                 (_LATF8)
#define BTLE_ACTIVE_PIO7_PORT                (_RF8)
//#define BTLE_To_PIC_PIO7_ANALOG            (_ANSA0)


/*=========================================================================
 * LEDs
 * =======================================================================*/
#define XPL16_D10_LED_TRIS                 (_TRISA7)
#define XPL16_D10_LED_LAT                  (_LATA7)
#define XPL16_D10_LED_PORT                 (_RA7)
#define XPL16_D10_LED_TurnON               (1)
#define XPL16_D10_LED_TurnOFF              !(XPL16_D10_LED_TurnON)


#define XPL16_D9_LED_TRIS                 (_TRISA6)
#define XPL16_D9_LED_LAT                  (_LATA6)
#define XPL16_D9_LED_PORT                 (_RA6)
#define XPL16_D9_LED_TurnON               (1)
#define XPL16_D9_LED_TurnOFF              !(XPL16_D9_LED_TurnON)


#define XPL16_D8_LED_TRIS                 (_TRISA5)
#define XPL16_D8_LED_LAT                  (_LATA5)
#define XPL16_D8_LED_PORT                 (_RA5)
#define XPL16_D8_LED_TurnON               (1)
#define XPL16_D8_LED_TurnOFF              !(XPL16_D8_LED_TurnON)


#define XPL16_D7_LED_TRIS                 (_TRISA4)
#define XPL16_D7_LED_LAT                  (_LATA4)
#define XPL16_D7_LED_PORT                 (_RA4)
#define XPL16_D7_LED_TurnON               (1)
#define XPL16_D7_LED_TurnOFF              !(XPL16_D7_LED_TurnON)

#define XPL16_D5_LED_TRIS                 (_TRISA2)
#define XPL16_D5_LED_LAT                  (_LATA2)
#define XPL16_D5_LED_PORT                 (_RA2)
#define XPL16_D5_LED_TurnON               (1)
#define XPL16_D5_LED_TurnOFF              !(XPL16_D5_LED_TurnON)

#define XPL16_D4_LED_TRIS                 (_TRISA1)
#define XPL16_D4_LED_LAT                  (_LATA1)
#define XPL16_D4_LED_PORT                 (_RA1)
#define XPL16_D4_LED_TurnON               (1)
#define XPL16_D4_LED_TurnOFF              !(XPL16_D4_LED_TurnON)

#define XPL16_D3_LED_TRIS                 (_TRISA0)
#define XPL16_D3_LED_LAT                  (_LATA0)
#define XPL16_D3_LED_PORT                 (_RA0)
#define XPL16_D3_LED_TurnON               (1)
#define XPL16_D3_LED_TurnOFF              !(XPL16_D3_LED_TurnON)


/*=========================================================================
 * Switches
 * =======================================================================*/
#define SWITCH_S1_TRIS                  (_TRISD6)
#define SWITCH_S1_LAT                   (_LATD6)
#define SWITCH_S1_PORT                  (_RD6)
#define SWITCH_S1_CN_INTERRUPT          (_CN15IE)


#define SWITCH_S2_TRIS                  (_TRISD7)
#define SWITCH_S2_LAT                   (_LATD7)
#define SWITCH_S2_PORT                  (_RD7)
#define SWITCH_S2_CN_INTERRUPT          (_CN16IE)

/*=========================================================================
 * LCD
 * =======================================================================*/

#define mUSE_ON_BOARD_LCD
// Control signal data pins
#define  LCD_RW         _LATD5       // LCD R/W signal
#define  LCD_RS         _LATB15      // LCD RS signal
#define  LCD_EN         _LATD4       // LCD E signal

// Control signal pin direction
#define  LCD_RW_TRIS    _TRISD5
#define  LCD_RS_TRIS    _TRISB15
#define  LCD_RS_Analog  _PCFG15
#define  LCD_EN_TRIS    _TRISD4

// Data signals and pin direction
#define  LCD_DATA_BUS   LATE                // Port for LCD data


#endif





