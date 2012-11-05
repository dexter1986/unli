#include<cstdio>
#include<iostream>
#include<string.h>
#include<conio2.h>
#include<cstdlib>
#include<ctype.h>

using namespace std;

void mostrarMenu();

int main(int argc,char *argv[])
{
	bool salir = false;
	bool salir2 = false;
	char wd[255];
	char opcion;
	while(!salir)
	{
		clrscr();
		gotoxy(1,3);
		mostrarMenu();
		gotoxy(1,1);
		cout<<"Ingrese una palabra: ";
		gets(wd);		
		while(!salir2)
		{
			clrscr();
			gotoxy(1,1);
			cout<<"Palabra: "<<wd;
			gotoxy(1,3);
			mostrarMenu();
			opcion  = getch();

			switch(opcion)
			{
			case '1':
				strupr(wd);
				break;
			case '2':
				strlwr(wd);
				break;
			case '3':
				wd[0] = toupper(wd[0]);
				break;
			case '4':
				salir2 = true;
				break;
			}
		}
		salir2= false;		
	}
	return 0;
}

void mostrarMenu()
{
	cout<<"1. Pasar a mayusculas"<<endl<<"2. Pasar a minusculas"<<endl<<"3. Solo inicial la inicial con mayusculas"<<endl<<"4. Otra palabra.";	
}
