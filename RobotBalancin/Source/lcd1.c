/*******************************************************************************
 Explorer 16 Demo LCD File

  Company:
    Microchip Technology Inc.

  File Name:
    lcd.c

  Summary:
    Explorer 16 Demo LCD File.

  Description:
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
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


#include "config.h"
#include "lcd.h"

#ifdef mUSE_ON_BOARD_LCD


/*******************************************************************************

  Function:
   void LCD_Initialize(void)

  Summary:
    Function that Initializes LCD.

  Description:
  .

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void LCD_Initialize(void)
{
    // 15mS delay after Vdd reaches nnVdc before proceeding with LCD initialization
    // not always required and is based on system Vdd rise rate
    __delay_ms(15);                // 15ms delay

    /* set initial states for the data and control pins */
    LATE &= 0xFF00;
    LCD_RS_Analog = !ANALOG;
    LCD_RW = 0;                 // R/W state set low
    LCD_RS = 0;                 // RS state set low
    LCD_EN = 0;                 // E state set low

    /* set data and control pins to outputs */
    TRISE &= 0xFF00;
    LCD_RW_TRIS = 0;            // RW pin set as output
    LCD_RS_TRIS = 0;            // RS pin set as output
    LCD_EN_TRIS = 0;            // E pin set as output

    /* 1st LCD initialization sequence */
    LCD_DATA_BUS &= 0xFF00;
    LCD_DATA_BUS |= 0x0038;     // Put 0x38 on the data bus
    LCD_EN = 1;                 // Enable pin high
    Nop();                      // Short delay for enable pulse
    Nop();
    Nop();
    LCD_EN = 0;                 // Enable pin low
    __delay_ms(5);                 // 5ms delay

    /* 2nd LCD initialization sequence */
    LCD_DATA_BUS &= 0xFF00;
    LCD_DATA_BUS |= 0x0038;     // Put 0x38 on the data bus
    LCD_EN = 1;                 // Enable pin high
    Nop();                      // Short delay for enable pulse
    Nop();
    Nop();
    LCD_EN = 0;                 // Enable pin low
    __delay_us(200);               // 200uS delay

    /* 3rd LCD initialization sequence */
    LCD_DATA_BUS &= 0xFF00;
    LCD_DATA_BUS |= 0x0038;     // Put 0x38 on the data bus
    LCD_EN = 1;                 // Enable pin high
    Nop();                      // Short delay for enable pulse
    Nop();
    Nop();
    LCD_EN = 0;                 // Enable pin low
    __delay_us(200); // 200uS delay

    LCD_WriteCommand(0x38);     // Set function
    LCD_WriteCommand(0x0C);     // Display on/off control, cursor blink off (0x0C)
    LCD_WriteCommand(0x06);     // Set entry mode (0x06)
}

/*******************************************************************************

  Function:
   void LCD_WriteCommand(char cmd)

  Summary:
    Write command to LCD module.

  Description:
  .

  Precondition:
    None.

  Parameters:
    unsigned char cmd.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void LCD_WriteCommand(char cmd)
{
    //	TRISD &= 0xFF00;        // ensure RD0 - RD7 are outputs
    LCD_DATA_BUS &= 0xFF00;
    LCD_DATA_BUS |= cmd;        // Put command byte on the data bus
    LCD_RW = 0;                 // RW is 0 for write
    LCD_RS = 0;                 // RS is 0 for control register
    LCD_EN = 1;                 // Enable pin high
    Nop();                      // Short delay for enable pulse
    Nop();
    Nop();
    LCD_EN = 0;                 // Enable pin low
    __delay_ms(5); // 5ms delay
}

/*******************************************************************************

  Function:
   void LCD_WriteData(char data)

  Summary:
    Write Data to LCD module.

  Description:
  .

  Precondition:
    None.

  Parameters:
    unsigned char data.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void LCD_WriteData(char data)
{
    //	TRISD &= 0xFF00;        // ensure RD0 - RD7 are outputs
    LCD_RW = 0;                 // RW is 0 for write
    LCD_RS = 1;                 // RS is 1 for data
    LCD_DATA_BUS &= 0xFF00;
    LCD_DATA_BUS |= data;       // Put data byte on the data bus
    LCD_EN = 1;                 // Enable pin high
    Nop();                      // Short delay for enable pulse
    Nop();
    Nop();
    LCD_EN = 0;                 // Enable pin low
    LCD_RS = 0;                 // negate register select to 0
    __delay_us(400);               // 400uS delay
}

/*******************************************************************************

  Function:
   void LCD_WriteString(char *data)

  Summary:
    Write String to LCD module.

  Description:
  .

  Precondition:
    None.

  Parameters:
    unsigned char *data.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void LCD_WriteString(char *data) {
    int i;
    for (i = 0; i < 16; i++) {      //Write up to 16 bytes
        if (*data != '\0')          //Check for the end of the text string
            LCD_WriteData(*data++); //Write the byte if it is not null
        else                        //else
            break;                  //we are done if the byte is null
    }
}

#endif