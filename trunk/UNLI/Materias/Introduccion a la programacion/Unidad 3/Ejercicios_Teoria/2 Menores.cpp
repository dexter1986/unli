#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>

using namespace std;

int main(int argc,char *argv[])
{
	int menor = 999999;
	int menor2 = 999999;
	int nro;
	cout<<"Ingrese una serie de numeros."<<endl<<"Se dira cual fueron los dos menores"<<endl<<"Para salir ingrese el numero 999999"<<endl;
	while(nro != 999999)
	{
		cout<<"Ingrese un numero: ";
		cin>>nro;
		if(nro<999999)
		{
			if(nro < menor)
			{
				menor2 = menor;
				menor = nro;
			}else if(nro < menor2)
			{
				menor2 = nro;
			}
		}
	}	
	
	cout<<"Los dos numeros menores fueron: "<<menor<<" y "<<menor2<<endl;
	system("PAUSE");
	return 0;
}
