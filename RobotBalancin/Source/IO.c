/*
Proyecto: PIC24H Brazo robotico 
Fichero: IO.c





Descripci?n: Todas las funciones relacionadas con los pulsadores los leds
 y las interrupciones. En este modulo tambien se leen algunos de los pulsadores
 del joistick para darle valores a la cabeza(S3) y a la pinza(S4) del brazo robotico 

*/
#include "p24HJ256GP610A.h"
#include "IO.h"


extern unsigned int cabeza;
extern unsigned int pinza;
int estadoRobot=0;
extern float  angulo;
extern float angulogiro;
extern float errorAngulo;
extern float anguloFiltro;
extern float Integral;

/*La variable modo la utilizamos para diferenciar los dos modos
 que dispone nuestro programa, en el modo uno se mostrara el cronometro
 y nos dejara jugar con los pulsadores y los leds*/

/*Ponemos los valores de todos los LEDS a cero, esto se hace cuando entramos
 en el modo _____ del programa, donde se muestra solo el valor del potenciometro
 y el del sensor de temperatura*/


void configura_CN(void)
{
CNEN1bits.CN15IE = 1;   //Habilitar la interrupcion pulsador S3 = RD6
CNEN2bits.CN16IE = 1;   //Habilitar la interrupcion pulsador S6 = RD7
CNEN2bits.CN19IE = 1;   //Habilitar la interrupcion pulsador S4 = RD13
CNEN2bits.CN23IE = 1;   //Habilitar la interrupcion pulsador S4 = RD13

IEC1bits.CNIE = 1; // Habilita interrupciones CN
IFS1bits.CNIF = 0; // Borra los flags de interrupciones

    //TRISAbits.TRISA0 = 0;	//  '0' -> Salida (Output) / '1' -> Entrada (Input)
 
    TRpulsador1= 1;    // Pata de Entrada (In= 1)
    TRpulsador2= 1;    // Pata de Entrada (In= 1)
    TRpulsador3=1;
} // Fin configura_CN


unsigned int Pulsado_Propor = 0;
unsigned int Pulsado_Diferen = 0;
unsigned int Pulsado_Integral = 0;

/*Dependiendo cual de los 3 botones se pulse hace una cosa u otra
 si es RD6 aumenta el estado en el programa de los leds y si es el RD13
 resta un estado
 Para el boton RD7 (que se utiliza para cambiar de estado y cargar un programa
 u otro) dependiendo el modo cargara un programa y actualizara el modo en el que
 se encuentra*/
void _ISR _CNInterrupt(void)
{
    if (VALpulsador4 == 0)
    {
                //errorAngulo=anguloFiltro;
                Integral=0.0;
                estadoRobot=!estadoRobot;
               // angulo=0;
                angulogiro=0;
              //  anguloFiltro=0;
                Pulsado_Propor = 0;
                Pulsado_Diferen = 0;
                Pulsado_Integral = 0;
    }
    else
        if (VALpulsador1 == 0)
            {
              //  angulo=0;
               // angulogiro=0;
              //  anguloFiltro=0;
                Pulsado_Propor = 1;
                Pulsado_Diferen = 0;
                Pulsado_Integral = 0;
 //               estadoRobot=0;
             
    }
    else
        if (VALpulsador2 == 0)
            {
              //   angulo=0;
              //  angulogiro=0;
              //  anguloFiltro=0;
                Pulsado_Diferen = 1;
                Pulsado_Propor = 0;
                Pulsado_Integral = 0;
//                estadoRobot=0;
        

    }
    else
        if (VALpulsador3 == 0)
            {
            // angulo=0;
          //      angulogiro=0;
            //    anguloFiltro=0;
              Pulsado_Integral = 1;
              Pulsado_Propor = 0;
              Pulsado_Diferen = 0;

            }

    _CNIF = 0; // Borra flag interrupción CN
}