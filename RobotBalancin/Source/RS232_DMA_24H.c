/*
* Proyecto: MOISE Micros 16bits 2014
* Fichero: RS232_DMA_24H.c
*
* Grupo: G0    Autor: Luis
* 	Fecha: 2014-X-30
* v1.0
 * 
Recibe por RS232_1 y transmite por RS232_2
RS232_1 por interrupciones

No utiliza RTS
*/


#include "p24hj256gp610A.h"
#include "RS232_24H_2.h"

// I/O definitions for the Explorer16
//#define TRTS    TRISFbits.TRISF13   // tris control for RTS pin


unsigned int num_datos ;
unsigned int num_datos_vacio;
unsigned char dato_rs232_1;
unsigned char dato_rs232_2;

unsigned char RS232_int_cont;

//extern unsigned char Ventana_LCD [2][16];

//extern unsigned int Fila_LCD;

//unsigned int uart2RxBuffA[32] __attribute__((space(dma)));
//unsigned int uart2RxBuffB[32] __attribute__((space(dma)));
//unsigned char uart2TxBuffA[2][16] __attribute__((space(dma)));
//unsigned char uart2TxBuffB[2][16] __attribute__((space(dma)));
unsigned char Ventana_RS232[2][16] __attribute__((space(dma)));

//=============================================================================
//==============================================================================
// ================ Inicializa la UART2 Serial Port ======================

void initRS232_2_DMA( void)
{
// === Configuracion DMA asociado a UART 2 ====
// Requiere desactivar interrupciones UART 2
    DMA0CON = 0;
    // CHEN CANAL habilitado / deshabilitado
    DMA0CONbits.SIZE = 1;   // 1=Byte / 0=Word
    DMA0CONbits.DIR = 1; // 1= lee de DPSRAM y escribe en periférico
                         // 0= lee de periférico y escribe en DPSRAM
    // DMA0CONbits.HALF =?      // 1= interrupcion a  mitad / 0= al final
    // DMA0CONbits.NULLW =?     // 1= Escribe nulos / 0= operacion normal
    // DMA0CONbits.AMODE =?     // 10: Direc.Indirect,Perif
                                // 01 Indir.Reg sin Post-incr
                                // 00 Indir.Reg con Post-Incr
    DMA0CONbits.MODE = 0;   // 11: Un bloque + PingPong
                            // 10: Continuo + PingPong
                            // 01: Un bloque
                            // 00: Continuo

//   DMA0REQ Selecciona nº IRQ Periferico
    DMA0REQbits.FORCE = 0; // 1= manual / 0= automático
    // IRQSEL Selecciona nº IRQ Periferico
        // 0x00 INT0
        // 0x01 IC1
        // 0x02 OC1
        // 0x05 IC2
        // 0x06 OC2
        // 0x07 TMR2
        // 0x08 TMR3
        // 0x0A SPI1
        // 0x0B UART1RX
        // 0x0C UART1TX
        // 0x0D ADC1
        // 0x15 ADC2
        // 0x1E UART2RX
    DMA0REQbits.IRQSEL = 0x1F; // UART2TX
        // 0x21 SPI2
        // 0x22 ECAN1-RX
        // 0x37 ECAN2-RX
        // 0x46 ECAN1-TX
        // 0x47 ECAN2-TX
   // DMA0STA = __builtin_dmaoffset(uart2TxBuffA);    //0;    // Inicio dir. offset
   // DMA0STB = __builtin_dmaoffset(uart2TxBuffB);    //0x0020;    // Inicio dir. offset
    DMA0STA = __builtin_dmaoffset(Ventana_RS232);    //0;    // Inicio dir. offset
    DMA0STB = __builtin_dmaoffset(Ventana_RS232);    //0x0020;    // Inicio dir. offset

    DMA0PAD = (volatile unsigned int)&U2TXREG;      // Dirección del periférico
    DMA0CNT = 32-1;     // Nº de trasnsferencias -1
    DMACS0 = 0;         // Borra flags de Colisiones

//    IPC1bits.DMA0IP = ?;
    INTCON1bits.DMACERR = 0;    // Borraa Flag de interrupción de colisiones
    IFS0bits.DMA0IF = 0;
    IEC0bits.DMA0IE = 1;        // Habilita interrupciones DMA 0

    DMA0CONbits.CHEN = 1;   // Enable canal 0 DMA

// **************************
Nop();
Nop();
// No requerido, lo hace el hardware
//    UART2_TX_TRIS = 0;
//    UART2_RX_TRIS = 1;
//    UART2_TX_LAT  = 1;
//    UART2_RX_LAT  = 1;

    U2MODE = 0;		// 8bits, sin paridad, 1 stop, Uart parada
//  _UARTEN_U2	=;	// Habilita UART
//  _USIDL_U2	=;	// 0-> continua en modo Idle
//  _IREN_U2	=;	// Habilita IrDA
//  _RTSMD_U2	=;	// Modo pata U2RTS
//  _UEN_U2	=;		// Habilita U2TX, U2RX, U2CTS y U2RTS
//  _WAKE_U2	=;	// Habilita Wake-up al detectar Start en Sleep
//  _LPBACK_U2	=;	// Habilita modo Loopback
//  _ABAUD_U2	=;	// Habilita Auto-Baud
//  _RXINV_U2	=;	// Invierte polaridad para recepción
    _BRGH_U2	=0;	// BRGH
//  _PDSEL_U2	=;	// Paridad: 00= 8 bits sin paridad
//  _STSEL_U2	=;	// Duración bit Stop

    U2BRG = BAUD_RATEREG_2_BRGH0;
//  U2BRG = 8;		// Aplicando la formula da 7 y no va bien

    U2STA = 0;
//  _UTXISEL_U2 =;	// Tipo Interrupción Transmisión
//  _UTXINV_U2 =;	// Invierte polaridad pata transmisión
//  _UTXBRK_U2 =;	// Bit Breal
//  _UTXEN_U2 =;	// Habilita Transmisión
//  _UTXBF_U2 =;	// Estado Buffer transmisión (solo lectura)
//  _TRMT_U2 =;         // Estado Reg.Desplazamiento (solo lectura)
//  _URXISEL_U2 =;	// Tipo interrupción en recepción
                        // 0x= interrupción con cada dato que llega
			// 10= interrupción a 3/4 del buffer
			// 11= interrupción cuando buffer lleno
//  _ADDEN_U2 =;	// Detección bit de dirección en 9 bits
//  _RIDLE_U2 =;	// Estado de la recepción (solo lectura)
//  _PERR_U2 =;         // Error de paridad /solo lectura)
//  _FERR_U2 =;         // Error de trama (solo lectura)
//  _OERR_U2 =;         // Error ocerrun (borrable/ solo lectura)
//  _URXDA_U2 =;	// 0=buffer vacío, 1= al menos un dato

    _U2RXIF = 0; 	// Borra flag int. RX
    _U2TXIF = 0; 	// Borra flag int. TX
    _U2EIF = 0;         // Boorra flag de Error UART
//  _U2TXIE = 1; 	// Habilita int. de transmisión
//  _U2RXIE = 1;
//  _U2EIE = 1;         // Habilita Int_ de Error UART

    _OERR_U2=0; // Según versión corrige bugg

    _UARTEN_U2 = 1; 	// Habilita la UART_2
    _UTXEN_U2 = 1; //Habilita transmisión, Debe activarse despues habilitar UART

// ESPERAR LA DURACION DE UN BIT ANTES DE TRANSMITIR
//    U2TXREG = 0;
}

/*const char Texto_LCD_1[]= {"S6>CAD|S3-S4>PLY" // 16 caracteres Fila 1
                           "Crono: --/--/-- "}; // 16 caracteres Fila 2*/
void Copia_FLASH_RAM_RS232(char Texto_RS232_1[])
{

      int j;
      for (j=0; j<32;j++)
      {
        Ventana_RS232[0][j] = Texto_RS232_1[j];
        Nop();
    }
}

//========================================================
// === Atención Interrupcione DMA ===================
//void __attribute__((__interrupt__)) _DMA0Interrupt(void)
void _ISR _DMA0Interrupt(void)
{
Nop();
Nop();
Nop();
IFS0bits.DMA0IF = 0;
}

// Rutina de servicio de interrupción del Timer1
/*extern int microsegundos;
extern int _TmicrosegIF;
void _ISR _T_Microseg_Interrupt( void)
{
    microsegundos++ ;    // se incrementa cada milisegundo

    _TmicrosegIF = 0;	// Borra flag de interrpción
} // Fin T1Interrupt */

void __attribute__((__interrupt__)) _DMACError(void)
{
static unsigned int ErrorLocation;
// Peripheral Write Collision Error Location if(DMACS0 & 0x0100)
{
ErrorLocation = DMA0STA;
}
// DMA RAM Write Collision Error Location if(DMACS0 & 0x0002)
{
ErrorLocation = DMA1STA;
}
DMACS0 = 0; //Clear Write Collision Flag
INTCON1bits.DMACERR = 0; //Clear Trap Flag
}

//========================================================
// ================ TRANSMISION RS232_2 ==================
// Envía un caracter por la UART2 
char putRS232_2( char c)
{
    while ( _UTXBF_U2 == 1);    // Espera mientras buffer Tx está lleno
    U2TXREG = c;                // Carga dato a transmitir
    return c;
} // FINputRS232_2

//==================
// Envía string de bytes hasta encontrar el caracter de fin (nulo) por la UART2
void putST_RS232_2( char *s)
{
    while( s)		// Bucle hasta *s == '\0' fin de string
    putRS232_2( *s++);	// envía dato y apunta al siguiente
//    putU2( '\r');     // Envía un CR = line feed
} // FIN putST_RS232_2

// ================ RECEPCION RS232_2 ==================
// Espera a recibir un caracter por la UART2
char getRS232_2( void)
{
    while ( !_URXDA_U2);	// Espera a que llegue un dato
    return U2RXREG;		// recoge el dato
}// FIN getRS232_2


//------------------------------------------------------------------------------
//   Funciones de gestion de interrupciones UART
//------------------------------------------------------------------------------
// ================ Servicio INTERRUPCION TRANSMISION RS232_2 ==================
// Trasmite un dato, si hay, al final de transmisión del anterior
void _ISR _U2TXInterrupt(void)
{
    U2TXREG = 'H';  // Envía dato
    _U2TXIF = 0;
} //	FIN _U2RXInterruptt

void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt (void)
{
Nop();
Nop();
_U2EIF = 0;
}



