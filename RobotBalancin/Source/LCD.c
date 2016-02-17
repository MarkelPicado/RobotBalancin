/*
Proyecto: PIC24H Brazo robotico 
Fichero: LCD.c

Grupo: 2    Autor: Markel



Descripci?n: Todas las funciones relacionadas con la inicializacion
 del LCD y la actualizacion de este mismo

*/
#include "p24HJ256GP610A.h"
#include "LCD.h"

#define RW _LATD5 // LCD R/W signal
#define RS _LATB15 // LCD RS signal
#define E _LATD4 // LCD E signal

// Control signal pin direction
#define RW_TRIS _TRISD5
#define RS_TRIS _TRISB15
#define E_TRIS _TRISD4

// Data signals and pin direction
#define DATA LATE // Port for LCD data
#define DATAPORT PORTE
#define TRISDATA TRISE // I/O setup for data Port



int estado=0;
unsigned char Ventana_LCD [2][16]; // Reserva espacio en RAM
const char Texto_LCD_1[]= {"S6>CAD|S3-S4>PLY" // 16 caracteres Fila 1
                           "Crono: --/--/-- "}; // 16 caracteres Fila 2




void Inic_LCD(){
    //Inicializar los timers
    PR_lcd = 9375;
    TCKPS1 = 1;
    TCKPS0 = 0;
    TMR_lcd = 0;
    Flag_lcd = 0;
    IE_lcd = 0;
    TCONbitsTON =1;
    PR_Actualizar=60000;    //Luis 80000
    CON_Actualizar=0;
    CONbitsTON_Actualizar=1;
    Prioridad_LCD = 1;
    Flag_Actualizar = 0;
    IE_Actualizar = 0;
    // ========================
//1
    RW=0;
    RS=0;
    E=0;
    TRISE &= 0xFF00;
    RW_TRIS=0;
    RS_TRIS=0;
    E_TRIS=0;

   while(Flag_lcd==0){}
   Flag_lcd = 0;
   lcd_cmd(0x38);
//2
   while(Flag_lcd==0){}
   Flag_lcd = 0;
   lcd_cmd(0x38);
   PR_lcd=3125;
  //3
   while(Flag_lcd==0){}
   Flag_lcd = 0;
   lcd_cmd(0x38);
   TCKPS1=0;
   TCKPS0=0;
   PR_lcd=1600;
//4
   while(Flag_lcd==0){}
   Flag_lcd = 0;
   lcd_cmd(0x38);
 //10
   while(Flag_lcd==0){}
   Flag_lcd = 0;
   lcd_cmd(0xC);
  //12
   while(Flag_lcd==0){}
   Flag_lcd = 0;
   lcd_cmd(0x06);
   //
   while(Flag_lcd==0){}
   Flag_lcd = 0;
   lcd_cmd(0x80);
   //
   while(Flag_lcd==0){}
   Flag_lcd = 0;
   Nop();
   Nop();
   lcd_cmd(0x02);
   Nop();
   Nop();

   TMR_Actualizar=0;
   Flag_Actualizar = 0;
   IE_Actualizar=1;
}
void Copia_FLASH_RAM(char Texto_LCD[])
{
      int i,j;
      for (j=0; j<32;j++)
      {
        Ventana_LCD[0][j] = Texto_LCD[j];
        Nop();
    }
}
int indice=0;

void actualizar(){
      switch (estado){
          case 0: //Enviamos el comando para ir a la primera posicion del LCD
              lcd_cmd(0x80);
              estado++;
              break;
          case 1: //Escribimos los 16 primero caracteres
              lcd_data(Ventana_LCD[0][indice]);
              indice++;
              if (indice>15) estado++;
              break;
          case 2: //Enciamos el comando para mandar el cursor al principio de la segundaa linea
              lcd_cmd(0xC0);
              estado++;
              break;
          case 3: //Escribimos los siguientes 16 caracteres en la segunda linea
              lcd_data(Ventana_LCD[0][indice]);
              indice++;
              if (indice>31){
                    estado=0;   //Volvemos al estado inicial
                    indice=0;   //restauramos el indice
              }
              break;
      }
}

//========= Envío de COMANDO =========
void lcd_cmd( char cmd ) // subrutina para comandos
{
//     TRISD &= 0xFF00; // asegura RD0 - RD7 como salidas
     DATA &= 0xFF00; // prepara RD0 - RD7
     DATA |= cmd; // command del lcd
     RW = 0; // Orden de escritura RW -> 0
     RS = 0; // Selecciona registro ?0?
     E = 1; // Activa la señal E
     Nop(); // Tiempo de espera requerido
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     E = 0; // Final de escritura
}

//======= Envio de DATO ===============
void lcd_data( char data ) // subroutina para datos
{
 //    TRISD &= 0xFF00; // asegura RD0 - RD7 como salidas
     RW = 0; // Orden de escritura RW -> 0
     RS = 1; // Selecciona registro ?1?
     DATA &= 0xFF00; // prepara RD0 - RD7
     DATA |= data; // dato del lcd
     E = 1; // Activa la señal E
     Nop(); // Tiempo de espera requerido
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     Nop();
     E = 0; // Final de escritura
    // RS = 0; // Selecciona registro ?0?
 }


int cont4=0;
void _ISR _TActualizarInterrupt( void)
{
    if (cont4==20){
    actualizar();
    cont4=0;
    }else cont4++;
    Flag_Actualizar = 0;
}
