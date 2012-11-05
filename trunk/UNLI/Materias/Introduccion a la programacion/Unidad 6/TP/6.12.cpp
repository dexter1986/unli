#include<cstdio>
#include<iostream>
#include<string.h>
#include<conio2.h>
#include<cstdlib>
#include<ctype.h>
#include<ctime>
#include<fstream>

using namespace std;

int cargar(char* palabras[]);
void liberar(char* palabras[],int cant);
void mostrarVertical(char* palabra);
void mostrarPalabras(char* palabras[],int index,int cant);

int main(int argc,char *argv[])
{
	srand(time(NULL));
	char* palabras[100];
	int cantidad = cargar(palabras);
	
	int index = rand()%cantidad;
	
	gotoxy(36,2);
	
	cout<<"CRUCIGRAMA";
		
	mostrarVertical(palabras[index]);
	
	mostrarPalabras(palabras,index,cantidad);	
	
	liberar(palabras,cantidad);
	gotoxy(60,24);
	cout<<"Oscar Sanchez - 2012";
	gotoxy(1,25);
	system("PAUSE");	
	return 0;
}

void mostrarPalabras(char* palabras[],int index,int cant)
{
	char *palabra = palabras[index];
	int len = strlen(palabra);
	int len_aux;
	int cont;	
	int index_aux;
	bool isOK;
	char *aux;

	for(int i=0;i<len;i++)
	{
		for(int p=0;p<cant;p++)
		{
			if(p == index)
				continue;
		
			if(strchr(palabras[p],palabra[i]) != NULL)
			{
				isOK = false;
				index_aux = 0;
				len_aux = strlen(palabras[p]);				
						
				aux = new char[len_aux+3];
								
				for(int a=0;a<len_aux;a++)
				{
					if(!isOK && palabras[p][a] == palabra[i])
					{			
						
						aux[index_aux++] = (char)179;						
						aux[index_aux++] = palabras[p][a];
						aux[index_aux++] = (char)179;						
						cont = a+1;
						isOK = true;											
					}
					else
					{
						aux[index_aux++] = palabras[p][a];
					}							
				}
				
				aux[len_aux+2] = '\0';
				gotoxy(40-cont,5+i);
				cout<<aux;
				delete aux;
				palabras[p][0] = '\0';
				break;				
			}
		}		
	}
}

void mostrarVertical(char* palabra)
{
	int len = strlen(palabra);
	gotoxy(39,4);
	cout<<(char)218<<(char)196<<(char)191;
	for(int i=0;i<len;i++)
	{
		gotoxy(39,5+i);
		cout<<(char)179<<palabra[i]<<(char)179;
	}	
	gotoxy(39,5+len);	
	cout<<(char)192<<(char)196<<(char)217;
}

int cargar(char* palabras[])
{
	int cont = 0;
	char aux[255];
	fstream file;
	file.open("6.12.txt",ios::in);
	while(!file.eof())
	{
		file.getline(aux,255);
		palabras[cont] = new char[strlen(aux)+1];
		strcpy(palabras[cont],strupr(aux));
		cont++;
	}
	file.close();
	return cont;
}
void liberar(char* palabras[],int cant)
{
	for(int i=0;i<cant;i++)
	{
		delete palabras[i];
	}
}

