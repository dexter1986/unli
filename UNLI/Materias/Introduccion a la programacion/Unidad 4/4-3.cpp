#include<constream>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<iomanip>
#include<ctime>

using namespace conio;
using namespace std;

int tirada(int caras);
bool devuelveTiradaPenalizacion(int caras,int penalizacion,int dados);
bool devuelveTiradaVentaja(int caras,int ventaja,int dados);
bool validarVentaja(int caras,int ventaja,int dados);

int main(int argc,char *argv[])
{
	srand(time(NULL));
	
	int dados;
	int caras = 20;
	int numero;		
	
	cout<<"Simulador de tirada."<<endl<<endl;
	cout<<"Numero de dados: ";
	cin>>dados;
	cout<<"Numero de caras: ";
	cin>>caras;
	cout<<endl<<"Ingrese un numero positivo para ventaja o negativo para penalizacion."<<endl<<"Si ingresa cero (0) no se toma en cuenta"<<endl<<endl;
	cout<<"Numero: ";
	cin>>numero;
	
	bool esVentaja = false;
	
	if(numero >= 0)
	{
		esVentaja = true;
		if(numero > 0)
		{
			bool salir = !validarVentaja(caras,numero,dados);
			if(salir)
			{
				cout<<endl<<"No es posible una ventaja de "<<numero<<" con el dado seleccionado."<<endl;
				return 0;
			}
		}
	}else
	{
		numero = abs(numero);
	}
	
	bool repetir = false;
		
	cout<<endl<<"Resultado de la simulacion:"<<endl<<endl;
	
	do
	{
		if(esVentaja)
		{
			repetir = !devuelveTiradaVentaja(caras,numero,dados);		
		}else
		{
			repetir = !devuelveTiradaPenalizacion(caras,numero,dados);
		}
		cout<<endl;
	}while(repetir);
	
	cout<<endl<<"Gracias por usar este programa."<<endl<<endl<<"Hasta luego."<<endl<<endl;
	
	system("PAUSE");
	
	return 0;
}

bool devuelveTiradaPenalizacion(int caras,int penalizacion,int dados)
{
	int total = 0;
	int tirada =0;
	for(int i=0;i<dados;i++)
	{
	  tirada = rand()%caras+1;
	  total += tirada;
	  cout<<tirada<<" ";	
	}
	cout<<"--> "<<total;
	if(total < penalizacion)
		return true;
	return false;
}

bool devuelveTiradaVentaja(int caras,int ventaja,int dados)
{
	int total = 0;
	int tirada =0;
	for(int i=0;i<dados;i++)
	{
		tirada = rand()%caras+1;
		total += tirada;
		cout<<tirada<<" ";
	}	
	cout<<"--> "<<total;
	if(total > ventaja)
		return true;
	return false;
}

bool validarVentaja(int caras,int ventaja,int dados)
{
	if(ventaja >= caras*dados)
		return false;
	
	return true;
}

int tirada(int caras)
{
	return (int)rand()%caras+1;
}
