// Ejemplo: arreglos como par?metros
#include <iostream>
#include <iomanip>

using namespace std;

void muestra_arreglo (int lista[], int largo);

int main ()
{ 
	int v1[] = {35, 41, 22};
	int v2[] = {12, 4, 6, 15, 10};
	muestra_arreglo(v1,3);
	muestra_arreglo(v2,5);
	return 0;
}


void muestra_arreglo (int lista[], int largo)
{ 
	for (int i=0; i<largo; i++)
		cout<<setw(4)<<lista[i];
	cout<<endl;}
