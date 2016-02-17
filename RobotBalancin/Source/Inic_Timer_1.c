//Estructura de inicialización del TIMER1
//#include "p24HJ256GP610.h"
#include "p24HJ256GP610A.h"

//Variables externas
////Para el Cronometro
extern unsigned char mSeg;
extern unsigned char dec, seg, min, parado;
////Para medir la pulsacion
extern unsigned char cont_mSeg, cont_dec, cont_seg, cont_min;
extern unsigned char contar_puls;

extern unsigned int aux;

void Inic_Timer_1(void) //Función de inicializacion del TIMER1
{
	TMR1 = 0;			//Borra el timer	
	PR1 = (40000-1);	//define el periodo, en este caso 1ms
	
	T1CON = 0b1000000000000000;	//habilitado, prescaler 1:xxxx, reloj interno (en este caso solo habilitarlo)

//	_TGATE = ??;	//Deshabilita Gate
//	_TCKPS = ??;	//Selecciona valor prescaler
//	_TCS = ??;		//Reloj Interno
//	_TON = ??;		//

	//Interrupción
	_T1IF = 0;	//Borra el flag
	_T1IE = 0;	//Deshabilitado, hasta que se habilite en el main
	_T1IP = 1;	//Prioridad

}		//Fin de Inic_Timer_1

//Rutina de interupcion del Timer 1
void _ISR _T1Interrupt( void)
{
	mSeg++;		//Incrementar variable mSeg

	//Función de cronometro
	if(!parado)		//Si el cronometro no esta parado
	{
		if(mSeg>99)	//Si se han contado mas de 99 ms
		{		
			//_LATA0=!_LATA0;	//Conmutar Led D3 (decimas)
			mSeg=0;		//Reiniciar milisegundos
			dec++;		//Incrementar decimas de segundo
		}
		if(dec>9)	//Si se han contado mas de 9 decimas
		{		
			//_LATA1=!_LATA1;	//Conmutar Led D4 (segundos)
			dec=0;		//Reiniciar decimas
			seg++;		//Incrementar segundos
		}
		if(seg>59)	//Si se han contado mas de 59 segundos
		{
			//_LATA2=!_LATA2;	//Conmutar Led D5 (minutos)
			seg=0;		//Reiniciar segundos
			min++;		//Incrementar minutos
		}
		if(min>59)	//Si se han contado mas de 59 minutos
		{		
			//_LATA3=!_LATA3;	//Conmutar Led D6 (horas)
			min=0;		//reiniciar minutos
		}
	}

	_T1IF = 0;	//Poner el flag a 0 de nuevo
}