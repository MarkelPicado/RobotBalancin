/*
Proyecto: PIC24H Brazo robotico 
Fichero: CAD.h

Grupo: 2    Autor: Markel
 */

#define Crono_CAD 8
extern unsigned int ADCValue;
extern unsigned int valorPotenciometro;
#define _chX 0x0008
#define _chY 0x0009
#define _chLat 0x000A
#define _chPotenciometro 0x0005
#define _chTemperatura 0x0004
#define Val1 servoX //Lee el valor del joystic del eje x para controlar el Servo que controla el EJE X del robot
#define Val2 servoY //Lee el valor del joystic del eje y para controlar el Servo que controla el EJE Y del robot
#define Val3 palanca //Lee el valor del joystic de la palanca y para controlar el Servo que controla el CODO del robot
//#define Val4 variable
//#define Val5 variable
//#define Val6 variable
#if(Crono_CAD == 1)
 #define PR_CAD PR1
 #define CON_CAD T1CON
 #define CONbitsTON_CAD T1CONbits.TON
 #define Flag_CAD _T1IF
 #define IE_CAD _T1IE
 #define _TCADInterrupt _T1Interrupt
#elif(Crono_CAD == 2)
 #define PR_CAD PR2
 #define CON_CAD T2CON
 #define CONbitsTON_CAD T2CONbits.TON
 #define Flag_CAD _T2IF
 #define IE_CAD _T2IE
 #define _TCADInterrupt _T2Interrupt
#elif(Crono_CAD == 3)
 #define PR_CAD PR3
 #define CON_CAD T3CON
 #define CONbitsTON_CAD T3CONbits.TON
 #define Flag_CAD _T3IF
 #define IE_CAD _T3IE
 #define _TCADInterrupt _T3Interrupt
#elif(Crono_CAD == 4)
 #define PR_CAD PR4
 #define CON_CAD T4CON
 #define CONbitsTON_CAD T4CONbits.TON
 #define Flag_CAD _T4IF
 #define IE_CAD _T4IE
 #define _TCADInterrupt _T4Interrupt
#elif(Crono_CAD == 5)
 #define PR_CAD PR5
 #define CON_CAD T5CON
 #define CONbitsTON_CAD T5CONbits.TON
 #define Flag_CAD _T5IF
 #define IE_CAD _T5IE
 #define _TCADInterrupt _T5Interrupt
#elif(Crono_CAD == 6)
 #define PR_CAD PR6
 #define CON_CAD T6CON
 #define CONbitsTON_CAD T6CONbits.TON
 #define Flag_CAD _T6IF
 #define IE_CAD _T6IE
 #define _TCADInterrupt _T6Interrupt
#elif(Crono_CAD == 7)
 #define PR_CAD PR7
 #define CON_CAD T7CON
 #define CONbitsTON_CAD T7CONbits.TON
 #define Flag_CAD _T7IF
 #define IE_CAD _T7IE
 #define _TCADInterrupt _T7Interrupt
#elif(Crono_CAD == 8)
 #define PR_CAD PR8
 #define CON_CAD T8CON
 #define CONbitsTON_CAD T8CONbits.TON
 #define Flag_CAD _T8IF
 #define Prioridad_CAD _T8IP
 #define IE_CAD _T8IE
 #define _TCADInterrupt _T8Interrupt
#elif(Crono_CAD == 9)
 #define PR_CAD PR9
 #define CON_CAD T9CON
 #define CONbitsTON_CAD T9CONbits.TON
 #define Flag_CAD _T9IF
 #define IE_CAD _T9IE
 #define _TCADInterrupt _T9Interrupt
#elif(Crono_CAD == 0|| Crono_CAD >= 9)
#error("TIMER para lcd NO DEFINIDO")
#endif
