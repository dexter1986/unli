#include <cstdio>
#include <iostream>
#include <string.h>

using namespace std;

void primero(char *c,int tam,int cant);
void pares(char *c,int tam,int cant);
void contiene(char *c,int tam,int cant);

#define MAX 8
#define LEN 12

int main(int argc,char *argv[])
{
	char cadena [MAX][LEN] = {"Casa","Auto","Perro","Gato","Pato","Agua","martes","mar de ajo"};
	cout<<"La primer palabra en orden alfabetico es: ";
	primero((char *)cadena,LEN,MAX);
	cout<<endl;
	cout<<"Palabras en posiciones pares: ";
	pares((char *)cadena,LEN,MAX);
	cout<<endl;
	cout<<"Palabras que comienza con 'mar': ";
	contiene((char *)cadena,LEN,MAX);
	cout<<endl;
	return 0;
}

void contiene(char *c,int tam,int cant)
{
	int index=0;	
	for(int i=0;i<cant;i++)
	{
		if(strncmp("mar",c+index,3)==0)
			cout<<"'"<<c+index<<"' ";
		index = i*tam;
	}
}

void pares(char *c,int tam, int cant)
{
	for(int i=0;i<cant;i++)
	{
		if(i%2 == 0)
			continue;
		cout<<"'"<<c+i*tam<<"' ";
	}
}
void primero(char *c,int tam,int cant)
{
	char *aux;	
	int index = 0 ;
	aux = c;
	for(int i=1;i<cant;i++)
	{
		index = i*tam;
		if(strcmp(c+index,aux) < 0)
			aux = c+index;
	}	
	
	cout<<"'"<<aux<<"'";
}
