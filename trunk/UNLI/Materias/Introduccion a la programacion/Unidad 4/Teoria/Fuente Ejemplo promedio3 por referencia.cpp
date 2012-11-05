/*
Ejemplo de la Funci?n promedio3 del material de lectura parametro por referencia

prototipo no devuelve ningun valor (void) y recibe tres enteros por valor como
parametros y un float por referencia

*/

#include<conio.h>
#include<iomanip>
#include <iostream>
using namespace std;

void promedio3(int x,int y,int z, float &p); //prototipo de la funci?n

int main( )
{
	int d1, d2, d3;
	float prom=0;
	cout <<"Ingrese el primer dato:" ; cin >> d1;
	cout <<"Ingrese el segundo dato:"; cin >> d2;
	cout <<"Ingrese el tercer dato:" ; cin >> d3;
	cout<<"prom antes de llamar a promedio3: "<<prom<<endl;
	promedio3(d1, d2, d3,prom); //llamada a la funci?n
	cout<<"prom despues de llamar a promedio3: "<<prom<<endl;
	getch();
}
void promedio3(int x,int y,int z, float &p) //definici?n de la funci?n (se repite prototipo sin ;)
{
	p=(x+y+z)/3.0 ;
	return; //como la funci?n no devuelve ning?n valor return no tiene parametros
}
