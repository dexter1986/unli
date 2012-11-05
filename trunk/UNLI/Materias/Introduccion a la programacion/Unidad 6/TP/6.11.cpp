#include<cstdio>
#include<iostream>
#include<string.h>
#include<conio2.h>
#include<iomanip>
#include<cstdlib>
#include<ctype.h>
#include<ctime>
#include<fstream>
#include<windows.h>

using namespace std;

enum sentido
{
	NADA=0,
	VER_U=1,
	VER_D=2,
	HOR_L=3,
	HOR_R=4,
	PRE=5
};

typedef struct {
	int len_palabras;
	char sopa[20][20];
	int sopa_ver[20][20];
	int count_palabras;
	char *palabras[5];
}sopa_def,*sopa_ptr;


typedef struct {	
	int cont;
	int ini_x;
	int ini_y;
	int fin_x;
	int fin_y;
	int pos_x,pos_y;
	sopa_ptr board;
}juego_def,*juego_ptr;

void liberar(juego_ptr juego);
void cargar(sopa_ptr sopa);
void mostrarSopa(sopa_ptr sopa);
void generar(sopa_ptr sopa);
void mostrarPalabras(sopa_ptr sopa);
void mostrarMenu();
void presentacion();
void ubicarPalabra(sopa_ptr sopa,int index,char *palabra);
int verificarPalabra(sopa_ptr sopa,char index,int ini,int fin,int coord,sentido sen);
void guardarjuego(juego_ptr juego);
void cargarJuego(juego_ptr juego);
void nuevaPartida(juego_ptr juego);

const char ENTER = (char)13;
const char ESPACIO = (char)32;
const char ESCAPE = (char)27;

const char KEY_LEFT  = (char)75;
const char KEY_RIGHT = (char)77;
const char KEY_UP =(char) 72;
const char KEY_DOWN =(char) 80;
const char F2 = (char) 60;
const char F3 = (char) 61;
const char F5 = (char) 63;

int main(int argc,char *argv[])
{
	srand(time(NULL));
	juego_def juego;
	
	juego.board = new sopa_def();
	
	cargar(juego.board);
	
	generar(juego.board);
	
	presentacion();
	gotoxy(60,24);
	cout<<"Oscar Sanchez - 2012";	
	gotoxy(33,1);
	cout<<"SOPA DE LETRAS";	
	mostrarSopa(juego.board);
	mostrarPalabras(juego.board);	
	mostrarMenu();
	
	bool salir = false;
	char aux;
	
	sentido sen = NADA;	
	int ret;	
	juego.cont = juego.board->count_palabras;
	juego.pos_x = 1;
	juego.pos_y = 1;
	
	while(!salir)
	{
		gotoxy(juego.pos_x+29,juego.pos_y+3);
		aux = getch();
		switch(aux)
		{
		case ENTER:
			if(sen == NADA)	
			{
				sen = PRE;
				juego.ini_x = juego.pos_x;
				juego.fin_x = juego.pos_x;
				juego.ini_y = juego.pos_y;
				juego.fin_y = juego.pos_y;
				textbackground(WHITE);
				textcolor(BLACK);
				cout<<juego.board->sopa[juego.pos_y-1][juego.pos_x-1];				
			}			
			else if( sen != PRE)
			{				
				normvideo();
				mostrarSopa(juego.board);
				sen = PRE;
				juego.ini_x = juego.pos_x;
				juego.fin_x = juego.pos_x;
				juego.ini_y = juego.pos_y;
				juego.fin_y = juego.pos_y;
				gotoxy(juego.pos_x+29,juego.pos_y+3);
				textbackground(WHITE);
				textcolor(BLACK);
				cout<<juego.board->sopa[juego.pos_y-1][juego.pos_x-1];
			}
			break;
		case F2:
			normvideo();
			nuevaPartida(&juego);
			sen = NADA;
			break;
		case F3:			
			normvideo();
			guardarjuego(&juego);
			break;
		case F5:
			normvideo();
			cargarJuego(&juego);			
			sen = NADA;
			clrscr();
			gotoxy(60,24);
			cout<<"Oscar Sanchez - 2012";	
			gotoxy(33,1);
			cout<<"SOPA DE LETRAS";
			mostrarSopa(juego.board);
			mostrarPalabras(juego.board);	
			mostrarMenu();
			break;	
		case ESPACIO:
			normvideo();
			sen = NADA;
			mostrarSopa(juego.board);
			break;
		case KEY_LEFT:
			if(sen != VER_U && sen != VER_D) 
			{
				juego.pos_x--;
				if(sen == PRE)
					sen = HOR_L;
			}
			break;
		case KEY_RIGHT:
			if(sen != VER_U && sen != VER_D) 
			{
				juego.pos_x++;
				if(sen == PRE)
					sen = HOR_R;
			}
			break;			
		case KEY_UP:
			if(sen != HOR_L && sen != HOR_R) 
			{
				juego.pos_y--;
				if(sen == PRE)
					sen = VER_U;
			}
			break;
		case KEY_DOWN:
			if(sen != HOR_L && sen != HOR_R) 
			{
				juego.pos_y++;
				if(sen == PRE)
					sen = VER_D;
			}
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':			
			normvideo();
			if(sen == VER_D || sen == VER_U)
			{
				ret = verificarPalabra(juego.board,aux,juego.ini_y,juego.fin_y,juego.ini_x,sen);
			}else
			{
			    ret = verificarPalabra(juego.board,aux,juego.ini_x,juego.fin_x,juego.ini_y,sen);
			}
			if(ret == 0)
			{
				juego.cont--;				
				mostrarSopa(juego.board);
				mostrarPalabras(juego.board);
				gotoxy(52,14);
				cout<<"Muy bien..!!";
				Sleep(1000);
				gotoxy(52,14);
				cout<<"                       ";				
				if(juego.cont<= 0)
					salir = true;
			}else if(ret == 1)
			{
				gotoxy(52,14);
				cout<<"Intentalo otra vez.";
				Sleep(1000);
				gotoxy(52,14);
				cout<<"                       ";
			}else{
				gotoxy(52,14);
				cout<<"Esa ya esta.";
				Sleep(1000);
				gotoxy(52,14);
				cout<<"                   ";
			}
			textbackground(WHITE);
			textcolor(BLACK);
			break;
		case ESCAPE:
			salir = true;
			break;
		}
		
		if(juego.pos_x>20)
			juego.pos_x = 20;
		else if(juego.pos_x<1)
			juego.pos_x = 1;
		
		if(juego.pos_y>20)
			juego.pos_y = 20;
		else if(juego.pos_y<1)
			juego.pos_y = 1;
		
		if(sen != NADA && sen != PRE)
		{				
			if(sen == VER_U)
			{
				if(juego.pos_y > juego.fin_y)					
				{
					normvideo();
					cout<<juego.board->sopa[juego.fin_y-1][juego.fin_x-1];	
				}				
			}
			else if(sen == VER_D)
			{
				if(juego.pos_y < juego.fin_y)
				{
					normvideo();
					cout<<juego.board->sopa[juego.fin_y-1][juego.fin_x-1];	
				}
			}else if(sen == HOR_L)
			{
				if(juego.pos_x > juego.fin_x)
				{
					normvideo();
					cout<<juego.board->sopa[juego.fin_y-1][juego.fin_x-1];	
				}
			}else if(sen == HOR_R)
			{
				if(juego.pos_x < juego.fin_x)				
				{
					normvideo();
					cout<<juego.board->sopa[juego.fin_y-1][juego.fin_x-1];	
				}
			}
			
			textbackground(WHITE);
			textcolor(BLACK);
			
			juego.fin_y = juego.pos_y;
			juego.fin_x = juego.pos_x;
					
			if(sen == VER_U && juego.ini_y < juego.fin_y)
			{
				sen = VER_D;
				gotoxy(juego.ini_x+29,juego.ini_y+3);
				cout<<juego.board->sopa[juego.ini_y-1][juego.ini_x-1];	
			}
			else if(sen == VER_D && juego.ini_y > juego.fin_y)
			{
				sen = VER_U;
				gotoxy(juego.ini_x+29,juego.ini_y+3);
				cout<<juego.board->sopa[juego.ini_y-1][juego.ini_x-1];	
			}
			else if(sen == HOR_L && juego.ini_x < juego.fin_x)
			{
				sen = HOR_R;
				gotoxy(juego.ini_x+29,juego.ini_y+3);
				cout<<juego.board->sopa[juego.ini_y-1][juego.ini_x-1];	
			}
			else if(sen == HOR_R && juego.ini_x > juego.fin_x)
			{
				sen = HOR_L;
				gotoxy(juego.ini_x+29,juego.ini_y+3);
				cout<<juego.board->sopa[juego.ini_y-1][juego.ini_x-1];	
			}
					
			gotoxy(juego.pos_x+29,juego.pos_y+3);
			cout<<juego.board->sopa[juego.pos_y-1][juego.pos_x-1];	
		}	
	}
	normvideo();
	clrscr();
	gotoxy(25,7);
	
	if(juego.cont == 0)
		cout<<"Felicitaciones, Ganaste...!!";
	else
	{
		cout<<"Te quedaron "<<juego.cont<<" palabras por descubrir";		
		gotoxy(25,8);
		cout<<"Intentalo otra vez.";
	}
	Sleep(3000);		
	liberar(&juego);	
	clrscr();
	gotoxy(33,7);
	cout<<"Gracias por jugar..!!";
	Sleep(800);	
	
	gotoxy(33,15);
	system("PAUSE");
	return 0;
}

void nuevaPartida(juego_ptr juego)
{
	clrscr();
	liberar(juego);	
	juego->board = new sopa_def();	
	cargar(juego->board);	
	generar(juego->board);
	
	juego->cont = juego->board->count_palabras;
	juego->pos_x = 1;
	juego->pos_y = 1;
	
	gotoxy(60,24);
	cout<<"Oscar Sanchez - 2012";	
	gotoxy(33,1);
	cout<<"SOPA DE LETRAS";
	mostrarSopa(juego->board);
	mostrarPalabras(juego->board);	
	mostrarMenu();
}

void guardarjuego(juego_ptr juego)
{
	gotoxy(52,14);
	cout<<"Guardando...";	
	fstream file;
	file.open("6.11.save",ios::binary|ios::trunc|ios::out);
	
	file.write((const char*) juego,sizeof(juego_def));
	file.write((const char*)juego->board,sizeof(sopa_def));
	
	for(int i=0;i<juego->board->count_palabras;i++)
	{
		file.write((const char*)juego->board->palabras[i],sizeof(char)*50);
	}
	
	file.close();
	Sleep(1000);
	gotoxy(52,14);
	cout<<"                       ";
}

void cargarJuego(juego_ptr juego)
{
	gotoxy(52,14);
	cout<<"Cargando...";	
	fstream file;
	file.open("6.11.save",ios::binary|ios::in);
	
	for(int i=0;i<juego->board->count_palabras;i++)
	{
		delete juego->board->palabras[i];
	}
	
	delete juego->board;
	
	file.read((char*)juego,sizeof(juego_def));
	
	juego->board = new sopa_def();
	file.read((char*)juego->board,sizeof(sopa_def));
	
	for(int i=0;i<juego->board->count_palabras;i++)
	{
		juego->board->palabras[i] = new char[50];
	    file.read((char*)juego->board->palabras[i],sizeof(char)*50);
	}
	
	file.close();
	Sleep(1000);
	gotoxy(52,14);
	cout<<"                       ";
}

int verificarPalabra(sopa_ptr sopa,char index,int ini,int fin,int coord,sentido sen)
{
	int ret = 1;	
	int aux ;
	int car = atoi(&index)-1;
	int len = strlen(sopa->palabras[car]);
	
	if(ini>fin)
	{
		aux = ini;
		ini = fin;
		fin = aux;
	}
	
	if(abs(ini-fin)+1 != len)
	{
		return 1;
	}
	
	if(sen == VER_U || sen == VER_D)
	{
		if(sopa->sopa_ver[ini-1][coord-1] == car && sopa->sopa_ver[fin-1][coord-1] == car)
		{
			ret = 0;
			for(int i=0;i<len;i++)
			{
				sopa->sopa[i+ini-1][coord-1] = index;
			}
		}
	}else
	{
		if(sopa->sopa_ver[coord-1][ini-1] == car && sopa->sopa_ver[coord-1][fin-1] == car)
		{
			ret = 0;
			for(int i=0;i<len;i++)
			{
				sopa->sopa[coord-1][i+ini-1] = index;
			}
		}
	}
	
	if(ret == 0)
	{
		sopa->palabras[car][len] = ' ';
		sopa->palabras[car][len+1] = '<';
		sopa->palabras[car][len+2] = '-';
		sopa->palabras[car][len+3] = '-';		
	}
	
	return ret;
}

void presentacion()
{
	clrscr();
	char rot[5][15] = {{'A','W','D','F','X','V','Z','G','H','M','A','W','L','N','\0'},
		               {'U','T','E','Q','X','B','H','J','F','W','T','K','J','M','\0'},
		               {'C','H','J','W','I','M','A','W','O','R','P','K','V','P','\0'},
		               {'S','O','P','A',' ','D','E',' ','L','E','T','R','A','S','\0'},
					   {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'}
					};
	int count_x = 0;
	int count = 0;
	gotoxy(50,20);
	cout<<"Oscar Sanchez - 2012";
	
	while(count_x<15)
	{
		gotoxy(33+count_x,5);
		for(int x=count_x;x<14;x++)
		{
			cout<<rot[rand()%4][rand()%14];		
		}
		
		if(rand()%10==0)
		{
			gotoxy(33+count_x,5);
			cout<<rot[3][count_x];
			count_x++;
		}		
		Sleep(50);
		if(count == 7)
		{	
			gotoxy(50,20);
			cout<<"Oscar Sanchez - 2012";			
		}else if(count == 35)
		{
			count = 0;
			gotoxy(50,20);
			cout<<"                    ";
		}
		count++;
	}
	
	gotoxy(50,20);
	cout<<"Oscar Sanchez - 2012";
	
	gotoxy(33,5);
	cout<<rot[3];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[4];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[3];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[4];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[3];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[4];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[3];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[4];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[3];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[4];
	Sleep(300);
	gotoxy(33,5);
	cout<<rot[3];
	gotoxy(80,25);
	Sleep(2000);
	clrscr();
}

void generar(sopa_ptr sopa)
{
	for(int y=0;y<20;y++)
	{
		for(int x=0;x<20;x++)
		{
			sopa->sopa[y][x] = rand()%25+65;
			sopa->sopa_ver[y][x] = -1;
		}
	}
	
	for(int i=0;i<sopa->count_palabras;i++)
	{
		ubicarPalabra(sopa,i,sopa->palabras[i]);		
	}	
}

void ubicarPalabra(sopa_ptr sopa,int index,char *palabra)
{
	bool isVertical;
	int ini_x,ini_y;
	bool salir = false;
	bool flag = false;
	int count = sopa->count_palabras;
	int len = strlen(palabra);
	
	while(!salir)
	{
		isVertical = rand()%2==1;
		ini_x = rand()%20;
		ini_y = rand()%20;
		flag = false;
		if(isVertical)
		{
			if(ini_y+len<20)
			{
				for(int y=0;y<len;y++)
				{
					if(sopa->sopa_ver[y+ini_y][ini_x] != -1)
					{
						flag = true;
						break;
					}
				}
			}else
			{
				flag = true;
			}
		}
		else
		{
			if(ini_x+len<20)
			{
				for(int x=0;x<len;x++)
				{
					if(sopa->sopa_ver[ini_y][x+ini_x] != -1)
					{
						flag = true;
						break;
					}
				}
			}else
			{
				flag = true;
			}
		}
		if(!flag)
		{
			salir=true;
			if(isVertical)
			{
				for(int y=0;y<len;y++)
				{
					sopa->sopa[y+ini_y][ini_x] = toupper(palabra[y]);
					sopa->sopa_ver[y+ini_y][ini_x] = index;
				}
			}else
			{
				for(int x=0;x<len;x++)
				{
					sopa->sopa[ini_y][x+ini_x] = toupper(palabra[x]);
					sopa->sopa_ver[ini_y][x+ini_x] = index;
				}
			}
		}
	}	
}

void mostrarPalabras(sopa_ptr sopa)
{
	for(int i=0;i<sopa-> count_palabras;i++)
	{
		gotoxy(5,5+i);
		cout<<i+1<<". "<<sopa->palabras[i];
	}
}

void mostrarMenu()
{
	gotoxy(52,5);
	cout<<"Enter: Selecciona.";
	gotoxy(52,6);
	cout<<"Flechas: Extiende seleccion.";
	gotoxy(52,7);
	cout<<"1 al 5: Selecciona palabra.";
	gotoxy(52,8);
	cout<<"Espacio: Limpiar.";
	gotoxy(52,9);
	cout<<"F2: Nueva Partida.";
	gotoxy(52,10);
	cout<<"F3: Guardar Partida.";
	gotoxy(52,11);
	cout<<"F5: Cargar Partida.";
	gotoxy(52,12);
	cout<<"Escape: Salir.";
}

void mostrarSopa(sopa_ptr sopa)
{
	gotoxy(29,3);	
	cout<<(char)218<<setw(21)<<setfill((char)196)<<(char)191;
	for(int y=0;y<20;y++)
	{	
		gotoxy(29,4+y);
		cout<<(char)179;
		for(int x=0;x<20;x++)
		{
			cout<<sopa->sopa[y][x];
		}		
		cout<<(char)179;
	}
	gotoxy(29,24);	
	cout<<(char)192<<setw(21)<<setfill((char)196)<<(char)217;
}

void liberar(juego_ptr juego)
{
	for(int i=0;i<juego->board->count_palabras;i++)
	{
		delete juego->board->palabras[i];
	}
	
	delete juego->board;
}
void cargar(sopa_ptr sopa)
{
	sopa->count_palabras = 0;
	sopa->len_palabras = 0;
	fstream file;
	file.open("6.10.txt",ios::in);
	char aux[255];
	int len;
	while(!file.eof() && sopa->count_palabras < 5)
	{
		sopa->count_palabras++;
		file.getline(aux,255);
		len = strlen(aux);
		sopa->palabras[sopa->count_palabras-1] = new char[50];
		strcpy(sopa->palabras[sopa->count_palabras-1],aux);		
		sopa->len_palabras += 50;
		
		sopa->palabras[sopa->count_palabras-1][len] = '\0';
		sopa->palabras[sopa->count_palabras-1][len+1] = ' ';
		sopa->palabras[sopa->count_palabras-1][len+2] = ' ';
		sopa->palabras[sopa->count_palabras-1][len+3] = ' ';
		sopa->palabras[sopa->count_palabras-1][len+4] = '\0';
		
	}
	file.close();
}
