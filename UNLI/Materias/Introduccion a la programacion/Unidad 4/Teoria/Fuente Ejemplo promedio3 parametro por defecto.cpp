/*
Ejemplo de la Funci?n promedio3 del material de lectura

prototipo devuelve un valor float y recibe tres enteros por valor como parametros
y el ?ltimo recibe 10 por defecto

*/

#include<conio.h>
#include<iomanip>
#include <iostream>
using namespace std;

float promedio3(int x,int y,int z=10); //prototipo de la funci?n

int main( )
{
	int d1, d2, d3;
	float p;
	cout <<"Ingrese el primer dato:" ; cin >> d1;
	cout <<"Ingrese el segundo dato:"; cin >> d2;
	cout <<"Ingrese el tercer dato:" ; cin >> d3;
	p = promedio3(d1, d2); //llamada a la funci?n sin el tercer parametro
	cout <<setprecision(3)<<"El promedio de: "<<d1<<" "<<d2<<" y "<< "10 (por defecto) es: " << p <<endl;
	p = promedio3(d1, d2, d3); //llamada a la funci?n con el tercer parametro
	cout <<setprecision(3)<<"El promedio de: "<<d1<<" "<<d2<<" y "<<d3<<" es: " << p;
	getch();
}
float promedio3(int x,int y,int z) //definici?n de la funci?n (se repite prototipo sin ;)
{
	float w=(x+y+z)/3.0 ;
	return(w);
}
