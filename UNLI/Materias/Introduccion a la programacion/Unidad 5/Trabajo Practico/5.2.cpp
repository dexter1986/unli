#include<iostream>
#include<constream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

void simularTirada(int arr[],int cant);
void ordenar(int arr[],int cant);
void mostrarTirada(int arr[],int cant);
void buscarJuego(int arr[],int cant);

int main(int argc,char *argv[])
{
	int tirada[5];	
	
	srand(time(NULL));

	cout<<"Simulacion de jugada de generala"<<endl;		
	simularTirada(tirada,5);
	ordenar(tirada,5);
	cout<<"Tirada ";
	mostrarTirada(tirada,5);	
	cout<<endl;		
	cout<<"Resultado: ";	
	buscarJuego(tirada,5);
	cout<<endl;
	
	system("PAUSE");
	return 0;
}

void simularTirada(int arr[],int cant)
{
	for(int i=0;i<cant;i++)
	{
		arr[i] = rand()%6+1;
	}
}
//Ordena en forma ascendente
void ordenar(int arr[],int cant)
{	
	int aux;
	for(int index=0;index<cant-1;index++)
	{
		for(int i=index+1;i<cant;i++)
		{	
			if(arr[index]>arr[i])
			{
				aux = arr[index];
				arr[index] = arr[i];
				arr[i] =  aux;
			}
		}
	}
}

void mostrarTirada(int arr[],int cant)
{
	for(int i=0;i<cant;i++)
	{
		cout<<arr[i];
	}
}








void buscarJuego(int arr[],int cant)
{
	//Escalera
	if(arr[0] == 1 && arr[1] == 2 && arr[2] == 3 && arr[3] == 4 && arr[4] == 5)
	{
		cout<<"Escalera";
	}else if(arr[0] == 2 && arr[1] == 3 && arr[2] == 4 && arr[3] == 5 && arr[4] == 6)
	{
		cout<<"Escalera";
	}else if(arr[0] == 1 &&  arr[1] == 3 && arr[2] == 4 && arr[3] == 5 && arr[4] == 6)
	{
		cout<<"Escalera";
	}else if(arr[0] == arr[1] == arr[2] == arr[3] == arr[4])
	{
		cout<<"Generala";
	}
	else{			
		int contador[6] = {0,0,0,0,0,0};
		
		for(int i=0;i<cant;i++)
		{
			contador[arr[i]-1]++;
		}
		
		int par = 0;
		int terna = 0;
		int cuarteto = 0;
		
		for(int i=0;i<6;i++)
		{
			if(contador[i]==2)
			{
				par++;
			}else if(contador[i]==3)
			{
				terna++;				
			}else if(contador[i]==4)
			{
				cuarteto++;
			}
		}
		
		if(cuarteto>0)
		{
			cout<<"Poker";
		}else if(par>0 && terna >0)
		{
			cout<<"Full";
		}else if(terna>0)
		{
			cout<<"Pierna";
		}else if(par>0)
		{
			for(int i=0;i<6;i++)
			{
				if(contador[i]==2)
				{
					cout<<(i+1)*2<<" al "<<i+1;
					par--;
					if(par>0)
						cout<<" o ";					
				}
				
				if(par==0)
					break;
			}
		}
	}
	
}


