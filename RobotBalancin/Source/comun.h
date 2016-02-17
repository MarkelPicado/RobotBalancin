/* 
 * File:   comun.h
 * Author: AMRP
 *
 * Created on 2 de junio de 2015, 11:35
 */

#define freq 5000


#if freq==5000
    #define PRT_PWM 8000
    #define LIMITE_PWM 8000.0
#elif freq==20000
    #define PRT_PWM 2000
    #define LIMITE_PWM 2000.0
#endif
