//Control del Acelerometro ADXL345
// Alelerómetro_v1_1.c
//Luis 29-5-15


//Variables externas
extern int errorFlag;

extern signed short acelX, acelY, acelZ;
extern double vec_acel[3];

extern unsigned char disp;
extern float angulogiro;
extern unsigned char I2C_ocupado;
extern unsigned char datos[3][6];
unsigned char Texto_2[];
extern char acelText[64];
extern int outputPID;

//Inclusiones
#include "i2c_Func_DSE.h"
#include "p24HJ256GP610A.h"
#include <math.h>

//Definiciones
#define CONV_ACEL (1.0/256.0)   // ???

#define DirAcel 0x53    // Dir I2C
#define DirAcelW 0xA6
#define DirAcelR 0xA7

//Registros de Configuración
#define Reg_BW_RATE 0x2C
#define Reg_POWER_CTL 0x2D
#define Reg_DATA_FORMAT 0x31

//Registros de Datos
#define Reg_DATAX0 0x32
#define Reg_DATAX1 0x33
#define Reg_DATAY0 0x34
#define Reg_DATAY1 0x35
#define Reg_DATAZ0 0x36
#define Reg_DATAZ1 0x37

#define PI 3.14159265358979
#define CONV_GIRO1 (1.0/14.375)   // ???
#define CONV_GIRO2 (0.0695652173913)   // ???
#define CONV_ACEL (1.0/256.0)   // ???
#define RAD2DEG (180.0/PI)   //
#define DEG2RAD (PI/180.0)   //

//array auxiliar
unsigned char aux_data[6] = {0,0,0,0,0,0};   // ???

float angulo=0.0;   // ???
//TEXTOA
extern unsigned char c0,c1,c2,c3,c4,c5;
extern vec_giro;

//Mensajes de TEXTOA
const char TEXTOA1[] = {"Apunte el eje X hacia la tierra y presione \"N\" o \"n\"\r\n"};
const char TEXTOA2[] = {"Incline ligeramente la placa hacia todos los lados y pulsar \"N\" o \"n\"\r\n"};
const char TEXTOA3[] = {"Apunte el eje X hacia el cielo y presione \"N\" o \"n\"\r\n"};
const char TEXTOA4[] = {"Apunte el eje Y hacia la tierra y presione \"N\" o \"n\"\r\n"};
const char TEXTOA5[] = {"Apunte el eje Y hacia el cielo y presione \"N\" o \"n\"\r\n"};
const char TEXTOA6[] = {"Apunte el eje Z hacia la tierra y presione \"N\" o \"n\"\r\n"};
const char TEXTOA7[] = {"Apunte el eje Z hacia el cielo y presione \"N\" o \"n\"\r\n"};

//Variables calibracion
extern unsigned char estado_calibracion;

extern double ACEL_X_MIN;
extern double ACEL_X_MAX;
extern double ACEL_Y_MIN;
extern double ACEL_Y_MAX;
extern double ACEL_Z_MIN;
extern double ACEL_Z_MAX;
extern double ACEL_OFFSET_X;
extern double ACEL_OFFSET_Y;
extern double ACEL_OFFSET_Z;

extern float anguloFiltro;
float errorAngulo=9.079696;
extern float Derivative;
extern float Integral;
extern float Ki;
extern float Kd;
extern float Kp;
extern unsigned int valorPotenciometro;
//Funciones
//Inicializar el Acelerometro
void Inic_Acel(void)
{
    LDByteWriteI2C_1(DirAcelW, Reg_BW_RATE, 0x09);   //Ajustamos la velocidad a 50Hz
    //Delay(Delay_5mS_Cnt);

    LDByteWriteI2C_1(DirAcelW, Reg_POWER_CTL, 0x08);   //Seleccionamos el modo de medición
    //Delay(Delay_5mS_Cnt);

    LDByteWriteI2C_1(DirAcelW, Reg_DATA_FORMAT, 0x08);   //Seleccionamos el modo FULL-RES
    //Delay(Delay_5mS_Cnt);
    errorFlag=3;   // ???
}

//Leer valores acelerometro
void Leer_Acel(/*unsigned int x, unsigned int * y, unsigned int * z*/)
{
    errorFlag=4;   // ???
    LDByteReadI2C_1(DirAcelW, Reg_DATAX0, aux_data, 6);

    acelX = aux_data[0] + aux_data[1]*256;
    acelY = aux_data[2] + aux_data[3]*256;
    acelZ = aux_data[4] + aux_data[5]*256;

    vec_acel[1] = -(aux_data[0] + aux_data[1]*256)*CONV_ACEL;
    vec_acel[0] = (aux_data[2] + aux_data[3]*256)*CONV_ACEL;
    vec_acel[2] = -(aux_data[4] + aux_data[5]*256)*CONV_ACEL;
    angulo=atan2(acelX,acelZ) * 180.0 / 3.14159265;
    if(angulo>0)angulo=angulo-errorAngulo;
    //angulo=angulo-errorAngulo;
    angulo=angulo*1.5;
    errorFlag=5;
}


void calibrar_acel()
{
    errorFlag=10;
    estado_calibracion = 0;
    int i;
    double vec_offset[3]={0.0,0.0,0.0};

    //Recolectar valores offset
    vec_offset[0]=0.0;
    errorFlag=11;
    for(i=0;i<5000;i++)
    {
        LDByteReadI2C_1(DirAcelW, Reg_DATAX0, aux_data, 6);
        vec_acel[1] = -(aux_data[0] + aux_data[1]*256)*CONV_ACEL;
        
        vec_offset[0]+=vec_acel[1];
        //sumar_vectores(vec_offset,vec_offset,vec_giro);
    }
    errorFlag=12;
    //Sacar la media
    vec_offset[0]=vec_offset[0]/5000.0;
    //vec_offset[0]+=0.20646405;

    errorFlag=13;

    ACEL_OFFSET_X=vec_offset[0];

    errorFlag=14;
}

//====================================================
//Leer valores por interrupciones
void Leer_Acel_Int()
{Leer_Acel();
    //Traducir valores anteriores
    acelX = datos[0][0] + datos[0][1]*256;
    acelY = datos[0][2] + datos[0][3]*256;
    acelZ = datos[0][4] + datos[0][5]*256;
    //Comprobar si el I2C está libre
 //   IdleI2C_1();    //Luis
    if(!I2C_ocupado){
        disp=0;     //Seleccionar Acelerometro
        I2C_ocupado=1;
        _MI2C1IF=0;             //Borrar flag int.
        _MI2C1IE=1;             //Habilitar interrupciones I2C
        //I2C1CONbits.SEN = 1;    //Envíar Start
    }
}

#define Motor_A1_dir _LATB10
#define Motor_B1_dir _LATB11
#define Motor_A2_dir _LATB12
#define Motor_B2_dir _LATB13

//Imprimir valores acelerometro
void print_PID()
{   
    errorFlag=6;
    char Texto_2[]= {"+++++M++++++++++" // 16 caracteres Fila 1
                     "P++++D+++++I++++"}; // 16 caracteres Fila 2
  
   /* signed12_ASCII(acelX);
  
   
    Texto_2[9]=c0;
    Texto_2[10]=c1;
    Texto_2[11]=c2;
    Texto_2[12]=c3;
    Texto_2[13]=c4;*/

    
    signed12_ASCII((int)anguloFiltro);
    Texto_2[0]=c0;
    Texto_2[1]=c1;
    Texto_2[2]=c2;
    Texto_2[3]=c3;
    Texto_2[4]=c4;

    //if(angulo==0)angulogiro=0;
    signed12_ASCII((int)(outputPID));
    Texto_2[6]=c0;
    Texto_2[7]=c1;
    Texto_2[8]=c2;
    Texto_2[9]=c3;
    Texto_2[10]=c4;


    if(valorPotenciometro<256){
             Texto_2[12]='P';
             Texto_2[13]='+';
             Texto_2[14]='-';
             Texto_2[15]='1';}
    else if (valorPotenciometro<512){
             Texto_2[12]='P';
             Texto_2[13]='-';
             Texto_2[14]='1';
             Texto_2[15]='0';}
    else if (valorPotenciometro<768){
             Texto_2[12]='P';
             Texto_2[13]='+';
             Texto_2[14]='+';
             Texto_2[15]='1';}
    else if (valorPotenciometro<1024){
             Texto_2[12]='P';
             Texto_2[13]='+';
             Texto_2[14]='1';
             Texto_2[15]='0';}


    signed12_ASCII((int)Kp);

    //Texto_2[16]=c0;
    Texto_2[16]=c1;
    Texto_2[17]=c2;
    Texto_2[18]=c3;
    Texto_2[19]=c4;

    signed12_ASCII((int)Kd);
    //signed16_ASCII((signed short)angulogiro);
    //Texto_2[22]=c0;
    Texto_2[22]=c1;
    Texto_2[23]=c2;
    Texto_2[24]=c3;
    Texto_2[25]=c4;
 

    signed12_ASCII((int)Ki);

    //Texto_2[28]=c0;
    Texto_2[28]=c1;
    Texto_2[29]=c2;
    Texto_2[30]=c3;
    Texto_2[31]=c4;
    /*signed12_ASCII(acelZ);

    Texto_2[25]=c0;
    Texto_2[26]=c1;
    Texto_2[27]=c2;
    Texto_2[28]=c3;
    Texto_2[29]=c4;
    */
    Copia_FLASH_RAM(Texto_2);
    Copia_FLASH_RAM_RS232(Texto_2);
    errorFlag=7;
}


void print_Angulo()
{
    errorFlag=6;
    char Texto_2[]= {"+++++M++++++++++" // 16 caracteres Fila 1
                     "A++++++G++++++++"}; // 16 caracteres Fila 2

   /* signed12_ASCII(acelX);


    Texto_2[9]=c0;
    Texto_2[10]=c1;
    Texto_2[11]=c2;
    Texto_2[12]=c3;
    Texto_2[13]=c4;*/


    signed12_ASCII((int)anguloFiltro);
    Texto_2[0]=c0;
    Texto_2[1]=c1;
    Texto_2[2]=c2;
    Texto_2[3]=c3;
    Texto_2[4]=c4;

    //if(angulo==0)angulogiro=0;
    signed12_ASCII((int)(outputPID));
    Texto_2[6]=c0;
    Texto_2[7]=c1;
    Texto_2[8]=c2;
    Texto_2[9]=c3;
    Texto_2[10]=c4;


    if(valorPotenciometro<256){
             Texto_2[12]='P';
             Texto_2[13]='+';
             Texto_2[14]='-';
             Texto_2[15]='1';}
    else if (valorPotenciometro<512){
             Texto_2[12]='P';
             Texto_2[13]='-';
             Texto_2[14]='1';
             Texto_2[15]='0';}
    else if (valorPotenciometro<768){
             Texto_2[12]='P';
             Texto_2[13]='+';
             Texto_2[14]='+';
             Texto_2[15]='1';}
    else if (valorPotenciometro<1024){
             Texto_2[12]='P';
             Texto_2[13]='+';
             Texto_2[14]='1';
             Texto_2[15]='0';}


    signed12_ASCII((int)angulo);

    Texto_2[17]=c0;
    Texto_2[18]=c1;
    Texto_2[19]=c2;
    Texto_2[20]=c3;
    Texto_2[21]=c4;

    signed12_ASCII((int)angulogiro);
    Texto_2[24]=c0;
    Texto_2[25]=c1;
    Texto_2[26]=c2;
    Texto_2[27]=c3;
    Texto_2[28]=c4;



    Copia_FLASH_RAM(Texto_2);
    Copia_FLASH_RAM_RS232(Texto_2);
    errorFlag=7;
}