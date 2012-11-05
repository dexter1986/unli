/*
Ejemplo de Variables Globales y locales del material de lectura



*/

#include<conio.h>
#include<iomanip>
#include <iostream>
using namespace std;

char a='F'; // a es una variable global porque fue definida fuera de las funciones
int main()
{
	cout<<a<<endl; // imprime la variable global
	int a=12;  // declara una variable local de la funci?n tipo int
	{ // nuevo bloque
		float a=3.4; //declara una variable local para el bloque tipo float
		cout<<a<<endl;  //imprime a, se elije la del bloque 
	} // fin del nuevo bloque las variables declaradas dentro del mismo se destruyen
	cout<<a<<endl; // imprime a, se elije la local de la funci?n antes que la global
	getch();
	return 0;
}
