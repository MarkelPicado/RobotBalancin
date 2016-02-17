/*
Proyecto: PIC24H Brazo robotico 
Fichero: IO.h

Grupo: 2    Autor: Markel
 */


void configura_CN();


#define TRled0 _TRISA0
#define TRled1 _TRISA1
#define TRled2 _TRISA2
#define TRled3 _TRISA3
#define TRled4 _TRISA4
#define TRled5 _TRISA5
#define TRled6 _TRISA6

#define LTled0 _LATA0
#define LTled1 _LATA1
#define LTled2 _LATA2
#define LTled3 _LATA3
#define LTled4 _LATA4
#define LTled5 _LATA5
#define LTled6 _LATA6

#define TRpulsador1 _TRISD6
#define TRpulsador2 _TRISD7
#define TRpulsador3 _TRISA7
#define TRpulsador4 _TRISD13

#define VALpulsador1 _RD6
#define VALpulsador2 _RD7
#define VALpulsador3 _RA7
#define VALpulsador4 _RD13