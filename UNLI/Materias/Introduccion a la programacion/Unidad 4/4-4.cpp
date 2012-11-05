#include<constream>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<iomanip>
#include<ctime>
#include<conio2.h>

#include<windows.h>

using namespace conio;
using namespace std;

void formalineah(int cantidad,char caracter);
void formalineav(int cantidad,char caracter);
void hacerRecuadro(int sup,int izq,int inf,int der);

int main(int argc,char *argv[])
{
	int cantidad;
	cout<<"Este programa dibuja rectangulos interiores.\n\n";
	cout<<"Ingrese la cantidad de rectangulos a dibujar (1-12): ";
	cin>>cantidad;
	
	if(cantidad > 12)
		cantidad = 12;
	else if( cantidad < 1)
		cantidad = 1;
	
	clrscr();
	int sup = 1;
	int izq = 1;
	int inf = 25;
	int der = 80;
		
	for(int i=0;i<cantidad;i++)
	{
		hacerRecuadro(sup,izq,inf,der);		
		sup++;
		izq++;
		inf-=2;
		der-=2;
	}
	gotoxy(25,13);
	system("Pause");	
	return 0;
}

void hacerRecuadro(int sup,int izq,int inf,int der)
{
	char lineaH = 205;
	char lineaV = 186;
	char codoSupIzq = 201;
	char codoSupDer = 187;
	char codoInfIzq = 200;
	char codoInfDer = 188;	
	
	gotoxy(izq,sup);	
	putchar(codoSupIzq);
	formalineah(der-3,lineaH);	
	putchar(codoSupDer);
	gotoxy(wherex()-1,wherey()+1);	
	formalineav(inf-1,lineaV);
	gotoxy(izq,sup+1);	
	formalineav(inf-1,lineaV);		
	putchar(codoInfIzq);
	formalineah(der-3,lineaH);
	putchar(codoInfDer);	
}

void formalineah(int cantidad,char caracter)
{	
	for(int i=0;i<cantidad;i++)
	{
		putchar(caracter);			
	}
}

void formalineav(int cantidad,char caracter)
{
	int x = wherex();
	int y = wherey();
	
	for(int i=0;i<cantidad;i++)
	{
		putchar(caracter);
		gotoxy(x,y+i);
	}
}
