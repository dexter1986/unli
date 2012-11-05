#include<cstdio>
#include<iostream>
#include<string.h>
#include<conio2.h>
#include<cstdlib>
#include<ctype.h>
#include<fstream>

using namespace std;

void mostrarnombres(const char *c,int max);
void mostrarapellidos(const char *c,int max);

#define MAX 10
#define LEN 255

int main(int argc,char *argv[])
{
	char nom[MAX][LEN];
	//cout<<"Ingrese 10 nombres de persona con el formato nombre apellido"<<endl;
	fstream file;
	file.open("6.4 - a.txt",ios::in);
	for(int i=0;i<MAX;i++)
	{
		file.getline(nom[i],255);		
	}	
	file.close();
	cout<<endl;
	cout<<"Listado de nombres: "<<endl;
	mostrarnombres((char *)nom,MAX);
	cout<<endl<<"Listado de apellidos: "<<endl;
	mostrarapellidos((char *)nom,MAX);
	cout<<endl;
	return 0;
}

void mostrarnombres(const char *c,int max)
{	
	char aux[LEN];	
	int l=0;
	for(int i=0;i<max;i++)
	{
		for(int x=0;x<LEN;x++)
		{
			if(*(c+i*LEN+x) == ' ')
			{
				strncpy(aux,c+i*LEN,x);
				aux[x] = '\0';
				break;
			}
		}
		
		cout<<aux<<endl;
		
	}
}

void mostrarapellidos(const char *c,int max)
{ 
	for(int i=0;i<max;i++)
	{
		cout<<strchr(c+i*LEN,' ')+1<<endl;
	}	
}
