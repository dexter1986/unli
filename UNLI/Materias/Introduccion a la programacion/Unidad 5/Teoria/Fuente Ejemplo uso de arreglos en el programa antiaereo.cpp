/*
Este ejemplo muestra el uso de arreglos para juntar variables del mismo tipo
y facilitar la escritura del programa

Se crea un arreglo para cada coordenada de aviones disparos y bombas de tal
manera de poder agregar el n?mero que se quiera de los mismos al juego, ya que
en la anterior versi?n m?s alla de tres variables complicaba la escritura

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
using namespace conio;
using namespace std;


//variando los valores en los defines pueden hacer que el juego sea m?s facil o dificil

#define MaxAvio 10 //cambiando estos numeros ser? la cantidad m?xima de esos
#define MaxDisp 5 //elementos que apareceran a la vez en el juego
#define MaxBomb 5

#define PAvion 8 //probabilidad de aparecer un nuevo avi?n cada 100 milisegundos cuando menor es el n?mero m?s rapido aparecen los aviones
#define PBomba 30 //probabilidad de que cada avi?n lance una bomba cada 100 milisegundos cuando menor es el numero mas bombas tiran los aviones

//declaraciones de los prototipos de las funciones
//se puede observar que son m?s simples en el traspaso de param?tros
void imprBombardero(int x[], int y[], int m);
void borraBombardero(int x, int y);
void imprTanque(int x, int y);
void explotaTanque(int x,int y);
void imprBomba(int x[],int y[],int m);
void lanzaAvion(int ax[],int ay[], int m);
void lanzabomba(int x,int y,int bx[],int by[],int m);
void caidaBomba(int bx[],int by[],int m);
void disparoIzq(int x,int y,int tx[],int ty[],int td[],int m);
void disparoDer(int x,int y,int tx[],int ty[],int td[],int m);
void avanceDisparo(int tx[],int ty[],int td[],int m);
void imprTiro(int x[],int y[],int d[],int m);
void explotaTanque(int x,int y);
void colTirAvi(int ax[],int ay[],int am,int tx[],int ty[],int tm);
bool colBombTanq(int x,int y,int bx[],int by[],int m);

//declaraciones de las variables globales
const int bizq=1;  //limites de los bordes
const int bder=80; //est?n declarados globalmente
const int bsup=1;  //para que todas las funciones puedan usarlas
const int binf=24; //de aqu? en adelante


int main() {
		
	int ax[MaxAvio]; //coordenadas x de los aviones
	int ay[MaxAvio]; //coordenadas y de los aviones
	int x,y; //coordenadas x y de nuestro veh?culo
	int bx[MaxBomb]; //coordenadas x de las bombas
	int by[MaxBomb]; //coordenadas y de las bombas
	int tx[MaxDisp]; //coordenadas x de los tiros
	int ty[MaxDisp]; //coordenadas y de los tiros
	int td[MaxDisp]; //direcci?n del tiro -1 izquierda +1 derecha
	
	char t;
	int n;
	
	int tam=3;
	
	for(n=0;n<MaxAvio;++n)
	{
		ax[n]=0; //inicializamos a cero
		ay[n]=0; // cuando las coordenadas son imprimibles esta en carrera
	}
	
	for(n=0;n<MaxBomb;++n)
	{
		bx[n]=0; //inicializamos a cero
		by[n]=0; // cuando las coordenadas son imprimibles esta en carrera
	}
	
	for(n=0;n<MaxDisp;++n)
	{
		tx[n]=0; //inicializamos a cero
		ty[n]=0; // cuando las coordenadas son imprimibles esta en carrera
		td[n]=0;
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
			if(ax[n]>1)  //avanzamos avi?n n si esta en carrera
			{
				if(rand()%PBomba==0) lanzabomba(ax[n],ay[n],bx,by,MaxBomb);
				++ax[n];
				
				if(ax[n]>73)
				{
					borraBombardero(ax[n],ay[n]);
					ax[n]=0;
				}
			}
		}
		
		//?Nuevo avi?n?
		if(rand()%PAvion==0) lanzaAvion(ax,ay,MaxAvio);
		
		//ca?da de bomba
		caidaBomba(bx,by,MaxBomb);
		//avance de tiro
		avanceDisparo(tx,ty,td,MaxDisp);
		
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
			if(t=='1') disparoIzq(x,y,tx,ty,td,MaxDisp);
			if(t=='2') disparoDer(x,y,tx,ty,td,MaxDisp);
		}
		
		//colisiones
		//colisi?n tiro-avion
		colTirAvi(ax,ay,MaxAvio,tx,ty,MaxDisp);
		
		//colisi?n bomba-tanque
		
		if(colBombTanq(x,y,bx,by,MaxBomb))
		{
			explotaTanque(x,y);
			break; //salimos del juego
		}
		
		//dibuja todo
		imprTiro(tx,ty,td,MaxDisp); //imprime tiros
		imprTanque(x,y); //imprime tanque
		imprBomba(bx,by,MaxBomb); //imprime bomba 1
		imprBombardero(ax,ay,MaxAvio); //imprimimos los aviones
		
		Sleep(100);
	}
	
	return 0;
}

/* (char) este modificador cambia el n?mero siguiente al caracter correspondiente
tambi?n funciona a la inversa (int)'0' devuelve el codigo de caracter 0 que ser?a 48
Si se hace una asignaci?n esto lo hace en forma autom?tica llevandolo al tipo de
variable, por ejemplo int a='0' a valdr? 48 char a=48 contendra '0'*/

void imprBombardero(int x[], int y[], int m) //dibuja los aviones en las coordenadas (x[n], y[n])
{
	for(int n=0;n<m;++n)
	{
		if((x[n]<2)||(y[n]<1)) continue; // si las coordenadas no son imprimibles no se imprime
		cout<<setxy(x[n]-1,y[n])<<" "<<(char)220<<"   "<<(char)218<<(char)191;
		cout<<setxy(x[n]-1,y[n]+1)<<" "<<(char)223<<(char)223<<(char)223<<(char)175<<(char)223<<(char)223;
	}
}

void borraBombardero(int x, int y) //borra un avi?n en las coordenadas (x, y)
{
	if((x<2)||(y<1)) return; // si las coordenadas no son imprimibles no se imprime
	cout<<setxy(x-1,y)<<"      ";
	cout<<setxy(x-1,y+1)<<"      ";
}

void imprTanque(int x, int y) //dibuja el tanque
{
	cout<<setxy(x-1,y)<<" \\"<<(char)127<<"/ ";
	cout<<setxy(x-1,y+1)<<" "<<(char)219<<(char)219<<(char)219<<" ";
	cout<<setxy(x-1,y+2)<<" O O ";
}

void imprBomba(int x[],int y[],int m)
{
	//buscamos las coordenadas diferentes de 0 que son las que se estan moviendo
	for(int n=0;n<m;++n)
	{
		if(x[n]>0) cout<<setxy(x[n],y[n])<<(char)153;
	}
}

void lanzaAvion(int ax[],int ay[], int m)
{
	//buscamos si hay un par de variables de avion sin uso
	//sino hay no pasa nada
	for(int n=0;n<m;++n)
	{
		if(ax[n]==0)
		{
			ax[n]=2;
			ay[n]=rand()%10+5;
			return;
		}
	}
}

void lanzabomba(int x,int y,int bx[],int by[],int m)
{
	//buscamos si hay un par de variables de bomba sin uso
	//sino hay no pasa nada
	for(int n=0;n<m;++n)
	{
		if(bx[n]==0)
		{
			bx[n]=x+3;
			by[n]=y+2;
			return;
		}
	}
}

void caidaBomba(int bx[],int by[],int m)
{
	//buscamos las coordenadas diferentes de 0 que son las que se estan moviendo
	for(int n=0;n<m;++n)
	{
		if(bx[n]>0)
		{
			cout<<setxy(bx[n],by[n])<<" "; //borramos bomba posici?n anterior
			++bx[n];
			++by[n];
			if((bx[n]>=bder)||(by[n]>=binf)) //verificamos si se sale de los bordes
			{
				bx[n]=0; //variables disponibles para pr?xima bomba
				by[n]=0;
			}
		}
	}
}

void disparoIzq(int x,int y,int tx[],int ty[],int td[],int m)
{
	//se busca un par de variables libres para usar, si no hay o habr? disparo alguno
	for(int n=0;n<m;++n)
	{
		if(tx[n]==0)
		{
			tx[n]=x-1;
			ty[n]=y-1;
			td[n]=-1;
			return;
		}
	}
}

void disparoDer(int x,int y,int tx[],int ty[],int td[],int m)
{
	//se busca un par de variables libres para usar, si no hay o habr? disparo alguno
	for(int n=0;n<m;++n)
	{
		if(tx[n]==0)
		{
			tx[n]=x+4;
			ty[n]=y-1;
			td[n]=1;
			return;
		}
	}
}

void avanceDisparo(int tx[],int ty[],int td[],int m)
{
	//primeros vemos si hay alg?n disparo en vuelo y si lo hay lo movemos seg?n su direcci?n
	for(int n=0;n<m;++n)
	{
		if(tx[n]>0)
		{
			cout<<setxy(tx[n],ty[n])<<" "; //borramos tiro posici?n anterior
			tx[n]+=td[n];
			--ty[n];
			if((tx[n]>=bder)||(tx[n]<=bizq)||(ty[n]<=bsup)) //verificamos si se sale de los bordes
			{
				tx[n]=0;
				ty[n]=0;
				td[n]=0;
			}
		}
	}
}

void imprTiro(int x[],int y[],int d[],int m)
{
	for(int n=0;n<m;++n)
	{
		if(x[n]<=0) continue; //no hay disparo para imprimir revisar siguiente
		cout<<setxy(x[n],y[n]);
		if(d[n]==1)
		{
			cout<<"/";
		}
		else
			{
				cout<<"\\";
			}
	}
}

void colTirAvi(int ax[],int ay[],int am,int tx[],int ty[],int tm)
{  // hay que revisar todos los aviones con todos los disparos
	for(int i=0;i<am;++i)
	{
		if(ax[i]==0) continue; //si la coordenada x del avion es 0 no evaluar
		for(int j=0;j<tm;++j)
		{
			if(tx[j]==0) continue; //si la coordenada x del tiro es 0 no evaluar
			if((tx[j]>=ax[i])&&(tx[j]<=ax[i]+5)&&(ty[j]<=ay[i]+1)&&(ty[j]>=ay[i]))
			{
				// impacto avi?n i con disparo j
				borraBombardero(ax[i],ay[i]);
				ax[i]=0; //las coordenadas del avion a 0 para que esten disponibles
				ay[i]=0; //cuando se lanze el pr?ximo avion
				tx[j]=0; //las coordenadas del tiro a 0 para que esten disponibles
				ty[j]=0; //cuando se lanze el pr?ximo tiro
			}
		}
	}
	
	return;
}

bool colBombTanq(int x,int y,int bx[],int by[],int m)
{ //verdadero si una bomba golpeo el tanque
	//comparamos todas las bombas
	for(int n=0;n<m;++n)
		if((bx[n]>=x)&&(bx[n]<=x+2)&&(by[n]<=y+2)&&(by[n]>=y)) return true;
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
