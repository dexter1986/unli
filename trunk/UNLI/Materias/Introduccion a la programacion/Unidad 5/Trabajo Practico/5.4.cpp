#include<iostream>
#include<constream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include <windows.h>

using namespace std;

#define CARTAS 40
#define MAX_JUGADORES 5
 
typedef struct{
	int nro;
	char tipo;
}carta;

typedef struct{
	int nro;
	carta cartas[20];
	float valor;
	int cant_cartas;
	bool sePaso;
}jugador;

void mostrarBaraja(carta arr[]);
void generarBaraja(carta arr[CARTAS]);
void corteEnMesa(carta arr[CARTAS]);
void mezclaAmerica(carta arr[CARTAS]);
void mezclaPorArrastre(carta arr[CARTAS]);
void mezclar(carta arr[CARTAS]);
float calcularValor(carta c);
void mostrarJugadas(jugador arr[],int cantidad,int turno);
void mostrarGanadores(jugador arr[],int cantidad);
bool validaJugador(jugador j);

int main(int argc,char *argv[])
{	
	carta baraja [CARTAS];
	jugador jugadores[MAX_JUGADORES];
	
	int cant_jugadores=0;
	int turno_jugador=0;
	int contador = 0;
	srand(time(NULL));	
	
	cout<<setw(50)<<"Juego de 7 y media"<<endl<<endl;
	cout<<"Cantidad de jugadores (1-5): ";
	cin>>cant_jugadores;
	
	generarBaraja(baraja);
	mezclar(baraja);
	//Primera mano
	for(int i=0;i<cant_jugadores;i++)
	{
		jugadores[i].nro = i+1;
		jugadores[i].cant_cartas = 0;	
		jugadores[i].valor = 0;
		jugadores[i].sePaso = false;
	}
	
	for(int i=0;i<cant_jugadores;i++)
	{
		clrscr();
		mostrarJugadas(jugadores,cant_jugadores,-1);
		cout<<setw(50)<<"Juego de 7 y media"<<endl<<endl;
		jugadores[i].cartas[0] = baraja[contador];		
		jugadores[i].cant_cartas = 1;
		jugadores[i].valor = calcularValor(baraja[contador]);
		contador++;		
		Sleep(500);
	}
	
	char opcion;
	while(true)
	{
		clrscr();
		mostrarJugadas(jugadores,cant_jugadores,turno_jugador);
		cout<<setw(50)<<"Juego de 7 y media"<<endl<<endl;		
		cout<<setw(47)<<"Juega jugador "<<jugadores[turno_jugador].nro<<endl<<endl;
		cout<<setw(53)<<"Otra carta si(s)/no(n): ";		
		cin>>opcion;
		
		switch(opcion)
		{
			case 's':
			case 'S':
				jugadores[turno_jugador].cant_cartas++;
				jugadores[turno_jugador].cartas[jugadores[turno_jugador].cant_cartas-1] = baraja[contador];
				jugadores[turno_jugador].valor += calcularValor(baraja[contador]);
				contador++;		
				if(!validaJugador(jugadores[turno_jugador])){
					jugadores[turno_jugador].sePaso = true;
					cout<<endl<<"Se paso."<<endl;
					Sleep(1000);
					turno_jugador++;
				}
				break;
			case 'n':
			case 'N':
				cout<<endl<<"Se planta."<<endl;
				Sleep(1000);
				turno_jugador++;
				break;
		}
		
		//Borra el buffer del teclado
		cin.clear();
		cin.sync();
		
		if(contador>=CARTAS)
		{
			cout<<setw(47)<<"No hay mas cartas"<<endl<<endl;
			break;
		}
		
		if(turno_jugador>=cant_jugadores)
			break;
	}	
	mostrarGanadores(jugadores,cant_jugadores);
	cout<<setw(49)<<"Gracias por jugar"<<endl<<endl;
	cout<<endl<<endl;
	system("PAUSE");
	return 0;
}

bool validaJugador(jugador j)
{
	if(j.valor > 7.5)
		return false;
	return true;
}

void mostrarGanadores(jugador arr[],int cantidad)
{
	clrscr();
	cout<<setw(50)<<"Juego de 7 y media"<<endl<<endl<<endl;
	
	int ganadores = 0;
	float valor = 0.0f;
	
	//Busca cual es el valor mayor
	for(int i=0;i<cantidad;i++)
	{
		if(!arr[i].sePaso)
		{
			if(valor < arr[i].valor)
			{
				valor = arr[i].valor;
			}
		}
	}
	
	if(valor > 0)
	{
		cout<<setw(50)<<"Los ganadores son: "<<endl<<endl;
		//Busca los ganadores
		for(int i=0;i<cantidad;i++)
		{
			if(!arr[i].sePaso)
			{
				if(arr[i].valor == valor)
					cout<<setw(44)<<" - Jugador "<<arr[i].nro<<endl;
			}
		}
	}else
	{
		cout<<setw(49)<<"No hay ganadores"<<endl<<endl;
	}
	
	cout<<endl<<endl;
}

void mostrarJugadas(jugador arr[],int cantidad,int turno)
{
	//Mostrar se paso	
	gotoxy(1,10);
	for(int i=0;i<cantidad;i++)
	{	
		for(int c=0;c<arr[i].cant_cartas;c++)
		{
			cout<<"["<<arr[i].cartas[c].nro<<arr[i].cartas[c].tipo<<"] ";			
		}
		
		if(arr[i].sePaso)
		{
			cout<<" se paso";
		}
		else if(turno >= i)
		{
			int valor =(int) arr[i].valor;
			cout<<" (";
			
			if(valor > 0)
				cout<<valor;
			
			if(valor > 0 && valor < arr[i].valor)
				cout<<" ";
			
			if(valor < arr[i].valor) 
				cout<<"1/2";
			
			cout<<")";
		}
		
		if(turno == i)
		{
			cout<<" <--";		
		}
		
		cout<<endl<<setw(10)<<"Jugador "<<arr[i].nro<<endl<<endl;		
	}
	gotoxy(1,1);	
}

float calcularValor(carta c)
{
	if(c.nro > 7)
		return 0.5f;
	else
		return (float)c.nro;
}

void mezclar(carta arr[CARTAS])
{
	int americana = rand()%3+3;
	
	corteEnMesa(arr);
	for(int i=0;i<americana;i++)
	{
		mezclaAmerica(arr);
		if(rand()%2==0)
		{
			corteEnMesa(arr);
			mezclaPorArrastre(arr);						
		}
		corteEnMesa(arr);
	}
	corteEnMesa(arr);
}

void corteEnMesa(carta arr[CARTAS])
{
	int index = CARTAS / 2;
	carta aux;
	for(int i = 0;i<index;i++)
	{
		aux = arr[i+index];
		arr[i+index] = arr[i];
		arr[i] = aux;
	}
}

void mezclaAmerica(carta arr[CARTAS])
{
	int cont = 0;
	int index = CARTAS / 2;
	carta aux[CARTAS];	
	
	for(int i=0;i<index;i++)
	{		
		aux[cont] = arr[i];
		aux[cont+1] = arr[i+index];
		cont+=2;
	}
	
	for(int i=0;i<CARTAS;i++)
	{
		arr[i] = aux[i];
	}
}

void mezclaPorArrastre(carta arr[CARTAS])
{
	int ciclo = rand()%5+5;
	int nro_cartas;
	carta aux[10];
	for(int i=0;i<ciclo;i++)
	{
		nro_cartas = rand()%3+5;
		
		for(int x=0;x<nro_cartas;x++)
		{
			aux[x] = arr[x];
		}
		
		for(int x=0;x<CARTAS-nro_cartas;x++)
		{
			arr[x] = arr[ x + nro_cartas];
		}
		
		for(int x=0;x<nro_cartas;x++)
		{
			arr[CARTAS - nro_cartas + x] = aux[x];
		}
		
	}	
}

void generarBaraja(carta arr[CARTAS])
{
	char tipo;
	int index;
	int nro;
	for(int i=0;i<4;i++)
	{
		switch(i)
		{
			case 0:
				tipo = 'c'; //Copas
				break;
			case 1:
				tipo = 'b'; //Bastos
				break;
			case 2:
				tipo = 'e'; //Espadas
				break;
			case 3:
				tipo = 'o'; //Oro
		}
		
		for(int x=0;x<10;x++)
		{
			nro = x + 1;
			if(x > 6)
			{
				nro += 2;
			}
			index = x + (i*10); 
			arr[index].nro = nro;
			arr[index].tipo = tipo;
		}				
	}
}

void mostrarBaraja(carta arr[CARTAS])
{
	for(int i=0;i<CARTAS;i++)
	{
		if(i%10==0)
			cout<<endl;
		cout<<arr[i].nro<<arr[i].tipo;
		if(i%10!=9)
			cout<<",";
	}
}












