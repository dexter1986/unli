#include <iostream>
using namespace std;  
int main(void)
{
	int edad, anio_nac;
	cout << "Escriba su edad:" ;
	cin >> edad;
	anio_nac = 2010 - edad;
	cout << "\n"; //Caracter especial o secuencia de escape para producir un avance de linea.
	cout << "Ud. ha nacido en " << anio_nac;
	return 0;
}

