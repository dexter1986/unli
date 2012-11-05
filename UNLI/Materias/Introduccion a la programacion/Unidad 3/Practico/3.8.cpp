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
	int n1,n2;
	int intentos;
	bool esAcerto = false;
		
	cout<<"Debes adivinar el numero secreto."<<endl;
	cout<<"Ahora debes ingresar el rango de numeros."<<endl<<"De ahi se elegira al azar el numero secreto."<<endl<<endl;
	cout<<"Ingresa un numero cualquiera: ";	
	cin>>n1;
	cout<<"Ingresa otro numero cualquiera: ";	
	cin>>n2;
	cout<<"Ahora ingresa la cantidad de intentos: ";
	cin>>intentos;
	
	srand(time(NULL));
	secreto = rand()%abs(n1-n2+1);
	
	if(n1<n2)
		secreto += n1;
	else
		secreto += n2;
	
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
