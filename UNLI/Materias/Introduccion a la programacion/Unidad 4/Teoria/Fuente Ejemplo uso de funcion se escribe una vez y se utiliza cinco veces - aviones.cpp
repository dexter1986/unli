/*
Este ejemplo muestra un de los usos de las funciones que es escribir una rutina
una sola vez y usarla muchas, en este caso imprBombardero que dibuja un aviocito
en las coordenadas que le suministremos.
En este ejemplo dibujamos cinco aviones y los movemos por la pantalla escribiendo
la funci?n de dibujo una sola vez.
*/
#include <constream>
#include <windows.h>
using namespace conio;
using namespace std;

void imprBombardero(int x, int y);

int main() {
	int x1,x2,x3,x4,x5; //coordenadas x de los aviones
	int y1,y2,y3,y4,y5; //coordenadas y de los aviones
	
	x1=x2=x3=x4=x5=2; //todos empiezan en x=2
	y1=2; //empiezan en distintas alturas
	y2=6;
	y3=9;
	y4=14;
	y5=19;
	cout<<clrscr; //borramos la pantalla
	for(int n=2;n<70;++n)
	{
		imprBombardero(x1,y1); //imprimimos el avi?n n?mero 1
		imprBombardero(x2,y2); //imprimimos el avi?n n?mero 2
		imprBombardero(x3,y3); //imprimimos el avi?n n?mero 3
		imprBombardero(x4,y4); //imprimimos el avi?n n?mero 4
		imprBombardero(x5,y5); //imprimimos el avi?n n?mero 5
		++x1; //avanzamos avi?n 1
		++x2; //avanzamos avi?n 2
		++x3; //avanzamos avi?n 3
		++x4; //avanzamos avi?n 4
		++x5; //avanzamos avi?n 5
		Sleep(100);
	}
	
	return 0;
}

void imprBombardero(int x, int y) //dibuja un avi?n en las coordenadas (x, y)
{
	cout<<setxy(x,y)<<" -"<<(char)220<<"   "<<(char)218<<(char)191<<x;
	cout<<setxy(x,y+1)<<" -"<<(char)223<<(char)223<<(char)223<<(char)175<<(char)223<<(char)223;
}

/* (char) este modificador cambia el n?mero siguiente al caracter correspondiente
tambi?n funciona a la inversa (int)'0' devuelve el codigo de caracter 0 que ser?a 48*/
