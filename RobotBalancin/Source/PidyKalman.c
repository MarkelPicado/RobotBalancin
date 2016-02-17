/*
Grupo: 2    Autor: Markel y Anartz

Descripcion: Este modulo principalmente se utiliza para darle valores a los servos
mediante el PWM. Aparte de esto tambien esta la funcion que escribe automaticamente un 10
con el brazo robotico
*/

#include "p24HJ256GP610A.h"
#include "PWM.h"
#include "stdlib.h"
#include "comun.h"


#define CTE_KP 330.0//225.0//335.0
#define CTE_KI 25.25//1.25//0.9
#define CTE_KD 1150.0//23.0//15.0



#define SETPOINT 0.0
#define MARGEN_INTEGRADOR 5.0

extern int errorFlag;
extern float angulo;
int ultimoAngulo;
int auxoutputPID=0;
int outputPID=0;
float error;
float prev_error;
float Proportional;
float Integral;
float Derivative;
float Kp;
float Ki;
float Kd;
float anguloFiltro=0.0;
long LastTime;
long SampleTime;
long timeOutInt;
int turbo;
float k_k;


unsigned char Calculo_PID = 0;

extern float vec_giro[3];

void Init_PID(){
// Inicializar y habilitar TIMER7
	T6CONbits.TON = 0; // Disable Timer
	T6CONbits.TCS = 0; // Select internal instruction cycle clock
	T6CONbits.TGATE = 0; // Disable Gated Timer mode
	T6CONbits.TCKPS = 0b10; // Selecionar Prescaler: 1:64
	TMR6 = 0x00; // Clear timer register
	PR6 = 3125; // Periodo Giroscopo: 10ms = 6250
//	_T6IP = 0x01; // Set Timer 7 Interrupt Priority Level
	_T6IP = 0x06; // Set Timer 7 Interrupt Priority Level
	_T6IF = 0; // Clear Timer 7 Interrupt Flag
	_T6IE = 0; // Enable Timer 7 interrupt
	T6CONbits.TON = 1; // Start Timer


        Kp=CTE_KP;
        Ki=CTE_KI;
        Kd=CTE_KD;
        prev_error=0.0;
        errorFlag=15;
        Proportional=0.0;
        Integral=0.0;
        Derivative=0.0;

}


/*float filtro(float anguloAcel,float anguloGir){
    anguloFiltro=(0.97*anguloGir)+(0.03*anguloAcel);
    return anguloFiltro;
}*/


void calcularPID(){

    errorFlag=16;

    //Angle = Angle + (((anguloFiltro-Angle) * 0.5 + vec_giro[0]) * 0.01);
   
    
    error=anguloFiltro-SETPOINT;

    Proportional=Kp*error;
    Derivative=error-prev_error;
    
    if ( (abs(error)<=MARGEN_INTEGRADOR))
    {
      Integral+=Ki*error;
        if (Integral>LIMITE_PWM)Integral=LIMITE_PWM;
        else if(Integral < -LIMITE_PWM) Integral= -LIMITE_PWM;
    }
    else {
        if(error>=0){
            Integral+=Ki*error/2;
        }
        else Integral+=Ki*error/2;
    }
     //Parte derivativa
    
   
    //----------------------------------------------------------------
    k_k=Proportional+ Integral +Kd * Derivative;
   //k_k = Kp * anguloFiltro + Kd * vec_giro[0]+Integral;

    //k_k=k_k+300.0;
    //Limites de la salida.
    //auxoutputPID=auxoutputPID+turbo;
    if (k_k <-LIMITE_PWM)
    {
      k_k=-LIMITE_PWM;
    }else if (k_k>=LIMITE_PWM)
    {
      k_k=LIMITE_PWM;
    }

    auxoutputPID=(int)k_k;
    outputPID=auxoutputPID;
    prev_error=error;
}

float Q_bias, Angle_err;
float K_0, K_1, t_0, t_1;
float Pdot [4] = {0,0,0,0};
float PP [2] [2] = {{1, 0}, {0, 1}};
float Q_angle = 0.001;
float Q_gyro = 0.003; // small, adjust the tracking speed of the waveform, but do not believe that prediction
float R_angle = 0.5;
float dt = 0.01; // dt for kalman filter sampling time;
char C_0 = 1;
float PCt_0, PCt_1, E;

void filtroKalman(float Accel, float Gyro){
anguloFiltro += (Gyro - Q_bias) * dt; // a priori estimate


Pdot [0] = Q_angle - PP [0] [1] - PP [1] [0]; // Pk- differential priori estimate error covariance

Pdot [1] = - PP [1] [1];
Pdot [2] = - PP [1] [1];
Pdot [3] = Q_gyro;

PP [0][0] += Pdot [0] * dt; // Pk- priori estimate error covariance integral differential
PP [0][1] += Pdot [1] * dt; // = a priori estimate error covariance
PP [1][0] += Pdot [2] * dt;
PP [1][1] += Pdot [3] * dt;

Angle_err = Accel - anguloFiltro; // zk- priori estimate

PCt_0 = C_0 * PP [0] [0];
PCt_1 = C_0 * PP [1] [0];

E = R_angle + C_0 * PCt_0;

K_0 = PCt_0 / E;
K_1 = PCt_1 / E;

t_0 = PCt_0;
t_1 = C_0 * PP [0] [1];

PP [0][0] -= K_0 * t_0; // after posteriori estimate error covariance
PP [0][1] -= K_0 * t_1;
PP [1][0] -= K_1 * t_0;
PP [1][1] -= K_1 * t_1;

anguloFiltro += K_0 * Angle_err; //posterior estimate after //
Q_bias += K_1 * Angle_err; //posterior estimate after //
vec_giro[0] = Gyro - Q_bias; // output value (a posteriori estimate) = angular speed differential


//anguloFiltro=anguloFiltro+(((angulo-anguloFiltro)*0.5+vec_giro[0]) * 0.01);
Nop();
}


void _ISR _T6Interrupt (void)
{
    //calcularPID();
    Calculo_PID = 1;
    _T6IF = 0;
    errorFlag=18;
}