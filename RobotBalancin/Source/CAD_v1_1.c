/*
Proyecto: PIC24H Brazo Robotico 
Fichero: CAD_v1_1.c
Luis 29-5-15

Grupo: 2    Autor: Markel Picado

Descripci?n: Todas las funciones relacionadas con las señales sigitales
 del potenciometro y el sensor de temperatura y la configuracion del modulo
 CAD, asi como dos funciones [toAN() y toDI()] relacionadas con el estado
 global del programa, con una te muestra y activa las interrupciones correspondientes
 al cronometro y con la otra las correspondientes a las señales analogicas(potenciometro
 y sensor de temperatura)
 
 IMPORTANTE: Con la interrupcion del CAD aqui definida se OBTIENEN los valores del joistic 
 para darle valor a los servos del brazo robotico, aparte de mostrarlos por la pantalla LCD.

*/
#include "p24HJ256GP610A.h"

#include "PWM.h"
#include "CAD.h"

int j;
unsigned char Vector[4];
int est=1;
unsigned int ADCValue;
unsigned int valorPotenciometro;

void Inic_CAD(){
    ////////////////////////INICCAD/////////////////////////////
    ///////////////////////////////////////////////////////////
    //_TRISB5=1;
 //   AD1PCFGL = 0xF8CF; // Todos los PORTB = Digital excepto RB8,RB9,RB10,RB5 y RB4= analog.
    AD1PCFGL = 0xFFF;
    AD1PCFGH = 0xFFF;
    _PCFG4 = 0;
   _PCFG5 = 0;
    AD1CON1 = 0x00E0; // SSRC bit = 111 auto-convert
    AD1CHS0= 0x0005; // RB5/AN5 como entrada de CH0
    AD1CSSL = 0;
    AD1CON3 = 0x1F3F; // Tiempo de muestreo = 63Tad, Tad interno = 2 Tcy
    AD1CON2 = 0;
    AD1CON1bits.ADON = 1; // Encendido del módulo
    ///////////////////////////////////////////////////////////
    AD1CON1bits.SAMP = 1; // Comienza el muestreo y al de 31Tad empieza la conversión

//Preparamos el TIMER para la interrupcion del CAD para que lea los datos analogicos.
    PR_CAD=40000; //Hacemos que interrumpa cada milisegundo
    CON_CAD=0;
    CONbitsTON_CAD=1;
    Prioridad_CAD = 0x01;
    Flag_CAD = 0; // reg. IFS0 bit 7 (T2IF)
    IE_CAD = 1; // reg. IEC0 bit 7 (T2IE)
}


/*
 * Cada milisegundo monitorizamos los valores(accedemos a esta interrupcion)
 * por lo que el tiempo de carga del condensador con la interrupcion la
 * solucionamos, dependiendo en el estado que nos encontremos
 * leeremos los datos o de la temperatura o el del potenciometro
 * y cambiamos de estado asi vamos alternando las lecturas.
 * En cada estado primero se lee el dato del buffer del valor analogico anterior
 * despues dependiendo el menu en el que nos encontremos mostramos ese valor o no
 * cambiamos de estado y ponemos como entrada del canal Analogico CH0 la entrada
 * del siguiente valor analogico que queremos obtener para asi la siguiente vez
 * que vuelva a interrumpir leeremos el dato porque ya abra tenido tiempo de
 * hacer la conversion.
 */
void _ISR _TCADInterrupt( void)
{
            AD1CHS0= _chPotenciometro; // RB5/AN5 como entrada de CH0
            ADCValue = ADC1BUF0; //leemos el valor del bufer (valor del condensador)
            valorPotenciometro=ADCValue;

    Flag_CAD = 0;
    AD1CON1bits.SAMP = 1; // Comienza el muestreo 
}
