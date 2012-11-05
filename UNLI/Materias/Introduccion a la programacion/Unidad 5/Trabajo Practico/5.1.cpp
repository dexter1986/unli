#include<iostream>
#include<constream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>

using namespace std;

int longitudCadena(char argv[]);
void concatenaCadena(char cadena1[], char cadena2[]);
int buscar(char cadena[],char caracter);

int main(int argc,char *argv[])
{
	char cadena[] = "Cadena de prueba";
	cout<<"La cadena '"<<cadena<<"' tiene "<<longitudCadena(cadena)<<" caracteres."<<endl;
	
	char cadena1[255] = "Hola";
	char cadena2[] = "Mundo";
	
	cout<<"Se concatena la palabra '"<<cadena1<<"' con '"<<cadena2<<"'.";
	concatenaCadena(cadena1,cadena2);
	cout<<" Resultado: '"<<cadena1<<"'"<<endl;
	
	char caracter = 'p';
	
	cout<<"Busca el caracter '"<<caracter<<"' en la cadena '"<<cadena<<"'. La posicion es "<<buscar(cadena,caracter)<<"."<<endl;
	
	system("PAUSE");
	return 0;
}

//Obtiene la longitud de la cadena. si es mayor de 255 devuelve -1
int longitudCadena(char argv[])
{
	int i = 0;
	
	while(argv[i] != '\0' || i > 255)
	{
		i++;
	}
	
	if(i>255)
		i = -1;
	
	return i;	
}

void concatenaCadena(char cadena1[], char cadena2[])
{
	int index1 = longitudCadena(cadena1);
	int index2 = longitudCadena(cadena2);
	
	if(index1 + index2 < 255)
	{
		cadena1[index1] = ' ';
		index1 +=1;
		
		for(int i=0;i<index2;i++)
		{
			cadena1[index1+i] = cadena2[i];
		}
	}
}
int buscar(char cadena[],char caracter)
{
	int index=0;
	while(cadena[index] != '\0' && index < 255)
	{
		if(cadena[index] == caracter)
			return index+1;
		index++;
	}
	
	return -1;	
}

