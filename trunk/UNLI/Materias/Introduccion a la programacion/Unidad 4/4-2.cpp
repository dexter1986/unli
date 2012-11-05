#include<constream>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<iomanip>
#include<ctime>

using namespace conio;
using namespace std;

int tirada(int caras);
int resultado(int dados, int caras);
void generala(int &t1,int &t2,int &t3,int &t4,int &t5);
void tiradaGenerala(int &suma,int &maximo);

//
void ordenar(int &v1, int &v2);
int obtenermaximo(int v1,int v2);

int main(int argc,char *argv[])
{
	srand(time(NULL));
	
	int caras;
	int dados;
	
	cout<<"Ingrese el nro de caras: ";
	cin>>caras;	
	cout<<"La tirada dio el nro: "<<tirada(caras)<<endl<<endl;
	
	cout<<"Ingrese el nro de dados: ";
	cin>>dados;
	cout<<"Ingrese el nro de caras: ";
	cin>>caras;
	cout<<"La suma del resultado es: "<<resultado(dados,caras)<<endl<<endl;
	
	int t1,t2,t3,t4,t5;
	generala(t1,t2,t3,t4,t5);
	cout<<"Este es el resultado de una tirada de generala: "<<t1<<", "<<t2<<", "<<t3<<", "<<t4<<", "<<t5<<endl<<endl;
	
	
	int suma,maximo;
	tiradaGenerala(suma,maximo);
	cout<<"Este es el resultado de una tirada de generala, suma: "<<suma<<", "<<maximo<<endl<<endl;
	
	system("PAUSE");	
	return 0;
}

//Punto a)
int tirada(int caras)
{
	return (int)rand()%caras+1;
}
//Punto b)
int resultado(int dados, int caras)
{
	int total=0;
	
	for(int i=0;i<dados;i++)
	{
		total += (int)rand()%caras+1;
	}	
	
	return total;
}
//Punto c)
void generala(int &t1,int &t2,int &t3,int &t4,int &t5)
{
	t1  = (int)rand()%6+1;
	t2  = (int)rand()%6+1;
	t3  = (int)rand()%6+1;
	t4  = (int)rand()%6+1;
	t5  = (int)rand()%6+1;
}
//Punto d)
void tiradaGenerala(int &suma,int &maximo)
{	
	int tirada;
	int max1 = 0;
	int max2 = 0;
	
	max1 = (int)rand()%6+1;
	max2 = (int)rand()%6+1;
	
	ordenar(max1,max2);
	
	for(int i=0;i<3;i++)
	{
		tirada = (int)rand()%6+1;
			
		if(tirada > max2 || tirada > max1)		
			max1 = tirada;			
				
		ordenar(max1,max2);
	}
	
	suma = max1 + max2;	
	maximo = obtenermaximo(max1,max2);
}
//Ordena de forma ascendente, en v1 deja el menor y en v2 el mayor
void ordenar(int &v1, int &v2)
{
	int aux;
	if(v1 > v2)
	{
		aux = v1;
		v1 = v2;
		v2 = aux;
	}	
}

int obtenermaximo(int v1,int v2)
{
	if(v1 > v2)
		return v1;
	else
		return v2;
}
	
	
	
