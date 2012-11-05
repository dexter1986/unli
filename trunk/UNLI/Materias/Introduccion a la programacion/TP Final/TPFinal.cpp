#include<iostream>
#include<constream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<conio.h>
#include<conio2.h>
#include<fstream>
#include<string.h>


#include<ctype.h>


using namespace std;

#define MAX_ANCHO 80
#define MAX_LARGO 25


const float MAX_VEL = 250.0;
const float FPS = 30.0;
const float Friccion = 1.0;
const int MAX_CANT_AUTOS = 100;
const int KEY_LEFT  = 75;
const int KEY_RIGHT = 77;
const int KEY_UP    = 72;
const int KEY_DOWN  = 80;
const int KEY_ENTER = 13;
const int KEY_ESC   = 27;
float step_time;


enum TIPO_ELEMENTO
{
	AUTO = 0,	
	POZO = 1		
};

enum ESTADO_JUGADOR
{
	Nada = 0,
	Acelera = 1,	
	Frena = 2	
};

class Circuito
{	
	char pista[5][5];
	char banquina;
	int index;
	void CargarPista();
	void CargarBanquina();	
	int getIndex();
public:
	void Incrementar_Distancia();
	void Dibujar();
	Circuito();
};

void Circuito::Incrementar_Distancia()
{
	index++;
	if(index > 4)
		index = 0;	
}

int Circuito::getIndex()
{
	return index;
}

void Circuito::CargarBanquina()
{
	banquina = 179;		
}

void Circuito::CargarPista()
{		
	pista[0][0] = 186;
	pista[0][1] = 186;
	pista[0][2] = ' ';
	pista[0][3] = 186;
	pista[0][4] = ' ';
	
	pista[1][0] = ' ';
	pista[1][1] = 186;
	pista[1][2] = 186;
	pista[1][3] = ' ';
	pista[1][4] = 186;
	
	pista[2][0] = 186;
	pista[2][1] = ' ';
	pista[2][2] = 186;
	pista[2][3] = 186;
	pista[2][4] = ' ';
	
	pista[3][0] = ' ';
	pista[3][1] = 186;
	pista[3][2] = ' ';
	pista[3][3] = 186;
	pista[3][4] = 186;
	
	pista[4][0] = 186;
	pista[4][1] = ' ';
	pista[4][2] = 186;
	pista[4][3] = ' ';
	pista[4][4] = 186;
}


Circuito::Circuito()
{	
	CargarPista();
	CargarBanquina();	 
	index = 0;
}

void Circuito::Dibujar()
{
	int index = getIndex();
	int count = 0;
	for(int i = 0;i<MAX_LARGO;i++)
	{
		gotoxy(25,i+1);		
		cout<<banquina;
		cout<<"               ";
		cout<<pista[index][count];
		cout<<"               ";
		cout<<banquina;		
		count++;
		if(count > 4)
			count = 0;
	}
}



class Auto
{
protected:
	float distancia;
	float velocidad;
	
	int x;
	int y;
public:
	Auto();
	int Get_Y();
	int Get_X();
	virtual void Dibujar()=0;
};

int Auto::Get_Y()
{
	return y;
}

int Auto::Get_X()
{
	return x;
}


Auto::Auto()
{
	velocidad = 80.0;
	distancia = 0;
	x = 0;
	y = 0;
}

class AutoOponente:public Auto
{
public:
	AutoOponente();	
	void Mover();
	void calcular_distancia(int cant);
	virtual void Dibujar()=0;
	bool isEnable();
	bool isDraw();
};

void AutoOponente::calcular_distancia(int cant)
{
	y+=cant;
}

void AutoOponente::Mover()
{
	if(velocidad > 0 && isEnable())
	{	
		distancia += velocidad * step_time;	
		if(distancia > 3)
		{
			y--;
		}
		if(distancia > 2)
		{
			y--;
		}
		if(distancia > 1)
		{
			distancia = 0;
			y--;
		}
	}
}

bool AutoOponente::isDraw()
{
	if(y > 0 && y < 21)
		return true;
	else
		return false;
}

bool AutoOponente::isEnable()
{
	if(y < 25)
		return true;
	else
		return false;
}
AutoOponente::AutoOponente()
{
	x = rand()%26+27;	
}

class AutoOponente_t1:public AutoOponente
{
public:
	void Dibujar();
	AutoOponente_t1(int y);
};

AutoOponente_t1::AutoOponente_t1(int py){
	y = py;
}

void AutoOponente_t1::Dibujar()
{
	if(isDraw())
	{
		gotoxy(x,y);
		cout<<(char)218<<"=="<<(char)191;
		gotoxy(x,y+1);
		cout<<(char)178<<"XX"<<(char)178;
		gotoxy(x,y+2);
		cout<<(char)204<<(char)205<<(char)205<<(char)185;
		gotoxy(x,y+3);
		cout<<(char)178<<(char)205<<(char)205<<(char)178;	
	}
}

class AutoOponente_t2:public AutoOponente
{
public:
	void Dibujar();
	AutoOponente_t2(int y);
};

AutoOponente_t2::AutoOponente_t2(int py){
	y = py;
}

void AutoOponente_t2::Dibujar()
{
	if(isDraw())
	{
		gotoxy(x,y);
		cout<<(char)218<<"=="<<(char)191;
		gotoxy(x,y+1);
		cout<<(char)177<<"=="<<(char)177;
		gotoxy(x,y+2);
		cout<<(char)204<<(char)205<<(char)205<<(char)185;
		gotoxy(x,y+3);
		cout<<(char)177<<"=="<<(char)177;
	}
}

class AutoJugador:public Auto{
public:
	AutoJugador();
	void Derecha();
	void Izquierda();
	void Dibujar();
};

void AutoJugador::Derecha()
{
	if(x<53)
		x++;
}

void AutoJugador::Izquierda()
{
	if(x>26)
		x--;	
}

AutoJugador::AutoJugador()
{
	y = 21;
	x = 39;
}

void AutoJugador::Dibujar()
{
	gotoxy(x,y);
	cout<<" /\\ ";
	gotoxy(x,y+1);
	cout<<(char)180<<"=="<<(char)195;
	gotoxy(x,y+2);
	cout<<" "<<(char)204<<(char)185<<" ";
	gotoxy(x,y+3);
	cout<<(char)176<<"=="<<(char)176;
}

typedef struct PODIO
{
	char nombre[12];
	float valor;
};

class Juego
{
	Circuito circuito;
	int count_char;
	float tiempo;	
	float velocidad;	
	float distancia;
	float distancia_total;
	int index_curr_auto;
	ESTADO_JUGADOR estado;
	
	AutoOponente *autos[MAX_CANT_AUTOS];
	
	PODIO podios[5];
	
	int cant_autos;
	
	AutoJugador jugador;
	
	void MostrarVelocidad();
	void MostrarTiempo();
	void MostrarDistancia();
	void CalcularVelocidad();
	void CalcularTiempo();	
	void MostrarEstado();
	void DibujarAutos();
	void MoverAutos();
	void Dibujar();
	void Get_Podio();
	void GuardarPodio();
	void VerificarColision();
public:
	void Intro();
	void Fin();
	float GET_TIME();
	void Loop();
	void Derecha();
	void Izquierda();
	void Acelerar();
	void Frenar();	
	Juego();
	~Juego();
};

Juego::Juego()
{
	srand(time(NULL));
	count_char = 0;
	index_curr_auto = 0;
	velocidad = 0;
	distancia_total = 0;
	step_time = 1 / FPS;
	tiempo = 60.0;
	estado = Nada;
	int step_y = 1500 / MAX_CANT_AUTOS *-1;
	int y = step_y;
	for(int i=0;i<MAX_CANT_AUTOS;i++)
	{
		if(rand()%3 > 1)
			autos[i] = new AutoOponente_t1(y);
		else
			autos[i] = new AutoOponente_t2(y);
		
		y += step_y;
	}
}

Juego::~Juego()
{
	for(int i=0;i<MAX_CANT_AUTOS;i++)
		delete autos[i];
}

float Juego::GET_TIME()
{
	return tiempo;
}

void Juego::CalcularVelocidad()
{
	if(velocidad > 0)
	{	int count = 0;
		distancia += velocidad * step_time;	
		
		if(distancia > 4)
		{
			count++;
		}
		if(distancia > 3)
		{
			count++;
		}
		if(distancia > 2)
		{
			count++;
		}		
		if(distancia > 1)
		{
			distancia = 0;
			count++;			
			count_char+=count;
			
			circuito.Incrementar_Distancia();
			
			for(int i=index_curr_auto;i<MAX_CANT_AUTOS;i++)
			{
				if(autos[i]->isEnable())
					autos[i]->calcular_distancia(count);
			}
			
		}
		
		//velocidad -= Friccion;
		
		if(velocidad < 0)
			velocidad = 0;	
		
		distancia_total += velocidad * step_time * 0.3;
	}
}

void Juego::MoverAutos()
{
	for(int i=index_curr_auto;i<MAX_CANT_AUTOS;i++)
	{	
		if(autos[i]->isEnable())
			autos[i]->Mover();
		else
			index_curr_auto = i+1;
	}
}

void Juego::DibujarAutos()
{
	for(int i=index_curr_auto;i<MAX_CANT_AUTOS;i++)
	{
		autos[i]->Dibujar();
	}
}

void Juego::CalcularTiempo()
{
	if(tiempo > 0)
		tiempo -= step_time;
	if(tiempo < 0)
		tiempo = 0;
}

void Juego::MostrarVelocidad()
{
	gotoxy(5,3);		
	cout<<(int)velocidad<<"    ";
	gotoxy(9,3);
	cout<<"KM/H";		
}

void Juego::MostrarTiempo()
{
	gotoxy(5,5);	
	if(tiempo / 60 >= 1)
		cout<<"1m 00seg";
	else
		cout<<fixed<<setprecision(1)<<tiempo<<" seg  ";
}

void Juego::MostrarEstado()
{
	gotoxy(5,10);		
	
	if(estado == Nada)
	{
		
	}
	else if(estado == Acelera)
	{
		cout<<"Acelerando...";
	}
	else if(estado == Frena)
	{
		cout<<"Frenando...";
	}
}

void Juego::MostrarDistancia()
{
	gotoxy(5,4);		
	cout<<fixed<<setprecision(3)<<distancia_total / 1000 <<" km";	
	gotoxy(5,6);		
	cout<<"Autos:"<<index_curr_auto<<"/"<<MAX_CANT_AUTOS;
	gotoxy(5,7);		
	cout<<"GPS POS: "<<count_char;
	gotoxy(5,8);		
	cout<<"Proximo: "<<autos[index_curr_auto]->Get_Y()<<"    ";		
}

void Juego::Dibujar()
{
	circuito.Dibujar();
	DibujarAutos();
	jugador.Dibujar();
	MostrarVelocidad();
	MostrarDistancia();
	MostrarTiempo();
	MostrarEstado();
}

void Juego::Derecha()
{
	jugador.Derecha();
}

void Juego::Izquierda()
{
	jugador.Izquierda();
}

void Juego::Acelerar()
{
	if(velocidad < MAX_VEL)
		velocidad+=10;
	if(velocidad > MAX_VEL)
		velocidad = MAX_VEL;	
}

void Juego::Frenar()
{
	if(velocidad > 0)
		velocidad-=10;
	if(velocidad < 0)
		velocidad = 0;
}



void Juego::Loop()
{	
	CalcularVelocidad();
	MoverAutos();
	CalcularTiempo();
	Dibujar();	
	VerificarColision();
}

void Juego::Fin()
{
	gotoxy(31,10);
	cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
	gotoxy(31,11);
	cout<<" "<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";		
	gotoxy(44,11);
	cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<"  ";	
	gotoxy(39,11);
	cout<<" Fin ";
	gotoxy(31,12);
	cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
	Sleep(1500);
	
	GuardarPodio();
}

void Juego::Get_Podio()
{
	gotoxy(67,4);
	cout<<(char)174<<" Podio "<<(char)175;
	gotoxy(65,5);
	cout<<(char)240<<(char)240<<(char)240<<(char)240<<(char)240<<(char)240<<(char)240<<(char)240<<(char)240<<(char)240<<(char)240<<(char)240<<(char)240;
	
	for(int i=0;i<5;i++)
	{
		strcpy(podios[i].nombre,"");
		podios[i].valor = 0;	
	}
	
	fstream file;
	try
	{
		file.open("podio.save",ios::binary|ios::in);	
		file.read((char*)podios,sizeof(PODIO)*5);
	}
	catch(...)
	{
		
	}
	
	file.close();
	
	for(int i=0;i<5;i++)
	{
		gotoxy(59,6+i);	
		cout<<i+1<<". ";
		if(podios[i].valor == 0)
			continue;
		cout<<fixed<<setprecision(3)<<podios[i].valor/1000<<" "<<podios[i].nombre;
	}
}

void Juego::GuardarPodio()
{
	PODIO aux[5];	
	int index = -1;
	
	for(int i=0;i<5;i++)
	{
		if(podios[i].valor < distancia_total)
		{
			index = i;
			break;
		}	
	}
	
	if(index != -1)
	{
		
		
		gotoxy(31,10);
		cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
		gotoxy(31,11);
		cout<<" "<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";		
		gotoxy(44,11);
		cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<"  ";	
		gotoxy(36,11);
		cout<<"Nuevo Podio";
		gotoxy(31,12);
		cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
		Sleep(1500);
		
		gotoxy(36,11);
		cout<<"  Puesto "<<index+1<<" ";		
		Sleep(1500);
		
		gotoxy(28,11);
		cout<<"Ingrese su nombre: ";
		
		char nombre[12];
		
		cin.get(nombre,12);
		
		for(int i=0;i<5;i++)
		{	
			if(i == index)
			{
				strcpy(aux[i].nombre,nombre);
				aux[i].valor = distancia_total;								
			}else if(i<index)
			{
				strcpy(aux[i].nombre, podios[i].nombre);
				aux[i].valor = podios[i].valor;
			}else if(i > index)
			{
				strcpy(aux[i].nombre, podios[i-1].nombre);
				aux[i].valor = podios[i-1].valor;
			}
		}
		
		fstream file;
		file.open("podio.save",ios::binary|ios::trunc|ios::out);	
		file.write((const char*) aux,sizeof(PODIO)*5);	
		file.close();
	}
}

void Juego::Intro()
{	
	clrscr();
	int flag = 0;
	gotoxy(60,24);
	cout<<"Oscar Sanchez - 2012";
	for(int i=0;i<20;i++)
	{
		gotoxy(30+flag,10);
		cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
		gotoxy(30+flag,11);
		cout<<" "<<" "<<(char)176<<" "<<(char)176<<"  ";		
		gotoxy(45+flag,11);
		cout<<" "<<(char)176<<" "<<(char)176<<" ";
		gotoxy(36,11);
		cout<<"Super Road";
		gotoxy(30+flag,12);
		cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
		Sleep(200);
		if(flag == 0)
			flag = 1;
		else
			flag = 0;
	}
	clrscr();
	gotoxy(30,10);
	cout<<"Instrucciones:";
	gotoxy(30,11);
	cout<<"Acelerar -> Flecha Arriba";
	gotoxy(30,12);
	cout<<"Frenar   -> Flecha Abajo";
	gotoxy(30,13);
	cout<<"Manejar  -> Flechas Derecha e Izquierda";
	gotoxy(30,14);
	cout<<"Salir    -> Tecla Escape (ESC)";
	Sleep(3000);	
	clrscr();
	Dibujar();
	
	Get_Podio();
	
	for(int i=0;i<3;i++)
	{
		gotoxy(31,10);
		cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
		gotoxy(31,11);
		cout<<" "<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";		
		gotoxy(42,11);
		cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<"  ";
		gotoxy(40,11);
		cout<<" "<<3-i<<" ";
		gotoxy(31,12);
		cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
		Sleep(1000);		
	}
	
	gotoxy(31,10);
	cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
	gotoxy(31,11);
	cout<<" "<<" "<<(char)176<<" "<<(char)176<<"  ";		
	gotoxy(46,11);
	cout<<" "<<(char)176<<" "<<(char)176<<" ";	
	gotoxy(37,11);
	cout<<" Largaron";
	gotoxy(31,12);
	cout<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" "<<(char)176<<" ";
	Sleep(1000);	
}

void Juego::VerificarColision()
{
	if(jugador.Get_Y() <= autos[index_curr_auto]->Get_Y()+3)
	{
		if(autos[index_curr_auto]->Get_X() < jugador.Get_X())
		{
			if(autos[index_curr_auto]->Get_X()+3 >= jugador.Get_X())
			{
				velocidad = 0;
			}
		}
		else if(autos[index_curr_auto]->Get_X() > jugador.Get_X())
		{
			if(autos[index_curr_auto]->Get_X() <= jugador.Get_X() + 3)
			{
				velocidad = 0;
			}
		}
		else
		{
		   velocidad = 0;
		}
	}
}

int main(int argc,char *argv[])
{		
	bool salir = false;
	float start_time;
	Juego juego;
	
	juego.Intro();
	
	while(!salir)
	{
		start_time =  clock();
		if(kbhit())
		{
			char key = getch();			
			if(key == KEY_ESC)
			{
				salir = true;
			}else
			{
				if(key == KEY_UP)
				{					
					juego.Acelerar();
				}
				if(key == KEY_DOWN)
				{					
					juego.Frenar();
				}
				if(key == KEY_LEFT)					
				{
					juego.Izquierda();
				}
				if(key == KEY_RIGHT)
				{					
					juego.Derecha();
				}
			}
		}
		juego.Loop();	
		while((clock() - start_time) < step_time);			
		if(juego.GET_TIME() == 0)
		{
			salir = true;
		}
	}
	juego.Fin();
	clrscr();
	gotoxy(30,10);
	cout<<"Gracias por jugar"<<endl<<endl<<endl;
	system("PAUSE");
	return 0;
}


