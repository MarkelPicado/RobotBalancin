//Estructura de inicialización del TIMER7

//Este Timer lanza las lecturas del Giroscopo

#include "p24hj256gp610A.h"
#include <time.h>
unsigned char estado_int;
extern unsigned char disp;
extern unsigned char leerMagne;
extern clock_t t1;
extern double angulogiro;
extern float angulo;
extern int errorFlag;
extern float vec_giro[3];

unsigned char Calculo_Kalman = 0;
unsigned char Impre_Acel = 0;

void Inic_Timer_7(void) //Función de inicializacion del TIMER7
{
	// Inicializar y habilitar TIMER7
	T7CONbits.TON = 0; // Disable Timer
	T7CONbits.TCS = 0; // Select internal instruction cycle clock
	T7CONbits.TGATE = 0; // Disable Gated Timer mode
	T7CONbits.TCKPS = 0b10; // Selecionar Prescaler: 1:64
	TMR7 = 0x00; // Clear timer register
	PR7 = 3125; // Periodo Giroscopo: 10ms = 6250
//	_T7IP = 0x01; // Set Timer 7 Interrupt Priority Level
	_T7IP = 0x05; // Set Timer 7 Interrupt Priority Level
	_T7IF = 0; // Clear Timer 7 Interrupt Flag
	_T7IE = 1; // Enable Timer 7 interrupt
	T7CONbits.TON = 1; // Start Timer

        estado_int=0;
        t1=clock();
        errorFlag=1;
}		//Fin de Inic_Timer_7
int contCali=100;

//===========================================================
void _ISR _T7Interrupt (void)   // Prioridad 1
{
    I2C1CONbits.SEN = 1;
    if (estado_int==0){
         Leer_Acel();
         estado_int=1;
    }
    //disp=1;
    else{
        Leer_Giro();
        estado_int=0;
//        filtroKalman(angulo,vec_giro[0]);
//        print_Acel();
        filtroKalman(angulo,vec_giro[0]);
        calcularPID();
        calcularPWM();
        Calculo_Kalman = 1;
        Impre_Acel = 1;
        
    }
    //disp=0; 
    errorFlag=2;
    _T7IF = 0;
}   // FIN _T7Interrupt


/*void _ISR _T7Interrupt (void)
{
    I2C1CONbits.SEN = 1;


        switch(estado_int)
        {
            case 0: Leer_Acel();
                    estado_int=1;
                    disp=1;
                    print_Acel();
                    break;
            case 1: Leer_Giro();
                    estado_int=0;
                    disp=0;
                    break;
            default: break;
        }

    _T7IF = 0;
}*/