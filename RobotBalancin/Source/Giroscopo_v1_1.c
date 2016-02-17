//Control del Magnetometro HMCL5883L
// Giroscopo_v1_1.c
//Luis 29-5-15

extern int errorFlag;
//Variables externas
extern signed short giroX, giroY, giroZ;
extern float vec_giro[3];

extern unsigned char disp;
extern unsigned char I2C_ocupado;
extern unsigned char datos[3][6];

extern char giroText[64];

//texto
extern unsigned char c0,c1,c2,c3,c4,c5;

//Inclusiones
#include "i2c_Func_DSE.h"
#include "p24HJ256GP610A.h"
#include <time.h>

//Definiciones
#define PI 3.14159265358979
#define CONV_GIRO1 (1.0/14.375)
#define CONV_GIRO2 (0.0695652173913)
#define CONV_ACEL (1.0/256.0)
#define RAD2DEG (180.0/PI)
#define DEG2RAD (PI/180.0)

//Definiciones
#define DirGiro 0x68
#define DirGiroW 0xD0
#define DirGiroR 0xD1

//Registros de Configuración
#define Reg_SMPLRT_DIV 0x15
#define Reg_DLPF_FS 0x16
#define Reg_PWR_MGM 0x3E

//Registros de Datos
#define Reg_TEMP_H 0x1B
#define Reg_TEMP_L 0x1C
#define Reg_XOUT_H 0x1D
#define Reg_XOUT_L 0x1E
#define Reg_YOUT_H 0x1F
#define Reg_YOUT_L 0x20
#define Reg_ZOUT_H 0x21
#define Reg_ZOUT_L 0x22

//array auxiliar
unsigned char aux_data2[6] = {0,0,0,0,0,0};

//Mensajes de TEXTO
const char TEXTOG1[] = {"Deje la placa quieta y pulse \"N\" o \"n\"\r\n"};

//Variables calibracion
extern unsigned char estado_calibracion;

extern double GIRO_OFFSET_X;
extern double GIRO_OFFSET_Y;
extern double GIRO_OFFSET_Z;
float angulogiro=0.0;

time_t  t1;
time_t  t2;
int tiempo;
//Funciones
//Inicializar el Giroscopo
void Inic_Giro(void)
{
    errorFlag=8;
    LDByteWriteI2C_1(DirGiroW, Reg_PWR_MGM, 0x80); //Hardware Reset
    //Delay(Delay_5mS_Cnt);

    LDByteWriteI2C_1(DirGiroW, Reg_SMPLRT_DIV, 0x09);   //Ajustamos la velocidad a 100Hz
    //Delay(Delay_5mS_Cnt);

    LDByteWriteI2C_1(DirGiroW, Reg_DLPF_FS, 0x1D);   //Seleccionamos el modo de medición, filtro pasaBajo 10Hz
    //Delay(Delay_5mS_Cnt);

    LDByteWriteI2C_1(DirGiroW, Reg_PWR_MGM, 0x01);   //Seleccionar como reloj, el gyroX
    //Delay(Delay_5mS_Cnt);
    t1=clock();
    errorFlag=9;
}

void calibrar_giro()
{
    errorFlag=10;
    estado_calibracion = 0;
    int i;
    double vec_offset[3]={0.0,0.0,0.0};

    //Imprimir: Deja la placa quieta y pulsa "N" o "n"
    /*i=0;
    putRS232_2('\x1B');
    putRS232_2('[');
    putRS232_2('2');
    putRS232_2('J');
    while(TEXTOG1[i]!='\0'){
        putRS232_2(TEXTOG1[i]);
        i++;
    }*/

    //Esperar pulsacion
    //while(estado_calibracion==0);
    
    //Recolectar valores offset
    vec_offset[0]=0.0;
    errorFlag=11;
    for(i=0;i<5000;i++)
    {
        LDByteReadI2C_1(DirGiroW, Reg_XOUT_H, aux_data2, 6);
        vec_giro[1] = (aux_data2[1] + aux_data2[0]*256)*CONV_GIRO1*DEG2RAD;
        vec_giro[0] = -(aux_data2[3] + aux_data2[2]*256)*CONV_GIRO1;
        vec_giro[2] = (aux_data2[5] + aux_data2[4]*256)*CONV_GIRO1*DEG2RAD;
        vec_offset[0]+=vec_giro[0];
        //sumar_vectores(vec_offset,vec_offset,vec_giro);
    }
    errorFlag=12;
    //Sacar la media
    vec_offset[0]=vec_offset[0]/5000.0;
    vec_offset[1]=vec_offset[1]/5000.0;
    vec_offset[2]=vec_offset[2]/5000.0;
    vec_offset[0]+=0.20646405;

    errorFlag=13;

    GIRO_OFFSET_X=vec_offset[0];
    GIRO_OFFSET_Y=vec_offset[1];
    GIRO_OFFSET_Z=vec_offset[2];

    errorFlag=14;
}


//Leer valores giroscopo
void Leer_Giro(/*signed short x, signed short y, signed short z*/)
{
    //t2=clock();
    LDByteReadI2C_1(DirGiroW, Reg_XOUT_H, aux_data2, 6);

    vec_giro[1] = (aux_data2[1] + aux_data2[0]*256)*CONV_GIRO1*DEG2RAD;
    vec_giro[0] = (-(aux_data2[3] + aux_data2[2]*256)*CONV_GIRO1)-GIRO_OFFSET_X;
    vec_giro[2] = (aux_data2[5] + aux_data2[4]*256)*CONV_GIRO1*DEG2RAD;

//    vec_giro[1] = (datos[2][1] + datos[2][0]*256)*CONV_GIRO1*DEG2RAD;
//    vec_giro[0] = -(datos[2][3] + datos[2][2]*256)*CONV_GIRO1*DEG2RAD;
//    vec_giro[2] = (datos[2][5] + datos[2][4]*256)*CONV_GIRO1*DEG2RAD;

  //  tiempo=(t2-t1);
    angulogiro=angulogiro+0.01*vec_giro[0];
  // angulogiro=angulogiro+(int)((sec2-sec1)/1000)*vec_giro[0];
  //  t1=clock();
}

//Leer valores por interrupciones
void Leer_Giro_Int()
{
    //Traducir valores anteriores
    /*giroX = datos[2][1] + datos[2][0]*256;
    giroY = datos[2][3] + datos[2][2]*256;
    giroZ = datos[2][5] + datos[2][4]*256;
    */
    //Comprobar si el I2C está libre
    if(!I2C_ocupado){
        disp=1;     //Seleccionar Giroscopo
        I2C_ocupado=1;
        _MI2C1IF=0;             //Borrar flag int.
        _MI2C1IE=1;             //Habilitar interrupciones I2C
        I2C1CONbits.SEN = 1;    //Envíar Start
    }
}

//Imprimir valores giroscopo
void print_Giro()
{
    //Print X
    putRS232_2('G');
    putRS232_2('X');
    putRS232_2(':');

    //signed16_ASCII((signed short)(vec_giro[0]*14.375*RAD2DEG));
    signed16_ASCII(giroX);
    putRS232_2('\t');
    putRS232_2(c0);
    putRS232_2(c1);
    putRS232_2(c2);
    putRS232_2(c3);
    putRS232_2(c4);
    putRS232_2(c5);

    //Hex_ASCII((signed short)(vec_giro[0]*14.375*RAD2DEG));
    Hex_ASCII(giroX);
    putRS232_2('\t');
    putRS232_2(c4);
    putRS232_2(c3);
    putRS232_2(c2);
    putRS232_2(c1);

    putRS232_2('\r');
    putRS232_2('\n');

    //Print Y
    putRS232_2('G');
    putRS232_2('Y');
    putRS232_2(':');

    //signed16_ASCII((signed short)(vec_giro[1]*14.375*RAD2DEG));
    signed16_ASCII(giroY);
    putRS232_2('\t');
    putRS232_2(c0);
    putRS232_2(c1);
    putRS232_2(c2);
    putRS232_2(c3);
    putRS232_2(c4);
    putRS232_2(c5);

//    Hex_ASCII((signed short)(vec_giro[1]*14.375*RAD2DEG));
    Hex_ASCII(giroY);
    putRS232_2('\t');
    putRS232_2(c4);
    putRS232_2(c3);
    putRS232_2(c2);
    putRS232_2(c1);

    putRS232_2('\r');
    putRS232_2('\n');

    //Print Z
    putRS232_2('G');
    putRS232_2('Z');
    putRS232_2(':');

//    signed16_ASCII((signed short)(vec_giro[2]*14.375*RAD2DEG));
    signed16_ASCII(giroZ);
    putRS232_2('\t');
    putRS232_2(c0);
    putRS232_2(c1);
    putRS232_2(c2);
    putRS232_2(c3);
    putRS232_2(c4);
    putRS232_2(c5);

//    Hex_ASCII((signed short)(vec_giro[2]*14.375*RAD2DEG));
    Hex_ASCII(giroZ);
    putRS232_2('\t');
    putRS232_2(c4);
    putRS232_2(c3);
    putRS232_2(c2);
    putRS232_2(c1);

    putRS232_2('\r');
    putRS232_2('\n');
}