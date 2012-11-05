//Ejemplo:     mostrar    una    matriz   de    2x  3   elementos
//en forma de tabla
#include<iomanip>
#include <iostream>
using namespace std;

int main()
{
	int m[2][3]={12,34,56,78,90,100};
	int i,j;
	for (i=0;i<2;i++)
	{
		for (j=0; j<3; j++)
		{
			cout<<setw(4)<<m[i][j]; //escribe elementos de una fila
		}
		cout<<endl;     //avanza a la pr?xima l?nea
	}
	return 0;
}
