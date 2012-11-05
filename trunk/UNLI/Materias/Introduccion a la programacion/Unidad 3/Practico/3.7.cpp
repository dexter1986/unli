#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;

int main(int argc,char *argv[])
{
	int secreto;
	int numero;
	int intentos = 5;
	bool esAcerto = false;
	
	srand(time(NULL));
	secreto = rand()%20+1;
	cout<<"Debes adivinar el numero secreto."<<endl<<"Dicho numero esta entre 1 y 20."<<endl<<"Para ello tienes "<<intentos<<" intentos para hallarlo."<<endl;
		
	for(int i=0;i<intentos;i++)
	{
		cout<<endl<<"Intento "<<i+1<<endl;
		cout<<"Elige un numero: ";
		cin>>numero;
		if(numero<secreto)
			cout<<"Tu numero es menor que el numero secreto."<<endl;
		else if(numero>secreto)
			cout<<"Tu numero es mayor que el numero secreto."<<endl;
		else
		{
			cout<<endl<<"Felicitaciones hacertaste el numero secreto."<<endl;
			esAcerto = true;
			break;
		}		
	}
	
	if(!esAcerto)
		cout<<endl<<"No hacertaste el numero secreto."<<endl<<"El numero secreto era: "<<secreto<<endl;
	
	cout<<endl<<"Hasta luego"<<endl;
	system("PAUSE");
	return 0;
}
