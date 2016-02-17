/*
Proyecto: PIC24H Brazo robotico 
Fichero: servo.h

Grupo: 2    Autor: Markel
 *
 */


#include "p24HJ256GP610A.h"

#define Servo_timer 2

#define TROCMotor1 _TRISD0
#define TROCMotor2 _TRISD1
#define TROCMotor3 _TRISD2
#define TROCMotor4 _TRISD3

//Variables

extern float angulo;

#if (Servo_timer == 2)
#define _T_Servo_interrupt _T2Interrupt
#define _T_ServoIF _T2IF
#elif (Servo_timer == 3)
#define _T_Servo_interrupt _T3Interrupt
#define _T_ServoIF _T3IF
#elif (Servo_timer != 2 && Servo_timer != 3)
#error (" TIMER para CRONO NO DEFINIDO")
#endif
