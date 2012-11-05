#include<cstdio>
#include<iostream>
#include<string.h>
#include<conio2.h>
#include<cstdlib>
#include<ctype.h>
#include<fstream>
#include<ctime>
#include<windows.h>

using namespace std;

int CargarPalabras(char **arr);
void presentacion();
void dibujarHorca();
void dibujarCabeza();
void dibujarBrazoIzq();
void dibujarBrazoDer();
void dibujaCuerpo();
void dibujarPiernaDer();
void dibujarPiernaIzq();
void mostrarPerdio();
void mostrarGano();
void dibujarPalabra(char *word);
int verificarAcierto(char a,char *palabra,char *letras,int &valor);
void MostrasLetras(char *letras);
void MostrarPalabra(char *palabra);
int contarLetras(char *palabra);

int main(int argc,char *argv[])
{
	char *palabras[255];
	int count = 0;
	char *palabra;
	char letras_elegidas[30];
	int men_count = 0;
		
	count = CargarPalabras(palabras);
	men_count = count;
	
	srand(time(NULL));
	
	count = rand()%count;
	
	palabra = new char[strlen(palabras[count])];
	strcpy(palabra,palabras[count]);
	
	
	for(int i=0;i<men_count;i++)
	{
		delete palabras[i];
	}
	
	
	palabra = strupr(palabra);
		
	int intentos = 0;
	bool salir = false;
	char letra;
	count = contarLetras(palabra);
	letras_elegidas[0] ='\0';
	
	presentacion();
	
	clrscr();
	
	dibujarHorca();
	dibujarPalabra(palabra);
	while(!salir)
	{
		gotoxy(50,4);
		cout<<"Letra: ";		
		
		letra = getch();
		
		cout<<letra;
		
		letra = toupper(letra);
		int ret = verificarAcierto(letra,palabra,letras_elegidas,count);
		MostrasLetras(letras_elegidas);
		if(ret == 2)
		{
			intentos++;			
			switch(intentos)
			{
			case 1:
				dibujarCabeza();
				break;
			case 2:
				dibujaCuerpo();
				break;
			case 3:
				dibujarBrazoIzq();
				break;
			case 4:
				dibujarBrazoDer();
				break;
			case 5:
				dibujarPiernaDer();
				break;
			case 6:
				dibujarPiernaIzq();
				MostrarPalabra(palabra);
				mostrarPerdio();			
				salir = true;
				break;
			}					
		}
		else if(ret == 0)
		{
			if(count==0)
			{
				mostrarGano();
				salir = true;
			}			
		}
	}
	clrscr();
	gotoxy(33,8);
	cout<<"GRACIAS POR JUGAR"<<endl<<endl<<endl;	
	Sleep(2000);
	
	return 0;
}

int contarLetras(char *palabra)
{
	int len = strlen(palabra);
	int cont = 0;
	for(int i=0;i<len;i++)
	{
		if(palabra[i] != ' ')
			cont++;
	}
	return cont;
}

int verificarAcierto(char a,char *palabra,char *letras,int &valor)
{
	int esAcierto = 2;
	int len;
		
	if(strchr(letras,a) == NULL)
	{				
		len = strlen(letras);
		*(letras+len) = a;
		letras[len+1] = '\0';		
	}
	else{
		gotoxy(50,5);
		cout<<"Esa letra ya fue elegida.";
		Sleep(1000);
		gotoxy(50,5);
		cout<<"                         ";
		return 1;
	}
	len = strlen(palabra);
	for(int i=0;i<len;i++)
	{	
		if(a == palabra[i])
		{
			valor--;
			gotoxy(40+(i*2),21);
			cout<<a;
			esAcierto = 0;
		}
	}	
	return esAcierto;
}

void MostrarPalabra(char *palabra)
{
	int len = strlen(palabra);
	for(int i=0;i<len;i++)
	{	
		gotoxy(40+(i*2),21);
		cout<<palabra[i];
	}
}

void MostrasLetras(char *letras)
{
	int len = strlen(letras);
	gotoxy(50,6);
	for(int i=0;i<len;i++)
	{
		cout<<letras[i]<<" ";
	}
}

void dibujarPalabra(char *word)
{
	int len = strlen(word);
	gotoxy(40,21);
	for(int i=0;i<len;i++)
	{
		if(word[i] != ' ')
			cout<<"_ ";		
		else
			cout<<"  ";
	}
}

void mostrarPerdio()
{
	gotoxy(34,7);
	cout<<"---------------";
	gotoxy(33,8);
	cout<<"|  PERDISTE..!! |";
	gotoxy(34,9);
	cout<<"---------------";
	gotoxy(80,25);
	Sleep(2500);
}

void mostrarGano()
{
	gotoxy(25,7);
	cout<<"-------------------------------";
	gotoxy(24,8);
	cout<<"|  FELICITACIONES, GANASTE..!!  |";
	gotoxy(25,9);
	cout<<"-------------------------------";
	gotoxy(80,25);
	Sleep(2500);
}

void dibujarPiernaDer()
{
	char tu = (char) 194;
	char lv = (char)179;
	char cbl = (char)192;
	char lh = (char)196;	
	
	gotoxy(41,13);
	cout<<tu;
	
	gotoxy(41,14);
	cout<<lv;
	gotoxy(41,15);
	cout<<lv;
	gotoxy(41,16);
	cout<<lv;
	gotoxy(41,17);
	cout<<lv;	
}

void dibujarPiernaIzq()
{	
	char tu = (char) 194;
	char lv = (char)179;
	char cbr = (char)217;
	char lh = (char)196;
	
	gotoxy(39,13);
	cout<<tu;
	
	gotoxy(39,14);
	cout<<lv;
	gotoxy(39,15);
	cout<<lv;
	gotoxy(39,16);
	cout<<lv;
	gotoxy(39,17);
	cout<<lv;	
}

void dibujarCabeza()
{
	char lh = (char)196;
	char lv = (char)179;
	char cur = (char)191;
	char cul = (char)218;
	char cbr = (char)217;
	char cbl = (char)192;
	char ldl = (char)96;
	char ldr = (char)96;
	gotoxy(38,4);
	cout<<cul<<lh<<lh<<lh<<cur;
	gotoxy(38,5);
	cout<<lv;
	gotoxy(42,5);
	cout<<lv;
	gotoxy(38,6);
	cout<<cbl<<lh<<lh<<lh<<cbr;
	gotoxy(40,7);
	cout<<lv;
	gotoxy(37,8);
	cout<<lh<<lh<<lh<<lh<<lh<<lh<<lh;
}

 void dibujaCuerpo()
 {
	 char lh = (char)196;
	 char lv = (char)179;
	 char cur = (char)191;
	 char cul = (char)218;
	 char cbr = (char)217;
	 char cbl = (char)192;
	 char tu = (char) 194;
	 gotoxy(42,8);	 
	 cout<<tu;
	 gotoxy(38,8);	 
	 cout<<tu; 
	 gotoxy(38,9);	 
	 cout<<lv<<"   "<<lv;
	 gotoxy(38,10);	 
	 cout<<lv<<"   "<<lv;
	 gotoxy(38,11);	 
	 cout<<lv<<"   "<<lv;
	 gotoxy(38,12);	 
	 cout<<lv<<"   "<<lv;
	 gotoxy(38,13);	 
	 cout<<cbl<<lh<<lh<<lh<<cbr;
	
 }

 void dibujarBrazoIzq()
 {
	 char lh = (char)196;
	 char lv = (char)179;
	 char cur = (char)191;
	 char cul = (char)218;
	 char cbr = (char)217;
	 char cbl = (char)192;
	 gotoxy(36,8);
	 cout<<cul;
	 gotoxy(36,9);
	 cout<<lv;
	 gotoxy(36,10);
	 cout<<lv;
	 gotoxy(36,11);
	 cout<<lv;
 }

 void dibujarBrazoDer()
 {
	 char lh = (char)196;
	 char lv = (char)179;
	 char cur = (char)191;
	 char cul = (char)218;
	 char cbr = (char)217;
	 char cbl = (char)192;
	 gotoxy(44,8);
	 cout<<cur;
	 gotoxy(44,9);
	 cout<<lv;
	 gotoxy(44,10);
	 cout<<lv;
	 gotoxy(44,11);
	 cout<<lv;
	 
 }

 void dibujarHorca()
 {
	char lh = (char)205;
	char lv = (char)186;
	char cur = (char)187;
	char cul = (char)201;
	
	
	gotoxy(32,2);
	cout<<lh<<lh<<lh<<lh<<lh<<lh<<lh<<lh<<cur;
	gotoxy(40,3);
	cout<<lv;
	gotoxy(32,2);
	cout<<cul;
	gotoxy(32,3);
	cout<<lv;
	gotoxy(32,4);
	cout<<lv;
	gotoxy(32,5);
	cout<<lv;
	gotoxy(32,6);
	cout<<lv;
	gotoxy(32,7);
	cout<<lv;
	gotoxy(32,8);
	cout<<lv;
	gotoxy(32,9);
	cout<<lv;
	gotoxy(32,10);
	cout<<lv;
	gotoxy(32,11);
	cout<<lv;
	gotoxy(32,12);
	cout<<lv;
	gotoxy(32,13);
	cout<<lv;
	gotoxy(32,14);	
	cout<<lv;	
	gotoxy(32,15);	
	cout<<lv;
	gotoxy(32,16);	
	cout<<lv;
	gotoxy(32,17);	
	cout<<lv;		
	gotoxy(31,18);
	cout<<lh<<lh<<lh;
	gotoxy(30,19);
	cout<<lh<<lh<<lh<<lh<<lh;	
 }

void presentacion()
{
	clrscr();
	gotoxy(32,10);
	cout<<"*****************";
	gotoxy(32,11);
	cout<<"*   AHORCADO    *";
	gotoxy(32,12);
	cout<<"*****************";
	gotoxy(55,22);
	cout<<"Oscar Sanchez - 2012";
	Sleep(200);	
	for(int i=0;i<3;i++)
	{
		gotoxy(55,22);
		cout<<"Oscar Sanchez - 2012";
		gotoxy(32,11);
		cout<<"*   -HORCADO    *";
		Sleep(200);	
		gotoxy(32,11);
		cout<<"*   --ORCADO    *";
		Sleep(200);	
		gotoxy(32,11);
		cout<<"*   A--RCADO    *";
		gotoxy(55,22);
		cout<<"                    ";		
		Sleep(200);	
		gotoxy(32,11);
		cout<<"*   AH--CADO    *";
		gotoxy(55,22);
		cout<<"Oscar Sanchez - 2012";
		Sleep(200);	
		gotoxy(32,11);
		cout<<"*   AHO--ADO    *";
		Sleep(200);	
		gotoxy(32,11);
		cout<<"*   AHOR--DO    *";
		Sleep(200);	
		gotoxy(32,11);
		cout<<"*   AHORC--O    *";
		gotoxy(55,22);
		cout<<"                    ";
		Sleep(200);	
		gotoxy(32,11);
		cout<<"*   AHORCA--    *";
		gotoxy(55,22);
		cout<<"Oscar Sanchez - 2012";
		Sleep(200);	
		gotoxy(32,11);
		cout<<"*   AHORCAD-    *";
		Sleep(200);	
		gotoxy(32,11);
		cout<<"*   AHORCADO    *";
		Sleep(200);	
	}
}

int CargarPalabras(char **arr)
{
	int count = 0;
	char aux[255];
	fstream file;
	file.open("6.10.txt",ios::in);
	while(!file.eof())
	{
		file.getline(aux,255);
		arr[count] = new char[strlen(aux)];
		strcpy(arr[count],aux);
		count++;
	}
	file.close();
	return count;
}
