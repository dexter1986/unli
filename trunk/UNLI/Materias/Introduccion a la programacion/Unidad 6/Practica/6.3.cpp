#include<cstdio>
#include<iostream>
#include<string.h>
#include<conio2.h>
#include<cstdlib>
#include<ctype.h>

using namespace std;

int cantidadVocales(const char *c);
int cantidadConsonantes(const char *c);
int cantidaLetras(const char *c);

int main(int argc,char *argv[])
{
	char word[255];
	
	cout<<"Ingrese una palabra: ";
	gets(word);
	word[254] = '\0';
	cout<<"Cantidad de vocales: "<<cantidadVocales((char *)word)<<endl;
	cout<<"Cantidad de consonantes: "<<cantidadConsonantes((char *)word)<<endl;
	cout<<"Cantida de letras: "<<cantidaLetras((char *)word)<<endl;
	return 0;
}

int cantidadVocales(const char *c)
{
	int cant = strlen(c);
	int cont=0;
	char aux;
	for(int i=0;i<cant;i++)
	{
		aux = tolower(c[i]);
		switch(aux)
		{
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				cont++;
				break;			
		}
	}
	return cont;
}

int cantidadConsonantes(const char *c)
{
	int cant = strlen(c);
	int cont=0;
	char aux;
	for(int i=0;i<cant;i++)
	{
		aux = tolower(c[i]);
		switch(aux)
		{
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
		case ' ':
			break;			
		default:			
			cont++;
		}
	}
	return cont;
}

int cantidaLetras(const char *c)
{
	int cant = strlen(c);
	int cont = 0;
	
	for(int i=0;i<cant;i++)
	{
		if(c[i] == ' ')
			continue;
		cont++;
	}	
	return cont;
}






