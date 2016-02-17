/*
Proyecto: PIC24H Brazo robotico 
Fichero: servo.c

Grupo: 2    Autor: Markel

Descripcion: Este modulo principalmente se utiliza para darle valores a los servos
mediante el PWM. Aparte de esto tambien esta la funcion que escribe automaticamente un 10 
con el brazo robotico
*/

#include "p24HJ256GP610A.h"
#include "PWM.h"
#include "stdlib.h"
#include "comun.h"

#define OCValue1 Value1
#define OCValue2 Value2
#define OCValue3 Value3
#define OCValue4 Value4
#define OCValue5 Value5
#define OCValue6 Value6

/*
#define TRServo1 _TRISB11
#define TRServo2 _TRISB12
#define TRServo3 _TRISB13
#define TRServo4 _TRISB14
#define TRServo5 _TRISF7
#define TRServo6 _TRISF8

#define LTServo1 _LATB11
#define LTServo2 _LATB12
#define LTServo3 _LATB13
#define LTServo4 _LATB14
#define LTServo5 _LATF7
#define LTServo6 _LATF8
*/
#define Motor_A2_Tris _TRISB10
#define Motor_B1_Tris _TRISB11
#define Motor_A1_Tris _TRISB12
#define Motor_B2_Tris _TRISB13

#define Motor_A1_dir _LATB10
#define Motor_B1_dir _LATB11
#define Motor_A2_dir _LATB12
#define Motor_B2_dir _LATB13

#define EnableMotor1_Tris _TRISD10
#define EnableMotor2_Tris _TRISD11

#define EnableMotor1_Lat _LATD10
#define EnableMotor2_Lat _LATD11



int finEscritura;
int servo=1; //si no vas a usarlo poner 0 y si no 1
int total=12500;
int Value1,Value2,Value3,Value4,Value5,Value6;
int wStep=1;
int medio=0;
extern int outputPID;
extern float angulo;
extern float anguloFiltro;
extern float angulogiro;

int angulo1=0;
int angulo2=0;
int angulo3=0;
int anguloMedia=0;
extern unsigned int valorPotenciometro;
extern float Integral;
int dir;
extern int estadoRobot;
unsigned char Calcula_PWM = 0;

extern int velExtra_RD;
extern int velExtra_RI;

void inic_PWM(){
    //Motor_A1_Tris = 0;
    Motor_B1_Tris = 0;
    Motor_A2_Tris = 0;
    Motor_B2_Tris = 0;

    // Inicialización del modulo de Salida Comparada
     TROCMotor1=0; //_TRISD0=0;
     TROCMotor2=0; //_TRISD1=0;
     TROCMotor3=0; //_TRISD2=0;
     TROCMotor4=0; //_TRISD3=0;

    
     OC1CON = 0; // Reset del módulo
     OC2CON = 0;
     OC3CON = 0; // Reset del módulo
     OC4CON = 0;

     //OC1CONbits.OCTSEL = 0; // Selección del Timer 2 como timer de referencia
     OC2CONbits.OCTSEL = 0;
    
     OC1R = 0;   //Define el duty cycle para el primer pulso PWM 450 min 1600 max
     OC2R = 0;
     OC3R = 0;
     OC4R = 0;
     
     OC1RS = 0; // Define el duty cycle para el segundo pulso PWM
     OC2RS = 0;
     OC3RS = 0;
     OC4RS = 0;
     
     OC1CONbits.OCM = 0b110; // Selecciona modo PWM sin protección
     OC2CONbits.OCM = 0b110;
     OC3CONbits.OCM = 0b110; // Selecciona modo PWM sin protección
     OC4CONbits.OCM = 0b110;


     EnableMotor1_Tris=0;
     EnableMotor2_Tris=0;
     //Estamos inicializando las patas que usaremos para que el primer motor avance o retroceda
 //     _TRISB10=0;  //Input 1 a RD2
//     _TRISD3=0;  //Input 2 a RD3
//     _TRISB8=0;  //Input 4 a RB8
//     _TRISB9=0;  //Input 3 a RB9

     /* //Va hacia delante
      _LATD2=1;
     _LATD3=0;

      //Va hacia atras
     _LATD2=0;
     _LATD3=1;
      *
     _LATG14=0;
     _LATG15=1;
      */
     dir=1;
    Motor_A1_dir  = 1;
    Motor_A2_dir  = 0;
    Motor_B1_dir  = 1;
    Motor_B2_dir  = 0;
//     _LATB10=1;
  //   _LATD3=0;

    // _LATB8=1;
    // _LATB9=0;

    // Iniciación del Timer asignado al PWM
#if (Servo_timer == 2)
    OC1CONbits.OCTSEL = 0; // Selección del Timer 2 como timer de referencia
     T2CON = 0; // Reset del Timer
    // T2CONbits.TCS = 0; // Selecciona reloj de CPU (Fosc/2)
    // T2CONbits.TGATE = 0; // Modo Gated deshabilitado
     T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
     //T2CONbits.TCKPS0=0;
     //T2CONbits.TCKPS1=1;
     TMR2 = 0x00; // Borra Timer
     PR2 = PRT_PWM; // Determina periodo
//     PR2 = 8000; // Determina periodo
     _T2IP = 0x01; // Define nivel de prioridad del Timer 2
     _T2IF = 0; // Borra el flag de interrupción Timer 2
     _T2IE = 1; // Habilita interrupción Timer 2
     T2CONbits.TON = 1; // Activa Timer
#elif (Servo_timer == 3)
    OC1CONbits.OCTSEL = 1; // Selección del Timer 2 como timer de referencia
     T3CON = 0; // Reset del Timer
    // T3CONbits.TCS = 0; // Selecciona reloj de CPU (Fosc/2)
    // T3CONbits.TGATE = 0; // Modo Gated deshabilitado
     T3CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
     T3CONbits.TCKPS0=0;
     T3CONbits.TCKPS1=1;
     TMR3 = 0x00; // Borra Timer
     PR3 = 12500; // Determina periodo
     _T3IP = 0x01; // Define nivel de prioridad del Timer 2
     _T3IF = 0; // Borra el flag de interrupción Timer 2
     _T3IE = 1; // Habilita interrupción Timer 2
     T3CONbits.TON = 1; // Activa Timer
#endif
     valorPotenciometro = 512;
}

/* Ejemplo ISR Timer 2*/

unsigned int n_int = 0;
void _ISR _T_Servo_interrupt( void )
{
    Nop();
    Nop();
    Calcula_PWM = 1;
 //   n_int++;
 // if (n_int > 11)
 //   {
    Nop();
    Nop();
//    calcularPID();
//    calcularPWM();
//     n_int = 0;
    Nop();
    Nop();
//    }
/*  
 */
    _T_ServoIF = 0;
}

int outputPIDIzq;
int outputPIDDch;
void calcularPWM(void){
    //calcularPID();
    if(estadoRobot==1){
        
    
        if(outputPID >0) // vamos hacia adelante
            if(dir==1){
                dir=0;
                Integral=0.0;
            }
        else if (outputPID <0) 
           if(dir==0){
                dir=1;
                Integral=0.0;
            }

        outputPIDIzq=outputPID;
        outputPIDDch=outputPID;
        
        //se limita el valor que le daremos al potenciometro para que no pase del minimo o maximo de potencia que podemos darle.
        
  
        if(outputPIDIzq+velExtra_RI>0){
           
            OC2RS=min(abs(outputPIDIzq+velExtra_RI),LIMITE_PWM);
            OC4RS=0;
         
        }else {
            OC2RS=0;
            OC4RS=min(abs(outputPIDIzq+velExtra_RI),LIMITE_PWM);
            
        }
        if(outputPIDDch+velExtra_RD>0){
           
            OC1RS=min(abs(outputPIDDch+velExtra_RD),LIMITE_PWM);
            OC3RS=0;
         
        }else {
            OC1RS=0;
            OC3RS=min(abs(outputPIDDch+velExtra_RD),LIMITE_PWM);
            
        }
        if (outputPIDDch==0 && outputPIDIzq==0){
            OC1RS=0;
            OC3RS=0;
            OC2RS=0;
            OC4RS=0;
        }
    
    }else{
            OC1RS=0;
            OC3RS=0;
            OC2RS=0;
            OC4RS=0;
             //Integral=0.0;
        }
    _T_ServoIF = 0; // Borra flag interrupción
}

void calcularPWM2(void){
    //calcularPID();
    if(estadoRobot==1){



  
        if(outputPID >0){
            if(dir==1){
                dir=0;
                Integral=0.0;
            }
            OC1RS=abs(outputPID)+velExtra_RD;
            OC3RS=0;
            OC2RS=abs(outputPID)+velExtra_RI;
            OC4RS=0;
               
                //OC1RS=outputPID;//abs(anguloMedia)*250;
                //OC2RS=outputPID;//abs(anguloMedia)*250;

        }
        else if (outputPID <0) {
           if(dir==0){
                dir=1;
                Integral=0.0;
            }
            OC1RS=0;
            OC3RS=abs(outputPID)+velExtra_RD;
            OC2RS=0;
            OC4RS=abs(outputPID)+velExtra_RI;
              


                //OC1RS=abs(outputPID);//abs(anguloMedia)*250;
                //OC2RS=abs(outputPID);//abs(anguloMedia)*250;

        }else{
            OC1RS=0;
            OC3RS=0;
            OC2RS=0;
            OC4RS=0;
             //Integral=0.0;
        }
            /*angulo3=angulo2;
            angulo2=angulo1;
            angulo1=angulo;*/
    }else{
            OC1RS=0;
            OC2RS=0;
            OC3RS=0;
            OC4RS=0;

        }

       _T_ServoIF = 0; // Borra flag interrupción
}

