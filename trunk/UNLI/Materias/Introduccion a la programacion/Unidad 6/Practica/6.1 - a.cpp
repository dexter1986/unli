#include <cstdio>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

void primero(char **c,int cant);
void pares(char **c,int cant);
void contiene(char **c,int cant);


int main(int argc,char *argv[])
{
	char *cadena[255];
	char aux[255];
	int cont = 0;
		
	fstream file;
	
	file.open("6.1 - a.txt",ios::in);
	
	while(!file.eof())
	{
		file.getline(aux,255);
		cadena[cont] =  new char[strlen(aux)];
		strcpy(cadena[cont],aux);				
		cont++;
	}
	
	file.close();
	
	cout<<"La primer palabra en orden alfabetico es: ";
	primero(cadena,cont);
	cout<<endl;
	cout<<"Palabras en posiciones pares: ";
	pares(cadena,cont);
	cout<<endl;
	cout<<"Palabras que comienza con 'mar': ";
	contiene(cadena,cont);
	cout<<endl;
	
	for(int i=0;i<cont;i++)
	{
		delete cadena[i];
	}
	
	return 0;
}

void contiene(char **c,int cant)
{
	for(int i=0;i<cant;i++)
	{
		if(strncmp("mar",c[i],3)==0)
			cout<<"'"<<c[i]<<"' ";	
	}
}

void pares(char **c,int cant)
{
	for(int i=0;i<cant;i++)
	{
		if(i%2 == 0)
			continue;
		cout<<"'"<<c[i]<<"' ";
	}
}
void primero(char **c,int cant)
{
	char *aux;		
	aux = c[0];
	for(int i=1;i<cant;i++)
	{
		if(strcmp(c[i],aux) < 0)
			aux = c[i];
	}	
	
	cout<<"'"<<aux<<"'";
}
