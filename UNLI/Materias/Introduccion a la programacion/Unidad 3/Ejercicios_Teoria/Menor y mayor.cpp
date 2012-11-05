#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>

using namespace std;

int main(int argc,char *argv[])
{
	int menor=9999;
	int mayor=0;
	int nro;
	cout<<"Ingrese una serie de numeros."<<endl<<"Se dira cual fue el menor y mayor de todos ellos"<<endl<<"Para salir ingrese el numero 9999"<<endl;
	while(nro != 9999)
	{
		cout<<"Ingrese un numero: ";
		cin>>nro;
		if(nro<9999)
		{
			if(nro<menor)
				menor = nro;
			else if(nro>mayor)
				mayor = nro;
		}
	}	
	
	cout<<"El numero menor fue: "<<menor<<" y el mayor: "<<mayor<<endl;
	system("PAUSE");
	return 0;
}
