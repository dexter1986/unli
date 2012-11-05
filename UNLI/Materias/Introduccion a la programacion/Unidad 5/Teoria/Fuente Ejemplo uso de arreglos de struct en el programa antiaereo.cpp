/*
Este ejemplo muestra el uso de arreglos de tipo struct para juntar variables del mismo tipo
y facilitar la escritura del programa

La diferencia con el uso de arreglos simples es que se agrupan todas las variables
de coordenadas en un mismo arreglo

Funcionamiento:
El tanque se mueve con las flechas y dispara con las teclas 1 y 2
El programa termina cuando una bomba alcanza al tanque

El algoritmo ser?a:
inicializar valores
repetir
avanzar aviones
	lanzar bombas al azar
Lanzar nuevos aviones al azar
mover bombas en caida
mover disparos
mover el tanque seg?n pulsaciones de teclas
	disparar seg?n pulsaciones de teclas
detectar colisi?n disparo bombardero, si ocurre borrar avi?n y borrar disparo
detectar colisi?n bomba tanque, si ocurre terminar el programa
volver a repetir

El programa fue subdivido en subprogramas para que sea m?s claro y los problemas
en los subprogramas son m?s sencillos de resolver por ejemplo Lanzar nuevos aviones
so encarga de solo eso:

El Algoritmo anterior

Si el par de valores x1,y1 est?n libres usarlo para un nuevo avi?n
colocar las coordenadas de inicio x1=2 y1=al azar
sino
Si el par de valores x2,y2 est?n libres usarlo para un nuevo avi?n
colocar las coordenadas de inicio x2=2 y2=al azar
sino
Si el par de valores x3,y3 est?n libres usarlo para un nuevo avi?n
colocar las coordenadas de inicio x3=2 y3=al azar
sino
Regresar sin lanzar nada.

El algoritmo actual

Buscar en el arreglo ax un valor libre (ax[n]==0)
Si encuentra uno usar la posici?n n en el arreglo de ax y ay para darle las coordenadas de inicio ax[n]=1 ay[n]=al azar
sino
Regresar sin lanzar nada

Como se ve el nuevo algoritmo es m?s corto y acepta cualquier cantidad de aviones,
tantos como el tama?o del arreglo lo permita

*/
#include <constream>
#include <windows.h>
#include <ctime>

using namespace conio;
using namespace std;


//variando los valores en los defines pueden hacer que el juego sea m?s facil o dificil

#define MaxAvio 10 //cambiando estos numeros ser? la cantidad m?xima de esos
#define MaxDisp 5 //elementos que apareceran a la vez en el juego
#define MaxBomb 5

#define PAvion 8 //probabilidad de aparecer un nuevo avi?n cada 100 milisegundos cuando menor es el n?mero m?s rapido aparecen los aviones
#define PBomba 30 //probabilidad de que cada avi?n lance una bomba cada 100 milisegundos cuando menor es el numero mas bombas tiran los aviones


//declaraci?n de las estructuras
//usamos typedef porque luego es m?s comodo para declarar las variables

typedef struct{
	int x; //coordenadas x,y
	int y;
} coordenadas; //las bombas y los aviones usan coordenadas

typedef struct{
	int x; //coordenadas x,y 
	int y;
	int d;
} disparo; //hacemos uno especial para el disparo ya que necesita direcci?n


//declaraciones de los prototipos de las funciones
//se puede observar que son m?s simples en el traspaso de param?tros
void imprBombardero(coordenadas a[], int m);
void borraBombardero(coordenadas a);
void imprTanque(int x,int y);
void explotaTanque(int x,int y);
void imprBomba(coordenadas b[],int m);
void lanzaAvion(coordenadas a[], int m);
void lanzabomba(coordenadas a,coordenadas b[],int m);
void caidaBomba(coordenadas b[],int m);
void disparoIzq(int x,int y,disparo t[],int m);
void disparoDer(int x,int y,disparo t[],int m);
void avanceDisparo(disparo t[],int m);
void imprTiro(disparo t[],int m);
void explotaTanque(int x,int y);
void colTirAvi(coordenadas a[],int am,disparo t[],int tm);
bool colBombTanq(int x,int y,coordenadas b[],int m);


//declaraciones de las variables globales
const int bizq=1;  //limites de los bordes
const int bder=80; //est?n declarados globalmente
const int bsup=1;  //para que todas las funciones puedan usarlas
const int binf=24; //de aqu? en adelante


int main() {
		
	coordenadas av[MaxAvio]; //coordenadas aviones
	coordenadas bo[MaxBomb]; //coordenadas bombas
	disparo ti[MaxDisp]; //coordenadas de disparo
	
	int x,y; //coordenadas x y de nuestro veh?culo
	
	char t;
	int n;
	
	int tam=3;
	
	for(n=0;n<MaxAvio;++n)
	{
		av[n].x=0; //inicializamos a cero
		av[n].y=0; // cuando las coordenadas son imprimibles esta en carrera
	}
	
	for(n=0;n<MaxBomb;++n)
	{
		bo[n].x=0; //inicializamos a cero
		bo[n].y=0; // cuando las coordenadas son imprimibles esta en carrera
	}
	
	for(n=0;n<MaxDisp;++n)
	{
		ti[n].x=0; //inicializamos a cero
		ti[n].y=0; // cuando las coordenadas son imprimibles esta en carrera
		ti[n].d=0;
	}
	
	
	x=38;
	y=21;
	
	srand(time(NULL));  //se inicializa el azar
	
	cout<<clrscr; //borramos la pantalla
	
	while(true)
	{
		
		// avanzamos los MaxAvio aviones
		for(n=0;n<MaxAvio;++n)
		{
			if(av[n].x>1)  //avanzamos avi?n n si esta en carrera
			{
				if(rand()%PBomba==0) lanzabomba(av[n],bo,MaxBomb);
				++av[n].x;
				
				if(av[n].x>73)
				{
					borraBombardero(av[n]);
					av[n].x=0;
				}
			}
		}
		
		//?Nuevo avi?n?
		if(rand()%PAvion==0) lanzaAvion(av,MaxAvio);
		
		//ca?da de bomba
		caidaBomba(bo,MaxBomb);
		//avance de tiro
		avanceDisparo(ti,MaxDisp);
		
		//movimiento del tanque
		if(kbhit())
		{
			t=getch();
			if(t==75) //nos movemos a la izquierda
			{
				--x;
				if(x<bizq) x=bizq; //no nos pasamos del borde izquierdo de la pantalla
			}
			if(t==77) //nos movemos a la derecha
			{
				++x;
				if(x>bder-tam+1) x=bder-tam+1; //no nos pasamos del borde derecho de la pantalla
			}
			if(t=='1') disparoIzq(x,y,ti,MaxDisp);
			if(t=='2') disparoDer(x,y,ti,MaxDisp);
		}
		
		//colisiones
		//colisi?n tiro-avion
		colTirAvi(av,MaxAvio,ti,MaxDisp);
		
		//colisi?n bomba-tanque
		
		if(colBombTanq(x,y,bo,MaxBomb))
		{
			explotaTanque(x,y);
			break; //salimos del juego
		}
		
		//dibuja todo
		imprTiro(ti,MaxDisp); //imprime tiros
		imprTanque(x,y); //imprime tanque
		imprBomba(bo,MaxBomb); //imprime bomba 1
		imprBombardero(av,MaxAvio); //imprimimos los aviones
		
		Sleep(100);
	}
	
	return 0;
}

/* (char) este modificador cambia el n?mero siguiente al caracter correspondiente
tambi?n funciona a la inversa (int)'0' devuelve el codigo de caracter 0 que ser?a 48
Si se hace una asignaci?n esto lo hace en forma autom?tica llevandolo al tipo de
variable, por ejemplo int a='0' a valdr? 48 char a=48 contendra '0'*/

void imprBombardero(coordenadas a[], int m) //dibuja los aviones en las coordenadas (x[n], y[n])
{
	for(int n=0;n<m;++n)
	{
		if((a[n].x<2)||(a[n].y<1)) continue; // si las coordenadas no son imprimibles no se imprime
		cout<<setxy(a[n].x-1,a[n].y)<<" "<<(char)220<<"   "<<(char)218<<(char)191;
		cout<<setxy(a[n].x-1,a[n].y+1)<<" "<<(char)223<<(char)223<<(char)223<<(char)175<<(char)223<<(char)223;
	}
}

void borraBombardero(coordenadas a) //borra un avi?n en las coordenadas (x, y)
{
	if((a.x<2)||(a.y<1)) return; // si las coordenadas no son imprimibles no se imprime
	cout<<setxy(a.x-1,a.y)<<"      ";
	cout<<setxy(a.x-1,a.y+1)<<"      ";
}

void imprTanque(int x, int y) //dibuja el tanque
{
	cout<<setxy(x-1,y)<<" \\"<<(char)127<<"/ ";
	cout<<setxy(x-1,y+1)<<" "<<(char)219<<(char)219<<(char)219<<" ";
	cout<<setxy(x-1,y+2)<<" O O ";
}

void imprBomba(coordenadas a[],int m)
{
	//buscamos las coordenadas diferentes de 0 que son las que se estan moviendo
	for(int n=0;n<m;++n)
	{
		if(a[n].x>0) cout<<setxy(a[n].x,a[n].y)<<(char)153;
	}
}

void lanzaAvion(coordenadas a[], int m)
{
	//buscamos si hay un par de variables de avion sin uso
	//sino hay no pasa nada
	for(int n=0;n<m;++n)
	{
		if(a[n].x==0)
		{
			a[n].x=2;
			a[n].y=rand()%10+5;
			return;
		}
	}
}

void lanzabomba(coordenadas a,coordenadas b[],int m)
{
	//buscamos si hay un par de variables de bomba sin uso
	//sino hay no pasa nada
	for(int n=0;n<m;++n)
	{
		if(b[n].x==0)
		{
			b[n].x=a.x+3;
			b[n].y=a.y+2;
			return;
		}
	}
}

void caidaBomba(coordenadas b[],int m)
{
	//buscamos las coordenadas diferentes de 0 que son las que se estan moviendo
	for(int n=0;n<m;++n)
	{
		if(b[n].x>0)
		{
			cout<<setxy(b[n].x,b[n].y)<<" "; //borramos bomba posici?n anterior
			++b[n].x;
			++b[n].y;
			if((b[n].x>=bder)||(b[n].y>=binf)) //verificamos si se sale de los bordes
			{
				b[n].x=0; //variables disponibles para pr?xima bomba
				b[n].y=0;
			}
		}
	}
}

void disparoIzq(int x,int y,disparo t[],int m)
{
	//se busca un par de variables libres para usar, si no hay o habr? disparo alguno
	for(int n=0;n<m;++n)
	{
		if(t[n].x==0)
		{
			t[n].x=x-1;
			t[n].y=y-1;
			t[n].d=-1;
			return;
		}
	}
}

void disparoDer(int x,int y,disparo t[],int m)
{
	//se busca un par de variables libres para usar, si no hay o habr? disparo alguno
	for(int n=0;n<m;++n)
	{
		if(t[n].x==0)
		{
			t[n].x=x+4;
			t[n].y=y-1;
			t[n].d=1;
			return;
		}
	}
}

void avanceDisparo(disparo t[],int m)
{
	//primeros vemos si hay alg?n disparo en vuelo y si lo hay lo movemos seg?n su direcci?n
	for(int n=0;n<m;++n)
	{
		if(t[n].x>0)
		{
			cout<<setxy(t[n].x,t[n].y)<<" "; //borramos tiro posici?n anterior
			t[n].x+=t[n].d;
			--t[n].y;
			if((t[n].x>=bder)||(t[n].x<=bizq)||(t[n].y<=bsup)) //verificamos si se sale de los bordes
			{
				t[n].x=0;
				t[n].y=0;
				t[n].d=0;
			}
		}
	}
}

void imprTiro(disparo t[],int m)
{
	for(int n=0;n<m;++n)
	{
		if(t[n].x<=0) continue; //no hay disparo para imprimir revisar siguiente
		cout<<setxy(t[n].x,t[n].y);
		if(t[n].d==1)
		{
			cout<<"/";
		}
		else
			{
				cout<<"\\";
			}
	}
}

void colTirAvi(coordenadas a[],int am,disparo t[],int tm)
{  // hay que revisar todos los aviones con todos los disparos
	for(int i=0;i<am;++i)
	{
		if(a[i].x==0) continue; //si la coordenada x del avion es 0 no evaluar
		for(int j=0;j<tm;++j)
		{
			if(t[j].x==0) continue; //si la coordenada x del tiro es 0 no evaluar
			if((t[j].x>=a[i].x)&&(t[j].x<=a[i].x+5)&&(t[j].y<=a[i].y+1)&&(t[j].y>=a[i].y))
			{
				// impacto avi?n i con disparo j
				borraBombardero(a[i]);
				a[i].x=0; //las coordenadas del avion a 0 para que esten disponibles
				a[i].y=0; //cuando se lanze el pr?ximo avion
				t[j].x=0; //las coordenadas del tiro a 0 para que esten disponibles
				t[j].y=0; //cuando se lanze el pr?ximo tiro
			}
		}
	}
	
	return;
}

bool colBombTanq(int x,int y,coordenadas b[],int m)
{ //verdadero si una bomba golpeo el tanque
	//comparamos todas las bombas
	for(int n=0;n<m;++n)
		if((b[n].x>=x)&&(b[n].x<=x+2)&&(b[n].y<=y+2)&&(b[n].y>=y)) return true;
	return false;
}

void explotaTanque(int x,int y)
{ //animaci?n de destrucci?n del tanque
	cout<<setxy(x-1,y-1)<<"\\   /";
	cout<<setxy(x,y)<<" "<<(char)127<<" ";
	cout<<setxy(x,y+1)<<"(*)";
	Sleep(100);
	cout<<setxy(x-1,y-1)<<"     ";
	cout<<setxy(x,y)<<"   ";
	cout<<setxy(x-1,y+1)<<"( "<<(char)127<<" )";
	Sleep(100);
	cout<<setxy(x-1,y-1)<<"     ";
	cout<<setxy(x,y)<<"   ";
	cout<<setxy(x-1,y+1)<<"     ";
	cout<<setxy(x,y+2)<<"O"<<(char)127<<"O";
	Sleep(100);
	cout<<setxy(x,y+2)<<"   ";
}
