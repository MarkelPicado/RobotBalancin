/*
 main_banancin_v1_1
 * //Luis 29-5-15
 * T7 prioridad 5; lee acelerómetro y giróscopo

 * Prioridad CAD = 1 (T8)
 *
 * LCD T5
 *
 * PDI T6
 * 
*/


#include "p24HJ256GP610A.h"
#include <stdio.h>
#include <string.h>
#include "main.h"

//#include "DCM.c"
//#include "controladorVuelo.c"

//** Solo una referencia de FOSSCEL, FOSC, FWDT debe aparecer en un proyecto
//** al inicio de un fichero fuente C, fuera de ninguna funcion

/*_FOSCSEL (FNOSC_PRIPLL);		// Primary oscillator (XT, HS, EC) w/ PPL
_FOSC (FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);// Clock switching and clock monitor: Both
												// disable, OSC2 is clock O/P,XT oscillator
_FWDT (FWDTEN_OFF);				// Watchdog Timer:Disabled
*/

void Inic_Oscilador(void);		//Incluir Oscilador.c a 'Source Files'

void Inic_Timer_1(void);
void InitI2C_1(void);
void filtroKalman(float Accel, float Gyro);
void calcularPID();

unsigned int resul=0;
//Variables globales para el cronometro
unsigned char mSeg;
unsigned char dec, seg, min, parado;

//Variables del acelerometro
signed short acelX, acelY, acelZ;
double vec_acel[3];
//Variables del magnetometro
signed short magneX, magneY, magneZ;
double desvMag;
double desvMagX;
double desvMagY;

//Variables del giroscopo
signed short giroX, giroY, giroZ;
float vec_giro[3];

//Strings de datos para UART
char acelText[64];
char magneText[64];
char giroText[64];

//Semaforos
unsigned char sem_leec;

//Definir Ventana del LCD en RAM

//Constantes del texto
const char TEXTO1[] = "Cronometro LCD  ";
const char TEXTO2[] = "Presione S3     ";

//E) Definir un texto en FLASH
const char TEXTO_CRON[] = {"Cronometro------"
			  "---------00:00.0"};

//Variables del I2C por interrupciones
unsigned char disp=0;
unsigned char I2C_ocupado=0;
unsigned char estado_I2C=0;
unsigned char kk=33;
const char DIR[3] = {0xA6,0xD0,0x3C};
const char DIR_REG[3] = {0x32,0x1D,0x03};
unsigned char datos[3][6] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char leerMagne=1;
unsigned char giro_listo=0;
unsigned char acel_listo=0;
unsigned char magne_listo=0;

//ángulos de vuelo
double DCM[3][3];
double yaw;
double pitch;
double roll;

//variables de control de vuelo
char volando = 0;
double fijarYaw = 0;
double correcYaw = 0;
double radInput = 0;
int anteriorInput = 0;

//Tiempo de bucle
double deltaT;

//Variables de control de motores
double gas=0;
double compPitchMotor=0;
double compRollMotor=0;
double compYawMotor=0;
//I2c motores
unsigned char I2C2_ocupado=0;
unsigned char estado_I2C2=0;
unsigned char dirMotor[4];
unsigned char motor[4];
unsigned char n_motor=0;

//Variables de comandos de entrada
int input[4]={7600,7600,7600,5400};
int inOffset[4]={7600,7600,7600,5400};


int errorFlag=0;


//errores
char flag=0;

//CALIBRACION

unsigned char estado_calibracion=0;

//  Acelerometro
double ACEL_X_MIN;
double ACEL_X_MAX;
double ACEL_Y_MIN;
double ACEL_Y_MAX;
double ACEL_Z_MIN;
double ACEL_Z_MAX;

double ACEL_OFFSET_X;
double ACEL_OFFSET_Y;
double ACEL_OFFSET_Z;
//  Magnetometro
double MAGN_X_MIN;
double MAGN_X_MAX;
double MAGN_Y_MIN;
double MAGN_Y_MAX;
double MAGN_Z_MIN;
double MAGN_Z_MAX;

//  Giroscopo
double GIRO_OFFSET_X;
double GIRO_OFFSET_Y;
double GIRO_OFFSET_Z;



//Variables de calibración RC Input
unsigned int ICMAX[4]={9600,9600,9600,9600};
unsigned int ICMIN[4]={5600,5600,5600,5600};
unsigned char flag_calibracionRC=0;


//Definiciones
#define PI 3.14159265358979
#define CONV_GIRO1 (1.0/14.375)
#define CONV_GIRO2 (0.0695652173913)
#define CONV_ACEL (1.0/256.0)
#define RAD2DEG (180.0/PI)
#define DEG2RAD (PI/180.0)
#define PWM2YAW (PI/2000.0)
#define PWM2INCL ((0.25*PI)/2000.0)
#define GAS2MOTOR   (1.0/4000.0)

//Calibracion
#define ACEL_X_OFFSET ((ACEL_X_MIN + ACEL_X_MAX) / 2.0f)
#define ACEL_Y_OFFSET ((ACEL_Y_MIN + ACEL_Y_MAX) / 2.0f)
#define ACEL_Z_OFFSET ((ACEL_Z_MIN + ACEL_Z_MAX) / 2.0f)
#define ACEL_X_SCALE (1.0 / (ACEL_X_MAX - ACEL_X_OFFSET))
#define ACEL_Y_SCALE (1.0 / (ACEL_Y_MAX - ACEL_Y_OFFSET))
#define ACEL_Z_SCALE (1.0 / (ACEL_Z_MAX - ACEL_Z_OFFSET))

#define MAGN_X_OFFSET ((MAGN_X_MIN + MAGN_X_MAX) / 2.0f)
#define MAGN_Y_OFFSET ((MAGN_Y_MIN + MAGN_Y_MAX) / 2.0f)
#define MAGN_Z_OFFSET ((MAGN_Z_MIN + MAGN_Z_MAX) / 2.0f)
#define MAGN_X_SCALE (100.0 / (MAGN_X_MAX - MAGN_X_OFFSET))
#define MAGN_Y_SCALE (100.0 / (MAGN_Y_MAX - MAGN_Y_OFFSET))
#define MAGN_Z_SCALE (100.0 / (MAGN_Z_MAX - MAGN_Z_OFFSET))

extern unsigned int Pulsado_Propor ;
extern unsigned int Pulsado_Diferen ;
extern unsigned int Pulsado_Integral ;
extern unsigned int valorPotenciometro;

extern float Kp;
extern float Ki;
extern float Kd;

extern unsigned char Calculo_PID;
extern unsigned char Calcula_PWM;

extern unsigned char Calculo_Kalman;
extern unsigned char Impre_Acel;
extern float angulo;
//=========================
BTLE_PERIPHERAL_STATES_T geBTLE_Peripheral_State;

int main(void)
{
Nop();
Nop();
    //Inic_Oscilador();		//Selección e inicializacion del Reloj
    Init_SystemClock();
    Init_XPL16_Board_LEDs();
    Init_XPL16_Board_Switches();
//       AD1PCFG = 0xFFFF;
       AD1PCFGL = 0xFFFF;
       AD1PCFGH = 0xFFFF;

    Init_Timer();
    BTLE_ConfigureUART(FCY);
    BTLE_As_PeripheralInit();
    
    
    Nop();
Nop();
    


    Inic_LCD();
    //Inicializar UART2
    //initRS232_2();

    //Inicializaciones de variables
    //cronometro
    mSeg=0;
    dec=0;
    seg=0;
    min=0;
    parado=0;
    //Inicializaciones de perifericos
    //Inic_Timer_1();		//Inicializa Timer_1
    //initRS232_2_DMA();
    char Texto_2[]= {"SF>CAD|S3-S4>PLY" // 16 caracteres Fila 1
                           "Crono: --/--/-- "}; // 16 caracteres Fila 2
    Texto_2[6]='0';
    //Copia_FLASH_RAM(Texto_2);
    //Mostrar texto en LCD
    //Copia_FLASH_RAM(TEXTO_ACEL);

    //Inicializacion de LCD
    //Init_LCD();

    //Inicializar I2C1
    

    InitI2C_1();
    Nop();
    Inic_Acel();
    Inic_Giro();
    calibrar_giro();
    calibrar_acel();
    Nop();
    Nop();
    Nop();
    //Función de inicializacion del TIMER7
   // //Inic_Timer_6();
    Inic_CAD();
    Init_PID();
    inic_PWM();
    configura_CN();
    Inic_Timer_7();


    //Inicialización del Timer 4 para el LCD por Interrupciones
    //Inic_Timer_4();

    //Inic_Timer_3(); //Timer para capturar entrdas PWM


    //Resto de inicializaciones
    //Bucle de inicializacion


    //Inicializar strings

//=========================
    //Mostrar texto en LCD
//	Copia_FLASH_RAM(TEXTO_ACEL);





    //---------------------
    //----CALIBRACION------
    //---------------------

    //Inicializar DCM

extern unsigned char Calculo_PID;
extern unsigned char Calcula_PWM;

extern unsigned char Calculo_Kalman;
extern unsigned char Impre_Acel;

    geBTLE_Peripheral_State = eBTLE_POR_RESET_STATE;
//Bucle principal
    while(1)
    {
        Nop();
        Nop();
        Nop();
 /*
         if (Calculo_PID == 1)
        {
         calcularPID(); 
         Calculo_PID = 0;
        }
  *
*/      if (Calculo_Kalman == 1)
        {
              //filtroKalman(angulo,vec_giro[0]);
              Calculo_Kalman = 0;
         }
        if (Calcula_PWM == 1)
        {
            //calcularPID();
            //calcularPWM();

         Calculo_PID = 0;
            Calcula_PWM = 0;
        }
        
        if (Impre_Acel == 1)
        {
            print_PID();
           // print_Angulo();
            Impre_Acel = 0;
        }

        
        if (Pulsado_Propor == 1)
        {   
            Nop();
            Nop();


            if(valorPotenciometro<256)
             Kp --;
            else if (valorPotenciometro<512)
             Kp=Kp-10;
            else if (valorPotenciometro<768)
             Kp++;
            else if (valorPotenciometro<1024)
             Kp=Kp+10;
          Pulsado_Propor = 0;
        }

         if (Pulsado_Diferen == 1)
        {
            Nop();
            Nop();
            if(valorPotenciometro<256)
             Kd --;
            else if (valorPotenciometro<512)
             Kd=Kd-10;
            else if (valorPotenciometro<768)
             Kd++;
            else if (valorPotenciometro<1024)
             Kd=Kd+10;
            Pulsado_Diferen = 0;
        }

        if (Pulsado_Integral == 1)
        {
            Nop();
            Nop();
            if(valorPotenciometro<256)
             Ki --;
            else if (valorPotenciometro<512)
             Ki=Ki-10;
            else if (valorPotenciometro<768)
             Ki++;
            else if (valorPotenciometro<1024)
             Ki=Ki+10;
          Pulsado_Integral = 0;
        }
        
       switch(geBTLE_Peripheral_State)
        {
            case eBTLE_POR_RESET_STATE:
                gCmdsTobeExecuted_index = AssignTheIndexUsingtheValueFromCmdTobeExecuted(ePERI_COMMAND_MODE);
                geBTLE_Peripheral_State = eBTLE_QUERY_FOR_PAIRING;
                RCON = 0;
                break;
            case eBTLE_QUERY_FOR_PAIRING:
                break;
        }

        Uart_Rcv_Msg_Handler();
        // check is there any message to be processed.
        if (Message_Rx_Packet.Msg_To_Be_Processed)
        {
            if (!GetBTLE_Connected_Status())
            {
                Peripheral_CMD_StateMachine();
            }
            else
            {         
                // bluetooth is connected. // In MLDP mode
                P_BTLE_PERI_SW_LED_T lBTLE_Resp =
            GetBTLE_ResponseIndexFrom_BTLE_CONTROL_Strings((const char *)Message_Rx_Packet.Message_Buffer);
                // Decode the response
                if (lBTLE_Resp != ePERI_CONTROL_NOT_IN_THE_LIST)
                {
                   Process_Control(lBTLE_Resp);
                }
            }
        }

       if (Message_Rx_Packet.Msg_To_Be_Processed)
       {
           ClearMessageRxBuffer();
           mReset_RxMessageTobeProcessedFlag();
       }
       Uart_Transmit_MessagePacket();

       Nop();
       Nop();    


    }	//Fin del bucle principal
}	//Fin del main


//*******************************************************************************
unsigned char dato_Uart2Uart1;

 void Uart2_Recive()
 {
     if (_U2RXIF == 1)
     {
     dato_Uart2Uart1 = U2RXREG;
    Nop();
    Nop();

     U1TXREG = dato_Uart2Uart1;
        _U2RXIF = 0;
     }
 }


/*******************************************************************************
  Function:   void Process_Control(P_BTLE_PERI_CONTROL_T lBTLE_Resp)
  Summary:
 * Esta funcion se utiliza para el control remoto del robot, cuando nos llegue
 * alguno de los comandos validos para el control se le añadiran o disminuiran
 * las velocidades a las ruedas del robot para que este ande hacia adelante,
 * hacia atras o incluso que gire hacia ambos sentidos (izquierda/derecha)
  Description:
  Precondition:    None.
  Parameters:    P_RESP_Strings_Enum_T lBTLE_Resp. 
  Returns:    None.
  Remarks:
/******************************************************************************/

void Process_Control(P_BTLE_PERI_CONTROL_T lBTLE_Resp)
{
    if (ePERI_GO_FORDWARD == lBTLE_Resp)
    {
        velExtra_RI=1000;
        velExtra_RD=1000;
        XPL16_D10_LED_LAT = XPL16_D10_LED_TurnON;
    }
    else if (ePERI_GO_BACK == lBTLE_Resp)
    {
        velExtra_RI=-1000;
        velExtra_RD=-1000;
        XPL16_D9_LED_LAT = XPL16_D9_LED_TurnON;
    }
    else if (ePERI_TURN_RIGHT == lBTLE_Resp)
    {
        velExtra_RI=1000;
        velExtra_RD=-1000;
        XPL16_D8_LED_LAT = XPL16_D8_LED_TurnON;        
    }
    else if(ePERI_TURN_LEFT == lBTLE_Resp)
    {
        velExtra_RI=-1000;
        velExtra_RD=1000;
        XPL16_D7_LED_LAT = XPL16_D7_LED_TurnON; 
    }
    else if(ePERI_STOP == lBTLE_Resp)
    {
        velExtra_RI=0;
        velExtra_RD=0;
        XPL16_D10_LED_LAT = XPL16_D10_LED_TurnOFF;
        XPL16_D9_LED_LAT = XPL16_D9_LED_TurnOFF;
        XPL16_D8_LED_LAT = XPL16_D8_LED_TurnOFF;
        XPL16_D7_LED_LAT = XPL16_D7_LED_TurnOFF; 
    }
}


/*******************************************************************************
  Function:   void Schedule_1X_Task(void)
  Summary: Base loop.
  Description:
  Precondition:    Refer to config.h (TimeOut_XmS) for timing of this loop.
  Parameters:
  Returns:    None.
  Remarks:
/******************************************************************************/

void Schedule_1X_Task(void)
{
    //Process_Switches();
}


/*******************************************************************************
  Function:   void Schedule_2X_Task(void)
  Summary:  This function is called for every alternate base loop.
  Description:
  Precondition:    Refer to config.h (TimeOut_XmS) for timing of this loop.
  Parameters:
  Returns:   None.
  Remarks:
/******************************************************************************/

void Schedule_2X_Task(void)
{

}

/*******************************************************************************
  Function:   void Schedule_3X_Task(void)
  Summary: This function is called for every third base loop.
  Description:
  Precondition:    Refer to config.h (TimeOut_XmS) for timing of this loop.
  Parameters:
  Returns:    None.
  Remarks:
/******************************************************************************/

void Schedule_3X_Task(void)
{

}


/*******************************************************************************
  Function:   void Schedule_4X_Task(void)
  Summary:  This function is called for every fourth base loop.
  Description:
  Precondition:    Refer to config.h (TimeOut_XmS) for timing of this loop.
  Parameters:
  Returns:    None.
  Remarks:
/******************************************************************************/
void Schedule_4X_Task(void)
{

}

/*******************************************************************************
  Function:   void Schedule_5X_Task(void)
  Summary:  This function is called for every fifth base loop.
  Description:
  Precondition:   Refer to config.h (TimeOut_XmS) for timing of this loop.
  Parameters:
  Returns:    None.
  Remarks:
/******************************************************************************/
void Schedule_5X_Task(void)
{

}

/*******************************************************************************
  Function:   void Schedule_10X_Task(void)
  Summary:  This function is called for every tenth base loop.
  Description:
  Precondition:    Refer to config.h (TimeOut_XmS) for timing of this loop.
  Parameters:
  Returns:    None.
  Remarks:
/******************************************************************************/
void Schedule_10X_Task(void)
{
    
}