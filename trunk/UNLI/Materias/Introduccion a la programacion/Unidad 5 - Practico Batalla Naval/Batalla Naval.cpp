#include<iostream>
#include<constream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

#define TABLERO 10
#define MAQUINA_INDEX 0
#define JUGADOR_INDEX 1

const char KEY_LEFT  = 75;
const char KEY_RIGHT = 77;
const char KEY_UP = 72;
const char KEY_DOWN = 80;
const char KEY_ENTER = 13;


enum TIPO_BARCO
{
	NADA = 0,
	AGUA = -1,
	AVERIADO = 1,
	FRAGATA = 2,
	SUBMARINO = 3,
	ACORAZADO = 4,	
	DESTRUCTOR = 5,
	HUNDIDO = 6
};

typedef struct{
	int tablero [TABLERO][TABLERO];	
	int cont_submarino;
	int cont_destructor;
	int cont_acorazado;
	int cont_fragata;
}jugador;

void inicializarJugador(jugador &j);
void generaTablero(int tablero[TABLERO][TABLERO]);
void generaTableroGrafico(jugador &j);
void dibujarTableros(jugador arr[]);
void dibujarTablero(jugador j,bool mostrar = false);
char convert_celda(int cell,bool mostrar = false);
bool validaUbicacion(int pos_x,int pos_y,TIPO_BARCO tipo,bool vertical,int tablero[TABLERO][TABLERO]);
void mostrarTurno(bool jugador);
void presentacion();
TIPO_BARCO procesaJugada(int pos_x,int pos_y,jugador &j);
bool computarAcierto(TIPO_BARCO tipo,jugador &j);
int GetPos(char letra);
void AIPos(int &pos_x,int &pos_y);
void imp_caract(char letra,int total,int cant);
bool buscarGanador(jugador arr[]);
void SetAIPos(int pos_x,int pos_y,TIPO_BARCO tipo);

bool _modo_debug = false;
bool _modo_auto = false;
bool _isDificultad_Facil = false;
bool turno_jugador = true;

jugador AI_j;
jugador AI_maq;
int old_pos_maq_X = 0,old_pos_maq_Y = 0;
int old_pos_jug_X = 0,old_pos_jug_Y = 0;
int cont_AI_maq=0;
int cont_AI_jug=0;

int main(int argc,char *argv[])
{	
	inicializarJugador(AI_j);
	inicializarJugador(AI_maq);
	
	int ret;
	int pos_x,pos_y;
	int pos_nro=0;
	char pos_letra = ' ';	
		
	srand(time(NULL));	
	
	presentacion();
		
	clrscr();
			
	jugador jugadores[2];
	
	inicializarJugador(jugadores[MAQUINA_INDEX]);
	inicializarJugador(jugadores[JUGADOR_INDEX]);
		
	generaTablero(jugadores[MAQUINA_INDEX].tablero);
	char sel;
	
	gotoxy(35,3);
	cout<<"BATALLA NAVAL";
	gotoxy(3,8);
	cout<<"Desea armar el tablero de forma automatica?";
	gotoxy(33,9);
	cout<<"si[s]/no[n] ";
	cin>>sel;
	
	if(sel == 's' || sel == 'S')
		generaTablero(jugadores[JUGADOR_INDEX].tablero);
	else
		generaTableroGrafico(jugadores[JUGADOR_INDEX]);
	
	clrscr();
	gotoxy(35,3);
	cout<<"BATALLA NAVAL";
	gotoxy(3,8);
	cout<<"Elija el nivel de dificultad:";
	gotoxy(11,9);	
	cout<<"Facil[f] - Normal[n] ";	
	cin>>sel;
	
	if(sel == 'f' || sel == 'F')
		_isDificultad_Facil = true;
	
	clrscr();
	gotoxy(35,3);
	cout<<"BATALLA NAVAL";
	gotoxy(34,5);
	cout<<"MODO SIMULACION";
	gotoxy(3,8);
	cout<<"Desea que la maquina juegue por ud.?";
	gotoxy(26,9);
	cout<<"si[s]/no[n] ";	
	cin>>sel;
	
	if(sel == 's' || sel == 's')
	{
		_modo_auto = true;
		clrscr();
		gotoxy(35,3);
		cout<<"BATALLA NAVAL";
		gotoxy(34,5);
		cout<<"MODO SIMULACION";
		gotoxy(3,8);
		cout<<"Desea ver el tablero de la maquina?";
		gotoxy(25,9);
		cout<<"si[s]/no[n] ";	
		cin>>sel;
		if(sel == 's' || sel == 's')
		{
			_modo_debug = true;
		}
	}
	
	while(true)
	{	
		clrscr();
		//Comienza la partida
		dibujarTableros(jugadores);
		
		mostrarTurno(turno_jugador);
		
		if(turno_jugador)
		{
			if(!_modo_auto)
			{
				cin>>pos_letra;
				cin>>pos_nro;
				
				pos_x = GetPos(pos_letra);	
				pos_y =  pos_nro - 1;	
				if(pos_y < 0 || pos_x < 0 )
				{
					gotoxy(35,8);
					cout<<"Posicion no valida.";
					gotoxy(35,9);
					cout<<"Intentelo otra vez";
					Sleep(1000);
					continue;
				}
				
				//Borra el buffer del teclado
				cin.clear();
				cin.sync();
			}else
			{
				Sleep(500);
				gotoxy(33,6);
				cout<<" PENSANDO...     ";
				gotoxy(33,7);				
				cout<<"                 ";
				Sleep(500);
				AIPos(pos_x,pos_y);				
				gotoxy(39,7);
				cout<<(char)(pos_x+65)<<pos_y+1;				
				Sleep(1000);
			}
			//Validar posicion
			ret = procesaJugada(pos_x,pos_y,jugadores[MAQUINA_INDEX]);
		}else
		{	
			Sleep(500);
			gotoxy(34,6);
			cout<<"PENSANDO...";
			Sleep(500);			
			AIPos(pos_x,pos_y);		
			gotoxy(33,7);
			cout<<"                 ";
			gotoxy(39,7);					
			cout<<(char)(pos_x+65)<<pos_y+1;			
			//Validar posicion			
			Sleep(1000);
			ret = procesaJugada(pos_x,pos_y,jugadores[JUGADOR_INDEX]);
		}
		SetAIPos(pos_x,pos_y,(TIPO_BARCO)ret);				
		gotoxy(33,6);		
		cout<<"                ";	
		gotoxy(35,7);		
		cout<<"             ";		
		switch(ret)
		{
			case NADA:
				gotoxy(35,6);
				cout<<"Ese lugar ya fue seleccionado.";
				gotoxy(35,7);		
				//cout<<"FRASE";
				break;
			case AGUA:
				gotoxy(39,6);
				cout<<"AGUA";
				gotoxy(35,7);
				//cout<<"FRASE";
				turno_jugador = !turno_jugador;
				break;
			case AVERIADO:
				gotoxy(37,6);
				cout<<"AVERIADO";
				gotoxy(35,7);
				//cout<<"FRASE";
				turno_jugador = !turno_jugador;
				break;
			case HUNDIDO:
				gotoxy(37,6);
				cout<<"HUNDIDO";
				gotoxy(35,7);
				//cout<<"FRASE";
				turno_jugador = !turno_jugador;
				break;
		}
		Sleep(1000);
		if(buscarGanador(jugadores))		
			break;
	}	
	cout<<setw(51)<<"Gracias por jugar"<<endl<<endl;
	cout<<endl<<endl;
	system("PAUSE");
	return 0;
}

bool buscarGanador(jugador arr[])
{
	if(arr[MAQUINA_INDEX].cont_acorazado == 0 && arr[MAQUINA_INDEX].cont_destructor == 0 
		   && arr[MAQUINA_INDEX].cont_fragata == 0 && arr[MAQUINA_INDEX].cont_submarino == 0)
		{
			gotoxy(35,6);
			cout<<"GANA EL HUMANO";
			Sleep(1000);
			clrscr();
			gotoxy(37,6);
			cout<<"GANA EL HUMANO"<<endl<<endl;
			return true;
		}
	else if(arr[JUGADOR_INDEX].cont_acorazado == 0 && arr[JUGADOR_INDEX].cont_destructor == 0 
	&& arr[JUGADOR_INDEX].cont_fragata == 0 && arr[JUGADOR_INDEX].cont_submarino == 0)
	{
		gotoxy(37,6);
		cout<<"GANA LA MAQUINA";
		Sleep(1000);
		clrscr();
		gotoxy(37,6);
		cout<<"GANA LA MAQUINA"<<endl<<endl;
		return true;
	}
	return false;
}



void AIPos(int &pos_x,int &pos_y)
{
	if(_isDificultad_Facil)
	{
		pos_x = rand()%10;
		pos_y = rand()%10;
	}else
	{
		if(turno_jugador)
		{			
			if(AI_j.tablero[old_pos_jug_Y][old_pos_jug_X] == AVERIADO)
			{
				if(old_pos_jug_Y+1<TABLERO && AI_j.tablero[old_pos_jug_Y+1][old_pos_jug_X] == NADA){					
					pos_x = old_pos_jug_X;
					pos_y = old_pos_jug_Y+1;
					cont_AI_jug++;
					return;
				}
				
				if(old_pos_jug_Y-1 >= 0 && AI_j.tablero[old_pos_jug_Y-1][old_pos_jug_X] == NADA)
				{					
					pos_x = old_pos_jug_X;
					pos_y = old_pos_jug_Y-1;
					cont_AI_jug++;
					return;
				}
				
				if(old_pos_jug_X+1 < TABLERO && AI_j.tablero[old_pos_jug_Y][old_pos_jug_X+1] == NADA)
				{					
					pos_x = old_pos_jug_X+1;
					pos_y = old_pos_jug_Y;
					cont_AI_jug++;
					return;
				}
				
				if(old_pos_jug_X-1 >= 0 && AI_j.tablero[old_pos_jug_Y][old_pos_jug_X-1] == NADA)
				{
					pos_x = old_pos_jug_X-1;
					pos_y = old_pos_jug_Y;
					cont_AI_jug++;
					return;
				}		
				cont_AI_jug = 0;
			}
			
			pos_x = rand()%10;
			pos_y = rand()%10;
			if(AI_j.tablero[pos_y][pos_x] != NADA)
			{
				for(int i=0;i<TABLERO;i++)
				{
					for(int x=0;x<TABLERO;x++)
					{
						if(AI_j.tablero[i][x] == NADA)
						{						
							pos_x = x;
							pos_y = i;
							return;
						}
					}
				}
			}		
		}else
		{			
			if(AI_maq.tablero[old_pos_maq_Y][old_pos_maq_X] == AVERIADO)
			{
				if(old_pos_maq_Y+1<TABLERO && AI_maq.tablero[old_pos_maq_Y+1][old_pos_maq_X] == NADA){					
					pos_x = old_pos_maq_X;
					pos_y = old_pos_maq_Y+1;
					cont_AI_maq++;
					return;
				}
					
				if(old_pos_maq_Y-1 >= 0 && AI_maq.tablero[old_pos_maq_Y-1][old_pos_maq_X] == NADA)
				{
					pos_x = old_pos_maq_X;
					pos_y = old_pos_maq_Y-1;
					cont_AI_maq++;
					return;
				}
				
				if(old_pos_maq_X+1 < TABLERO && AI_maq.tablero[old_pos_maq_Y][old_pos_maq_X+1] == NADA)
				{
					pos_x = old_pos_maq_X+1;
					pos_y = old_pos_maq_Y;
					cont_AI_maq++;
					return;
				}
				
				if(old_pos_maq_X-1 >= 0 && AI_maq.tablero[old_pos_maq_Y][old_pos_maq_X-1] == NADA)
				{
					pos_x = old_pos_maq_X-1;
					pos_y = old_pos_maq_Y;
					cont_AI_maq++;
					return;
				}
				cont_AI_maq = 0;
			}
			
			pos_x = rand()%10;
			pos_y = rand()%10;
			if(AI_maq.tablero[pos_y][pos_x] != NADA)
			{
				for(int i=0;i<TABLERO;i++)
				{
					for(int x=0;x<TABLERO;x++)
					{
						  if(AI_maq.tablero[i][x] == NADA)
						  {
							  pos_x = x;
							  pos_y = i;
							  return;
						  }
					}
				}
			}			
		}
	}
}

void SetAIPos(int pos_x,int pos_y,TIPO_BARCO tipo) 
{
	if(turno_jugador)
	{
		AI_j.tablero[pos_y][pos_x] = tipo;
		
		if(cont_AI_jug >=4 || tipo == HUNDIDO)
			cont_AI_jug = 0;
		
		if(tipo == AVERIADO || cont_AI_jug == 0)
		{
			old_pos_jug_X = pos_x;
			old_pos_jug_Y = pos_y;
		}
		
	}else
	{
		AI_maq.tablero[pos_y][pos_x] = tipo;
		
		if(cont_AI_maq>=4 || tipo == HUNDIDO)
			cont_AI_maq = 0;
		
		if(tipo == AVERIADO || cont_AI_maq == 0)
		{
			old_pos_maq_X = pos_x;
			old_pos_maq_Y = pos_y;
		}
		
	}
}

int GetPos(char letra)
{
	switch(letra)
	{
	case 'A':
	case 'a':
		return 0;
	case 'B':
	case 'b':
		return 1;
	case 'C':
	case 'c':
		return 2;
	case 'D':
	case 'd':
		return 3;
	case 'E':
	case 'e':
		return 4;
	case 'F':
	case 'f':
		return 5;
	case 'G':
	case 'g':
		return 6;
	case 'H':
	case 'h':
		return 7;
	case 'I':
	case 'i':
		return 8;
	case 'J':
	case 'j':
		return 9;
	default:
		return -1;
	}
}

TIPO_BARCO procesaJugada(int pos_x,int pos_y,jugador &j)
{
	if(pos_x<TABLERO && pos_y < TABLERO)
	{
		TIPO_BARCO tipo =(TIPO_BARCO) j.tablero[pos_x][pos_y];
		switch(tipo)
		{
			case NADA:
				j.tablero[pos_x][pos_y] = AGUA;
				return AGUA;				
			case AVERIADO:
			case AGUA:
				return NADA;				
			default:
				j.tablero[pos_x][pos_y] = AVERIADO;
				if(computarAcierto(tipo,j))
					return HUNDIDO;
				else
					return AVERIADO;
		}		
	}
	
	return NADA;
}

bool computarAcierto(TIPO_BARCO tipo,jugador &j)
{
	switch(tipo)
	{
		case FRAGATA:
			j.cont_fragata--;
			if(j.cont_fragata == 0)
				return true;
			break;
		case SUBMARINO:
			j.cont_submarino--;
			if(j.cont_submarino == 0)
				return true;
			break;
		case ACORAZADO:
			j.cont_acorazado--;
			if(j.cont_acorazado == 0)
				return true;
			break;
		case DESTRUCTOR:
			j.cont_destructor--;
			if(j.cont_destructor == 0)
				return true;
			break;		
	}
	return false;
}

void presentacion()
{
	clrscr();
	bool flag= true;
	
	char c_ldw = 192;
	char c_rdw = 217;
	char c_rup = 191;
	char c_lup = 218;
	char lr = 179;
	
	for(int i=0;i<10;i++)
	{
		gotoxy(31,8);
		
		if(flag)
		{
		    cout<<"*-*-*-*-*-*-*-*-*";
			gotoxy(31,9);
			cout<<lr<<"               "<<lr;
			gotoxy(31,10);
			cout<<"*               *";
			gotoxy(31,11); 
			cout<<lr<<"               "<<lr;
			gotoxy(31,12);
			cout<<"*"<<"-*-*-*-*-*-*-*-*";
		}
		else	
		{
			cout<<c_lup<<"*-*-*-*-*-*-*-*"<<c_rup;
			gotoxy(31,9);
			cout<<"*               *";
			gotoxy(31,10); 
			cout<<lr<<"               "<<lr;
			gotoxy(31,11);
			cout<<"*               *";
			gotoxy(31,12);
			cout<<c_ldw<<"*-*-*-*-*-*-*-*"<<c_rdw;
		}
		
		gotoxy(33,10);
		cout<<"BATALLA NAVAL";	
		
		flag = !flag;
		
		Sleep(200);
	}
	
	gotoxy(30,20);
	cout<<"Oscar Sanchez - 2012";
	Sleep(300);
	gotoxy(30,20);
	cout<<"                    ";
	Sleep(300);
	gotoxy(30,20);
	cout<<"Oscar Sanchez - 2012";
	Sleep(300);
	gotoxy(30,20);
	cout<<"                    ";
	Sleep(300);
	gotoxy(30,20);
	cout<<"Oscar Sanchez - 2012";
	Sleep(300);
	gotoxy(30,20);
	cout<<"                    ";
	Sleep(300);
	gotoxy(30,20);
	cout<<"Oscar Sanchez - 2012";
	Sleep(800);
}

void mostrarTurno(bool jugador)
{
	if(jugador)
	{
		gotoxy(35,5);
		cout<<"JUEGA HUMANO";
		gotoxy(33,6);
		cout<<"INGRESE POSICION";	
		gotoxy(35,7);
		cout<<"ej.(A1): ";
	}else
	{
		gotoxy(35,5);
		cout<<"JUEGA MAQUINA";					
	}
}

void dibujarTableros(jugador arr[])
{
	//Imprime el titul0
	gotoxy(1,1);	
	cout<<setw(24)<<"MAQUINA";
	cout<<setw(22)<<"BATALLA NAVAL"<<setw(19)<<"HUMANO";
	cout<<endl;
	
	//Imprime la linea divisoria
	for(int i=0;i<22;i++)
	{
		cout<<setw(40)<<(char)186<<endl;
	}
	
	//Imprime el pie de la pantalla
	gotoxy(1,24);
	cout<<"  [";
	imp_caract('S',SUBMARINO,arr[0].cont_submarino);
	cout<<"]    [";
	imp_caract('D',DESTRUCTOR,arr[0].cont_destructor);
	cout<<"]    [";
	imp_caract('A',ACORAZADO,arr[0].cont_acorazado);
	cout<<"]    [";
	imp_caract('F',FRAGATA,arr[0].cont_fragata);
	cout<<"] ";
	cout<<"  "<<(char)186<<" ";
	
	cout<<"  [";
	imp_caract('S',SUBMARINO,arr[1].cont_submarino);
	cout<<"]    [";
	imp_caract('D',DESTRUCTOR,arr[1].cont_destructor);
	cout<<"]    [";
	imp_caract('A',ACORAZADO,arr[1].cont_acorazado);
	cout<<"]    [";
	imp_caract('F',FRAGATA,arr[1].cont_fragata);
	cout<<"] ";
	cout<<endl;
		
	cout<<"Submarino Destructor Acorazado Fragata";
	cout<<" "<<(char)186;
	cout<<" Submarino Destructor Acorazado Fragata";
	
	Sleep(100);
	//Imprimir tableros	
	gotoxy(42,2);
	dibujarTablero(arr[JUGADOR_INDEX],true);
	
	gotoxy(1,2);
	dibujarTablero(arr[MAQUINA_INDEX],_modo_debug);
}

void imp_caract(char letra,int total,int cant)
{
	for(int i=0;i<total;i++)
	{
		if(cant>0)
			cout<<letra;
		else
			cout<<'X';
		cant--;
	}
}

void dibujarTablero(jugador j,bool mostrar)
{
	
	int pos_x = wherex();
	int pos_y = wherey();
	
	char t_up = 194;
	char t_dw = 193;	
	char ln = 196;
	char lr = 179;
	char c_rup = 191;
	char c_lup = 218;
	char m_r = 180;
	char m_l = 195;
	char c_rdw = 217;
	char c_ldw = 192;
	char lt =  197;
	
	gotoxy(pos_x+10,pos_y);
	
	cout<<c_lup;
	cout<<ln<<t_up<<ln<<t_up<<ln<<t_up<<ln<<t_up<<ln<<t_up<<ln<<t_up<<ln<<t_up<<ln<<t_up<<ln<<t_up<<ln<<c_rup<<endl;
	
	gotoxy(pos_x,pos_y++);
	
	for(int x=0;x<TABLERO;x++)
	{
		gotoxy(pos_x+8,pos_y);
		cout<<(char)(65+x)<<" ";
		cout<<lr;		
		cout<<convert_celda(j.tablero[x][0],mostrar)<<lr;
		cout<<convert_celda(j.tablero[x][1],mostrar)<<lr;
		cout<<convert_celda(j.tablero[x][2],mostrar)<<lr;
		cout<<convert_celda(j.tablero[x][3],mostrar)<<lr;
		cout<<convert_celda(j.tablero[x][4],mostrar)<<lr;
		cout<<convert_celda(j.tablero[x][5],mostrar)<<lr;
		cout<<convert_celda(j.tablero[x][6],mostrar)<<lr;
		cout<<convert_celda(j.tablero[x][7],mostrar)<<lr;
		cout<<convert_celda(j.tablero[x][8],mostrar)<<lr;
		cout<<convert_celda(j.tablero[x][9],mostrar)<<lr<<endl;
		
		gotoxy(pos_x,pos_y++);
		
		if(x<TABLERO-1){
			gotoxy(pos_x+10,pos_y);
			cout<<m_l;
			cout<<ln<<lt<<ln<<lt<<ln<<lt<<ln<<lt<<ln<<lt<<ln<<lt<<ln<<lt<<ln<<lt<<ln<<lt<<ln<<m_r<<endl;
			gotoxy(pos_x,pos_y++);
		}
		
	}	
	gotoxy(pos_x+10,pos_y++);
	cout<<c_ldw;
	cout<<ln<<t_dw<<ln<<t_dw<<ln<<t_dw<<ln<<t_dw<<ln<<t_dw<<ln<<t_dw<<ln<<t_dw<<ln<<t_dw<<ln<<t_dw<<ln<<c_rdw<<endl;
	gotoxy(pos_x+10,pos_y++);
	cout<<" 1 2 3 4 5 6 7 8 9 10"<<endl;
	gotoxy(pos_x,pos_y++);
}

char convert_celda(int cell,bool mostrar)
{
	switch(cell)
	{
		case AGUA:
			return 'O';
		case AVERIADO:		
			return 'X';		
	}
	
	if(mostrar)
	{
		switch(cell)
		{
			case FRAGATA:
				return 'F';
			case SUBMARINO:
				return 'S';
			case ACORAZADO:
				return 'A';
			case DESTRUCTOR:
				return 'D';			
		}
	}
	return ' ';
}

void generaTableroGrafico(jugador &j)
{
	int pos_x = 0;
	int pos_y = 0;
		
	bool isSubmarino = false;
	bool isAcorazado = false;
	bool isFragata = false;
	bool isDestructor = false;
	bool isVertical = true;
	char letra;
	TIPO_BARCO current;
	int index = 0;
	
	jugador j_temp;
	
	while(index<4)
	{
		clrscr();
		gotoxy(35,2);
		cout<<"BATALLA NAVAL";
		gotoxy(2,5);
		cout<<"Seleccione la ubicacion de ";
		
		switch(index)
		{
		case 0:
			current = FRAGATA;	
			letra = 'F';
			cout<<"la FRAGATA";	
			break;
		case 1:
			current = SUBMARINO;			
			letra = 'S';
			cout<<"el SUBMARINO";						
			break;
		case 2:
			current = ACORAZADO;			
			letra = 'A';
			cout<<"el ACORAZADO";						
			break;
		case 3:
			current = DESTRUCTOR;			
			letra = 'D';
			cout<<"el DESTRUCTOR";						
			break;
		}
		
		gotoxy(40,3);
		dibujarTablero(j,true);
		
		gotoxy(40+(pos_x+1)*2+9,(pos_y+1)*2+2);
		
		if(isVertical)
		{
			for(int i=0;i<current;i++)
			{
				cout<<letra;
				gotoxy(40+(pos_x+1)*2+9,(pos_y+1)*2 + 4 +(i*2));
			}
		}
		else
		{
			for(int i=0;i<current;i++)
			{
				cout<<letra;
				gotoxy(40+(pos_x+1)*2+11+(i*2),(pos_y+1)*2+2);
			}
		}
		
		gotoxy(2,10);
		cout<<"Utilice las flechas para mover el barco";
		gotoxy(2,12);
		cout<<"Presione [r] para Rotar";		
		gotoxy(2,14);
		cout<<"Presione Enter para confirmar la posicion";
		
		//detectar el teclado		
		char key = getch();
		switch(key)
		{
		case KEY_ENTER:
			{			
				if(validaUbicacion(pos_x,pos_y,current,isVertical,j.tablero))
				{
					isVertical = true;
					pos_x = 0;
					pos_y = 0;
					index++;
				}
			}
			break;
		case KEY_LEFT:
			{
				pos_x--;
				if(pos_x < 0)
					pos_x = 0;
			}
			break;
		case KEY_RIGHT:
			{					
				pos_x++;
				if(isVertical)
				{
					if(pos_x > 9)
						pos_x = 9;
				}else
				{
					if(pos_x+current > 10)
						pos_x = 10 - current;
				}
			}
			break;	
		case KEY_UP:
			{
				pos_y--;
				if(pos_y < 0)
					pos_y = 0;
			}
			break;
		case KEY_DOWN:
			{					
				pos_y++;
				if(isVertical)
				{
					if(pos_y+current > 10)
						pos_y = 10-current;
				}else{
					if(pos_y > 9)
						pos_y = 9;
				}
			}
			break;
		case 'R':
		case 'r':
			{					
				isVertical = !isVertical;
			}
			break;
		default:
			break;
		}
	}
}

void generaTablero(int tablero[TABLERO][TABLERO])
{
	int pos_x;
	int pos_y;
	bool vertical;
	TIPO_BARCO tipo;
	int cont = 0;
	while(cont<4)
	{
		pos_x = rand()%10;
		pos_y =  rand()%10;
		vertical = rand()%2;
		
		switch(cont+2)
		{
			case FRAGATA:
				tipo = FRAGATA;
				break;
			case SUBMARINO:
				tipo = SUBMARINO;
				break;
			case ACORAZADO:
				tipo = ACORAZADO;
				break;
			case DESTRUCTOR:
				tipo = DESTRUCTOR;
				break;		
		}
		if(validaUbicacion(pos_x,pos_y,tipo,vertical,tablero))
			cont++;
	}
}

bool validaUbicacion(int pos_x,int pos_y,TIPO_BARCO tipo,bool vertical,int tablero[TABLERO][TABLERO])
{	
	int val_x = pos_x;
	int val_y = pos_y;
	
	for(int i=0;i<tipo;i++)
	{
		if(val_x >= TABLERO)
			return false;
		else if(val_y >= TABLERO)
			return false;
		
		if(tablero[val_y][val_x] != NADA)
		{
			return false;
		}
		
		if(vertical)
			val_y++;
		else
			val_x++;
	}
	
	val_x = pos_x;
	val_y = pos_y;
	
	for(int i=0;i<tipo;i++)
	{
		tablero[val_y][val_x] = tipo;
		
		if(vertical)
			val_y++;
		else
			val_x++;
	}
	
	return true;
}

void inicializarJugador(jugador &j)
{	
	j.cont_acorazado = ACORAZADO;
	j.cont_destructor =  DESTRUCTOR;
	j.cont_fragata = FRAGATA;
	j.cont_submarino = SUBMARINO;
	
	for(int i=0;i<TABLERO;i++)
		for(int x=0;x<TABLERO;x++)
			j.tablero[i][x] = NADA;
	
}



















