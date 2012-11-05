#include<cstdio>
#include<iostream>
#include<string.h>
#include<conio2.h>
#include<cstdlib>
#include<ctype.h>

using namespace std;

void generarMail(char *nombre,char *dominio);

int main(int argc,char *argv[])
{
	char **nombres;
	char aux[255];
	char *dominio = "@gmail.com";
	int count = 0;
	cout<<"Ingrese el nro de nombres a ingresar: ";
	cin>>aux;
	count = atoi(aux);
	cin.sync();
	
	nombres = new char*[count];
	
	for(int i=0;i<count;i++)
	{
		clrscr();
		cout<<"Ingrese apellido y nombre ("<<i+1<<" de "<<count<<") : ";		
		gets(aux);
		nombres[i] = new char[strlen(aux)];
		strcpy(nombres[i],aux);
	}
	clrscr();
	cout<<"Listado de emails"<<endl;
	for(int i=0;i<count;i++)
	{
		generarMail(nombres[i],dominio);
	}
	for(int i=0;i<count;i++)
	{
		delete nombres[i];
	}
	
	return 0;
}

void generarMail(char *usuario,char *dominio)
{
	int len = strlen(usuario);
	char *nombre = new char[len];
	char *apellido = new char[len];
	char *index;
	int ind = 0;
	index = apellido;
	
	for(int i=0;i<len;i++)
	{
		if(*(usuario+i) == ' ')
		{
			*(index+ind)= '\0';
			index = nombre;
			ind = 0;
			continue;
		}
		index[ind] = usuario[i];
		ind++;
	}
	
	*(index+ind)= '\0';
	
	cout<<nombre[0]<<apellido<<dominio<<endl;
	
	delete nombre;
	delete apellido;
}
















