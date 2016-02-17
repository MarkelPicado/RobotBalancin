/*
** CONVERSIONES
** 
*/

//#include <p24fj128ga010.h>
#include <p24HJ256GP610A.h>

unsigned char c1;
unsigned char c2;
unsigned char c3;
unsigned char c4;
unsigned char c5;
unsigned char c0;
int v1;
int v2;
int v3;
int v4;

signed short aux_c;
signed short aux;

//===================================================
void Hex_ASCII (int c)
{
    c1 = (c & 0x000F) + 0x30;
    if (c1 > 0x39) c1 = c1 + 0x07;

    c2 = ((c >> 4) & 0x000F) + 0x30;
    if (c2 > 0x39) c2 = c2 + 0x07;

    c3 = ((c >> 8) & 0x000F) + 0x30;
    if (c3 > 0x39) c3 = c3 + 0x07;

    c4 = ((c >> 12) & 0x000F) + 0x30;
    if (c4 > 0x39) c4 = c4 + 0x07;
}


void convASCII( unsigned int c)	//Convierte a ASCII, 4 caracteres: c1 c2 c3 c4
{
    c0=c1=c2=c3=c4='0';
    if(c/10000)
    {
        c0=(c/10000+'0');
    }

   c = c - (c/10000)*10000;
   if(c/1000) 
    {
       c1=(c/1000+'0');
    }
	
    c = c - (c/1000)*1000;
    if(c/100) 
	{  	c2=(c/100+'0'); 
    }

    c = c - (c/100)*100;
    if(c/10) 
	{ 	c3=(c/10+'0'); 
    }

    c = c - (c/10)*10;
    	c4=(c+'0');
}

//Convierte entero 16 bits a caracteres con signo
void signed16_ASCII(signed short c)
{
    c0=c1=c2=c3=c4=c5='0';
    if(c & 0x8000){
        c0='-';
        aux_c= ~c + 0x0001;
    }else{
        c0=' ';
        aux_c=c;
    }

    if(aux == aux_c/10000)
    {
        c1+=aux;
    }
    aux_c -= aux*10000;

    if(aux == aux_c/1000)
    {
        c2+=aux;
    }
    aux_c -= aux*1000;

    if(aux == aux_c/100)
    {
        c3+=aux;
    }
    aux_c -= aux*100;

    if(aux == aux_c/10)
    {
        c4+=aux;
    }
    aux_c -= aux*10;

    c5 += aux_c;
}

//Convierte entero 12 bits a caracteres con signo
void signed12_ASCII(signed short c)
{
    /*c0=c1=c2=c3=c4='0';
    if(c & 0x8000){
        c0='-';
        aux_c= ~c + 0x0001;
    }else{
        c0=' ';
        aux_c=c;
    }

    if(aux == aux_c/1000)
    {
        c1+=aux;
    }
    aux_c -= aux*1000;

    if(aux == aux_c/100)
    {
        c2+=aux;
    }
    aux_c -= aux*100;

    if(aux == aux_c/10)
    {
        c3+=aux;
    }
    aux_c -= aux*10;

    c4 += aux_c;*/
    if(c & 0x8000){
        c0='-';
        aux_c= ~c + 0x0001;
    }else{
        c0=' ';
        aux_c=c;
    }
    v1 = (int)aux_c/1000;
    v2 = (int) (aux_c-v1*1000)/100;
    v3 = (int) (aux_c-v1*1000-v2*100)/10;
    v4 = aux_c-v1*1000-v2*100-v3*10;

    c1=v1+0x30;
    c2=v2+0x30;
    c3=v3+0x30;
    c4=v4+0x30;
}

/*
{
	c1=c2=c3=c4='0';
    if(c/1000) 
    {	c1=(c/1000+'0');
    }
	
    c = c - (c/1000)*1000;
    if(c/100) 
	{  	c2=(c/100+'0'); 
    }

    c = c - (c/100)*100;
    if(c/10) 
	{ 	c3=(c/10+'0'); 
    }

    c = c - (c/10)*10;
    	c4=(c+'0');
}
*/
//-------------------------------------------------
