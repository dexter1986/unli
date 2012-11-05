/*
Este ejemplo muestra un de los usos de las funciones que es dividir un problema
complejo en peque?os subproblemas m?s simples

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

Algoritmo

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

*/
#include <constream>
#include <ctime>
#include <windows.h>

using namespace conio;
using namespace std;

//declaraciones de los prototipos de las funciones
void imprBombardero(int x, int y);
void borraBombardero(int x, int y);
void imprTanque(int x, int y);
void explotaTanque(int x,int y);
void imprBomba(int x,int y);
void lanzaAvion(int &x1,int &y1,int &x2,int &y2,int &x3,int &y3);
void lanzabomba(int x,int y,int &bx1,int &by1,int &bx2,int &by2,int &bx3,int &by3);
void caidaBomba(int &bx1,int &by1,int &bx2,int &by2,int &bx3,int &by3);
void disparoIzq(int x,int y,int &tx1,int &ty1,int &td1,int &tx2,int &ty2,int &td2,int &tx3,int &ty3,int &td3);
void disparoDer(int x,int y,int &tx1,int &ty1,int &td1,int &tx2,int &ty2,int &td2,int &tx3,int &ty3,int &td3);
void avanceDisparo(int &tx1,int &ty1,int &td1,int &tx2,int &ty2,int &td2,int &tx3,int &ty3,int &td3);
void imprTiro(int x,int y,int d);
void explotaTanque(int x,int y);
int colTirAvi(int x,int y,int tx1,int ty1,int tx2,int ty2,int tx3,int ty3);
bool colBombTanq(int x,int y,int bx1,int by1,int bx2,int by2,int bx3,int by3);

//declaraciones de las variables globales
const int bizq=1;  //limites de los bordes
const int bder=80; //est?n declarados globalmente
const int bsup=1;  //para que todas las funciones puedan usarlas
const int binf=24; //de aqu? en adelante


int main() {
		
	int x1,x2,x3; //coordenadas x de los aviones
	int y1,y2,y3; //coordenadas y de los aviones
	int x,y; //coordenadas x y de nuestro veh?culo
	int bx1,bx2,bx3; //hasta 3 bombas al mismo tiempo
	int by1,by2,by3;
	int tx1,tx2,tx3; //hasta 3 tiros al mismo tiempo
	int ty1,ty2,ty3;
	int td1,td2,td3; //direcci?n del tiro -1 izquierda +1 derecha
	
	char t;
	int n;
	
	int tam=3;
	
	x1=x2=x3=0; //inicializamos a cero
	y1=y2=y3=0; // cuando las coordenadas son imprimibles esta en carrera
	
	bx1=bx2=bx3=0;
	by1=by2=by3=0;
	
	tx1=tx2=tx3=0;
	ty1=ty2=ty3=0;
	td1=td2=td3=0;
	
	x=38;
	y=21;
	
	srand(time(NULL));  //se inicializa el azar
	
	cout<<clrscr; //borramos la pantalla
	
	while(true)
	{
		
		if(x1>1)  //avanzamos avi?n 1 si esta en carrera
		{
			if(rand()%30==0) lanzabomba(x1,y1,bx1,by1,bx2,by2,bx3,by3);
			++x1;
			
			if(x1>73)
			{
				borraBombardero(x1,y1);
				x1=0;
			}
		}
		if(x2>1)  //avanzamos avi?n 2 si esta en carrera
		{
			if(rand()%30==0) lanzabomba(x2,y2,bx1,by1,bx2,by2,bx3,by3);
			++x2;
			
			if(x2>73)
			{
				borraBombardero(x2,y2);
				x2=0;
			}
		}
		if(x3>1)  //avanzamos avi?n 3 si esta en carrera
		{
			if(rand()%30==0) lanzabomba(x3,y3,bx1,by1,bx2,by2,bx3,by3);
			++x3;
			
			if(x3>73)
			{
				borraBombardero(x3,y3);
				x3=0;
			}
		}
		
		//?Nuevo avi?n?
		if(rand()%20==0) lanzaAvion(x1,y1,x2,y2,x3,y3);
		
		//ca?da de bomba
		caidaBomba(bx1,by1,bx2,by2,bx3,by3);
		//avance de tiro
		avanceDisparo(tx1,ty1,td1,tx2,ty2,td2,tx3,ty3,td3);
		
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
			if(t=='1') disparoIzq(x,y,tx1,ty1,td1,tx2,ty2,td2,tx3,ty3,td3);
			if(t=='2') disparoDer(x,y,tx1,ty1,td1,tx2,ty2,td2,tx3,ty3,td3);
		}
		
		//colisiones
		//colisi?n tiro-avion
		n=colTirAvi(x1,y1,tx1,ty1,tx2,ty2,tx3,ty3);
		if(n) //avion 1
		{
			borraBombardero(x1,y1);
			x1=0;
			y1=0;
			switch(n) //dependiendo de cual tiro hay que borrar las variables que usa
			{
			case 1:
				tx1=0;
				ty1=0;
				td1=0;
				break;
			case 2:
				tx2=0;
				ty2=0;
				td2=0;
				break;
			case 3:
				tx3=0;
				ty3=0;
				td3=0;
				break;
			}
		}
		n=colTirAvi(x2,y2,tx1,ty1,tx2,ty2,tx3,ty3);
		if(n) //avion 2
		{
			borraBombardero(x2,y2);
			x2=0;
			y2=0;
			switch(n) //dependiendo de cual tiro hay que borrar las variables que usa
			{
			case 1:
				tx1=0;
				ty1=0;
				td1=0;
				break;
			case 2:
				tx2=0;
				ty2=0;
				td2=0;
				break;
			case 3:
				tx3=0;
				ty3=0;
				td3=0;
				break;
			}
		}
		n=colTirAvi(x3,y3,tx1,ty1,tx2,ty2,tx3,ty3);
		if(n) //avion 3
		{
			borraBombardero(x3,y3);
			x3=0;
			y3=0;
			switch(n) //dependiendo de cual tiro hay que borrar las variables que usa
			{
			case 1:
				tx1=0;
				ty1=0;
				td1=0;
				break;
			case 2:
				tx2=0;
				ty2=0;
				td2=0;
				break;
			case 3:
				tx3=0;
				ty3=0;
				td3=0;
				break;
			}
		}
		
		//colisi?n bomba-tanque
		
		if(colBombTanq(x,y,bx1,by1,bx2,by2,bx3,by3))
		{
			explotaTanque(x,y);
			break; //salimos del juego
		}
		
		//dibuja todo
		imprTiro(tx1,ty1,td1); //imprime tiro 1
		imprTiro(tx2,ty2,td2); //imprime tiro 2
		imprTiro(tx3,ty3,td3); //imprime tiro 3
		imprTanque(x,y); //imprime tanque
		imprBomba(bx1,by1); //imprime bomba 1
		imprBomba(bx2,by2); //imprime bomba 2
		imprBomba(bx3,by3); //imprime bomba 3
		imprBombardero(x1,y1); //imprimimos el avi?n n?mero 1
		imprBombardero(x2,y2); //imprimimos el avi?n n?mero 2
		imprBombardero(x3,y3); //imprimimos el avi?n n?mero 3
		
		Sleep(100);
	}
	
	return 0;
}

/* (char) este modificador cambia el n?mero siguiente al caracter correspondiente
tambi?n funciona a la inversa (int)'0' devuelve el codigo de caracter 0 que ser?a 48
Si se hace una asignaci?n esto lo hace en forma autom?tica llevandolo al tipo de
variable, por ejemplo int a='0' a valdr? 48 char a=48 contendra '0'*/

void imprBombardero(int x, int y) //dibuja un avi?n en las coordenadas (x, y)
{
	if((x<2)||(y<1)) return; // si las coordenadas no son imprimibles no se imprime
	cout<<setxy(x-1,y)<<" "<<(char)220<<"   "<<(char)218<<(char)191;
	cout<<setxy(x-1,y+1)<<" "<<(char)223<<(char)223<<(char)223<<(char)175<<(char)223<<(char)223;
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

void imprBomba(int x,int y)
{
	if(x>0) cout<<setxy(x,y)<<(char)153;
}

void lanzaAvion(int &x1,int &y1,int &x2,int &y2,int &x3,int &y3)
{
	//buscamos si hay un par de variables de avion sin uso
	//sino hay no pasa nada
	if(x1==0)
	{
		x1=2;
		y1=rand()%10+5;
		return;
	}
	if(x2==0)
	{
		x2=2;
		y2=rand()%10+5;
		return;
	}
	if(x3==0)
	{
		x3=2;
		y3=rand()%10+5;
	}
}

void lanzabomba(int x,int y,int &bx1,int &by1,int &bx2,int &by2,int &bx3,int &by3)
{
	//buscamos si hay un par de variables de bomba sin uso
	//sino hay no pasa nada
	if(bx1==0)
	{
		bx1=x+3;
		by1=y+2;
		return;
	}
	if(bx2==0)
	{
		bx2=x+3;
		by2=y+2;
		return;
	}
	if(bx3==0)
	{
		bx3=x+3;
		by3=y+2;
	}
}

void caidaBomba(int &bx1,int &by1,int &bx2,int &by2,int &bx3,int &by3)
{
	//buscamos si hay un par de variables de bomba en uso
	//sino hay no pasa nada
	if(bx1>0)
	{
		cout<<setxy(bx1,by1)<<" "; //borramos bomba posici?n anterior
		++bx1;
		++by1;
		if((bx1>=bder)||(by1>=binf)) //verificamos si se sale de los bordes
		{
			bx1=0;
			by1=0;
		}
	}
	if(bx2>0)
	{
		cout<<setxy(bx2,by2)<<" "; //borramos bomba posici?n anterior
		++bx2;
		++by2;
		if((bx2>=bder)||(by2>=binf)) //verificamos si se sale de los bordes
		{
			bx2=0;
			by2=0;
		}
	}
	if(bx3>0)
	{
		cout<<setxy(bx3,by3)<<" "; //borramos bomba posici?n anterior
		++bx3;
		++by3;
		if((bx3>=bder)||(by3>=binf)) //verificamos si se sale de los bordes
		{
			bx3=0;
			by3=0;
		}
	}
}

void disparoIzq(int x, int y,int &tx1,int &ty1,int &td1,int &tx2,int &ty2,int &td2,int &tx3,int &ty3,int &td3)
{
	//se busca un par de variables libres para usar, si no hay o habr? disparo alguno
	if(tx1==0)
	{
		tx1=x-1;
		ty1=y-1;
		td1=-1;
		return;
	}
	if(tx2==0)
	{
		tx2=x-1;
		ty2=y-1;
		td2=-1;
		return;
	}
	if(tx3==0)
	{
		tx3=x-1;
		ty3=y-1;
		td3=-1;
	}
}

void disparoDer(int x, int y,int &tx1,int &ty1,int &td1,int &tx2,int &ty2,int &td2,int &tx3,int &ty3,int &td3)
{
	//se busca un par de variables libres para usar, si no hay o habr? disparo alguno
	if(tx1==0)
	{
		tx1=x+4;
		ty1=y-1;
		td1=1;
		return;
	}
	if(tx2==0)
	{
		tx2=x+4;
		ty2=y-1;
		td2=1;
		return;
	}
	if(tx3==0)
	{
		tx3=x+4;
		ty3=y-1;
		td3=1;
	}
}

void avanceDisparo(int &tx1,int &ty1,int &td1,int &tx2,int &ty2,int &td2,int &tx3,int &ty3,int &td3)
{
	//primeros vemos si hay alg?n disparo en vuelo y si lo hay lo movemos seg?n su direcci?n
	if(tx1>0)
	{
		cout<<setxy(tx1,ty1)<<" "; //borramos tiro posici?n anterior
		tx1+=td1;
		--ty1;
		if((tx1>=bder)||(tx1<=bizq)||(ty1<=bsup)) //verificamos si se sale de los bordes
		{
			tx1=0;
			ty1=0;
			td1=0;
		}
	}
	if(tx2>0)
	{
		cout<<setxy(tx2,ty2)<<" "; //borramos tiro posici?n anterior
		tx2+=td2;
		--ty2;
		if((tx2>=bder)||(tx2<=bizq)||(ty2<=bsup)) //verificamos si se sale de los bordes
		{
			tx2=0;
			ty2=0;
			td2=0;
		}
	}
	if(tx3>0)
	{
		cout<<setxy(tx3,ty3)<<" "; //borramos tiro posici?n anterior
		tx3+=td3;
		--ty3;
		if((tx3>=bder)||(tx3<=bizq)||(ty3<=bsup)) //verificamos si se sale de los bordes
		{
			tx3=0;
			ty3=0;
			td3=0;
		}
	}
}

void imprTiro(int x,int y,int d)
{
	if(x<=0) return; //no hay disparo para imprimir
	cout<<setxy(x,y);
	if(d==1)
	{
		cout<<"/";
	}
	else
	{
		cout<<"\\";
	}
}

int colTirAvi(int x,int y,int tx1,int ty1,int tx2,int ty2,int tx3,int ty3)
{  // 1, 2 o 3 seg?n que variables de tiro dieron en el avion que est?n en (x,y)
	if((tx1>=x)&&(tx1<=x+5)&&(ty1<=y+1)&&(ty1>=y)) return 1;
	if((tx2>=x)&&(tx2<=x+5)&&(ty2<=y+1)&&(ty2>=y)) return 2;
	if((tx3>=x)&&(tx3<=x+5)&&(ty3<=y+1)&&(ty3>=y)) return 3;
	return 0;
}

bool colBombTanq(int x,int y,int bx1,int by1,int bx2,int by2,int bx3,int by3)
{ //verdadero si una bomba golpeo el tanque
	if((bx1>=x)&&(bx1<=x+2)&&(by1<=y+2)&&(by1>=y)) return true;
	if((bx2>=x)&&(bx2<=x+2)&&(by2<=y+2)&&(by2>=y)) return true;
	if((bx3>=x)&&(bx3<=x+2)&&(by3<=y+2)&&(by3>=y)) return true;
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
