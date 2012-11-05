#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>

using namespace std;

int main(int argc,char *argv[])
{
	int menor=999999;
	int mayor=0;
	int contador=0;
	float promedio; 
	int nro;
	cout<<"Ingrese una serie de numeros."<<endl<<"Se dira cual fue el promedio"<<endl<<"sin tener en cuenta el mayor y el menor de todos ellos"<<endl<<"Para salir ingrese el numero 999999"<<endl;
	while(nro != 999999)
	{
		cout<<"Ingrese un numero: ";
		cin>>nro;
		if(nro<9999)
		{
			if(nro<menor)
				menor = nro
			else if(nro>mayor)
				mayor = nro;
			promedio += nro;
			contador++;
		}
	}	
	if(contador <=2)
		cout<<"Debe ingresar mas de 2 numeros"<<endl;
	else
	{		
		promedio -= menor;
		promedio -= mayor;
		promedio /= contador -2;
		cout.precision(2);
		cout<<fixed<<"El promedio es: "<<promedio<<endl;
	}
	system("PAUSE");
	return 0;
}
