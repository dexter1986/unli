/*
Ejemplo de Sobrecarga de Funciones

Aqu? tratamos de demostrar que dependiendo del tipo de parametros que colocamos
al llamar a la funci?n del mismo nombre el compilador elije la correcta

Aunque no lo parezca la divisiones entre dos enteros no son iguales a entre dos
float

Si quieren ver bien que funci?n elije pueden agregar a dividir con enteros un
cout<<"entero" y al dividir con float un cout<<"float"

*/

#include<conio.h>
#include<iomanip>
#include <iostream>
using namespace std;

int dividir (int a, int b)
{ 
	return (a/b); 
}
float dividir (float a, float b)
{ 
	return (a/b); 
}


int main ()
{
	int x=5,y=2;
	float n=5.0,m=2.0;
	cout << dividir (x,y);
	cout << "\n";
	cout << dividir (n,m);
	return 0;
}
