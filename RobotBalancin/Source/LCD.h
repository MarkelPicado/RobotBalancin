/*
Proyecto: PIC24H Brazo robotico 
Fichero: LCD.h

Grupo: 2    Autor: Markel
 */




// Patas utilizadas por el LCD en la Explorer 16
// RS -> RBx
// E -> RDx
// RW -> RDx
// DATA -> REx -

// Control signal data pins
void Inic_Timers_LCD();
void Inic_LCD(void);
void refrescar(int minutos, int segundos, int decimas);
void Copia_FLASH_RAM(char Texto_LCD[]
);
//========= Envío de COMANDO =========
void lcd_cmd( char cmd );
//======= Envio de DATO ===============
void lcd_data( char data );

#define Crono_lcd 4
#define Crono_actualizar_lcd 5
extern unsigned char Ventana_LCD [2][16];

#if(Crono_lcd == 1)
 #define Flag_lcd _T1IF
 #define PR_lcd PR1
 #define TCKPS1 T1CONbits.TCKPS1
 #define TCKPS0 T1CONbits.TCKPS0
 #define TMR_lcd  TMR1
 #define IE_lcd _T1IE
 #define TCONbitsTON  T1CONbits.TON
#elif(Crono_lcd == 2)
 #define Flag_lcd _T2IF
 #define PR_lcd PR2
 #define TCKPS1 T1CONbits.TCKPS1
 #define TCKPS0 T1CONbits.TCKPS0
 #define TMR_lcd  TMR2
 #define IE_lcd _T2IE
 #define TCONbitsTON  T2CONbits.TON
#elif(Crono_lcd == 3)
 #define Flag_lcd _T3IF
 #define PR_lcd PR3
 #define TCKPS1 T1CONbits.TCKPS1
 #define TCKPS0 T1CONbits.TCKPS0
 #define TMR_lcd  TMR3
 #define IE_lcd _T3IE
 #define TCONbitsTON  T3CONbits.TON
#elif(Crono_lcd == 4)
 #define Flag_lcd _T4IF
 #define PR_lcd PR4
 #define TCKPS1 T1CONbits.TCKPS1
 #define TCKPS0 T1CONbits.TCKPS0
 #define TMR_lcd  TMR4
 #define IE_lcd _T4IE
 #define TCONbitsTON  T4CONbits.TON
#elif(Crono_lcd == 5)
 #define Flag_lcd _T5IF
 #define PR_lcd PR5
 #define TCKPS1 T1CONbits.TCKPS1
 #define TCKPS0 T1CONbits.TCKPS0
 #define TMR_lcd  TMR5
 #define IE_lcd _T5IE
 #define TCONbitsTON  T5CONbits.TON
#elif(Crono_lcd == 6)
 #define Flag_lcd _T6IF
 #define PR_lcd PR6
 #define TCKPS1 T1CONbits.TCKPS1
 #define TCKPS0 T1CONbits.TCKPS0
 #define TMR_lcd  TMR6
 #define IE_lcd _T6IE
 #define TCONbitsTON  T6CONbits.TON
#elif(Crono_lcd == 7)
 #define Flag_lcd _T7IF
 #define PR_lcd PR7
 #define TCKPS1 T1CONbits.TCKPS1
 #define TCKPS0 T1CONbits.TCKPS0
 #define TMR_lcd  TMR7
 #define IE_lcd _T7IE
 #define TCONbitsTON  T7CONbits.TON
#elif(Crono_lcd == 8)
 #define Flag_lcd _T8IF
 #define PR_lcd PR8
 #define TCKPS1 T1CONbits.TCKPS1
 #define TCKPS0 T1CONbits.TCKPS0
 #define TMR_lcd  TMR8
 #define IE_lcd _T8IE
 #define TCONbitsTON  T8CONbits.TON
#elif(Crono_lcd == 9)
 #define Flag_lcd _T9IF
 #define PR_lcd PR9
 #define TCKPS1 T1CONbits.TCKPS1
 #define TCKPS0 T1CONbits.TCKPS0
 #define TMR_lcd  TMR9
 #define IE_lcd _T9IE
 #define TCONbitsTON  T9CONbits.TON
#elif(Crono_lcd == 0|| Crono_lcd >= 9)
#error("TIMER para lcd NO DEFINIDO")
#endif

#if(Crono_actualizar_lcd == 1)
 #define _TActualizarInterrupt _T1Interrupt
 #define TMR_Actualizar TMR1
 #define PR_Actualizar PR1
 #define CON_Actualizar T1CON
 #define CONbitsTON_Actualizar T1CONbits.TON
 #define Flag_Actualizar _T1IF
 #define IE_Actualizar _T1IE
#elif(Crono_actualizar_lcd == 2)
 #define _TActualizarInterrupt _T2Interrupt
 #define TMR_Actualizar TMR2
 #define PR_Actualizar PR2
 #define CON_Actualizar T2CON
 #define CONbitsTON_Actualizar T2CONbits.TON
 #define Flag_Actualizar _T2IF
 #define IE_Actualizar _T2IE
#elif(Crono_actualizar_lcd == 3)
 #define _TActualizarInterrupt _T3Interrupt
 #define TMR_Actualizar TMR3
 #define PR_Actualizar PR3
 #define CON_Actualizar T3CON
 #define CONbitsTON_Actualizar T3CONbits.TON
 #define Flag_Actualizar _T3IF
 #define IE_Actualizar _T3IE
#elif(Crono_actualizar_lcd == 4)
 #define _TActualizarInterrupt _T4Interrupt
 #define TMR_Actualizar TMR4
 #define PR_Actualizar PR4
 #define CON_Actualizar T4CON
 #define CONbitsTON_Actualizar T4CONbits.TON
 #define Flag_Actualizar _T4IF
 #define IE_Actualizar _T4IE
#elif(Crono_actualizar_lcd == 5)
 #define _TActualizarInterrupt _T5Interrupt
 #define TMR_Actualizar TMR5
 #define PR_Actualizar PR5
 #define CON_Actualizar T5CON
 #define CONbitsTON_Actualizar T5CONbits.TON
#define Prioridad_LCD _T5IP
 #define Flag_Actualizar _T5IF
 #define IE_Actualizar _T5IE
#elif(Crono_actualizar_lcd == 6)
 #define _TActualizarInterrupt _T6Interrupt
 #define TMR_Actualizar TMR6
 #define PR_Actualizar PR6
 #define CON_Actualizar T6CON
 #define CONbitsTON_Actualizar T6CONbits.TON
 #define Flag_Actualizar _T6IF
 #define IE_Actualizar _T6IE
#elif(Crono_actualizar_lcd == 7)
 #define _TActualizarInterrupt _T7Interrupt
 #define TMR_Actualizar TMR7
 #define PR_Actualizar PR7
 #define CON_Actualizar T7CON
 #define CONbitsTON_Actualizar T7CONbits.TON
 #define Flag_Actualizar _T7IF
 #define IE_Actualizar _T7IE
#elif(Crono_actualizar_lcd == 8)
 #define _TActualizarInterrupt _T8Interrupt
 #define TMR_Actualizar TMR8
 #define PR_Actualizar PR8
 #define CON_Actualizar T8CON
 #define CONbitsTON_Actualizar T8CONbits.TON
 #define Flag_Actualizar _T8IF
 #define IE_Actualizar _T8IE
#elif(Crono_actualizar_lcd == 9)
 #define _TActualizarInterrupt _T9Interrupt
 #define TMR_Actualizar TMR9
 #define PR_Actualizar PR9
 #define CON_Actualizar T9CON
 #define CONbitsTON_Actualizar T9CONbits.TON
 #define Flag_Actualizar _T9IF
 #define IE_Actualizar _T9IE
#elif(Crono_actualizar_lcd == 0|| Crono_actualizar_lcd >= 9)
#error("TIMER para lcd NO DEFINIDO")
#endif
