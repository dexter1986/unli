#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
#define G 9.8 //aceleraci?n de la gravedad 9,8 m/s
#define PI 3.14162

int main(int argc, char *argv[]) {
	float a; //variable que contendr? el ?ngulo del disparo
	float d; //variable que contendr? la distancia
	const float V0=55; //velocidad inicial 55 m/s
	const float OExpansiva=1; // distancia en la que la explosi?n hace da?o en metros
	int x; // metros donde est? el blanco
	int	n; // contador de disparo
	int s; // almacena el numero de sorteo para ventajas especiales
	int b=5; // cantidad de balas con las que iniciamos
	
	srand(time(NULL));  //se obtiene una distancia al azar
	x=rand()%201+100;
	
	cout<<"Intenta dar en el Blanco"<<endl<<"Para ello tienes cinco balas"<<endl;
	cout<<"Te indicare que tan lejos del blanco has hecho impacto"<<endl;
	cout<<"El blanco se encuentra a "<<x<<" metros"<<endl<<endl;
	
	n=1; //iniciamos el contador de disparos
	while(n<=b) //mientras nuestro contador sea menor igual a b en principio 5 (n=1,2,3,4,5)
	{
		cout<<"introduce el angulo de disparo "<<n<<": ";
		cin>>a;
		d=pow(V0,2)*sin(2*a*PI/180)/G; //c?lculo de la distancia
		cout<<"\nLa bala "<<n<<" cayo a "<<d<<" metros.\n";
		if(abs(x-d)<=OExpansiva) //si la distancia entre impacto y blanco es menor a Onda Expansiva
		{
			//acertamos al blanco
			cout<<"\n\nDiste en el blanco!!!  Solo te llevo: "<<n<<" disparos";
			break; //forzamos la salida del while ya que no es necesario seguir tirando
		}
		else
			{
				//erramos al blanco
				cout<<"Le has errado por "<<abs(x-d)<<" metros.\n";
			}
		
		s=rand()%8; // sorteo de ventajas 8 posibilidades un numero al azar de 0 a 7
		
		switch(s){
		case 0: // ganamos si o si
			cout<<"\nQue suerte!!! el ca?on se disparo solo y justo dio en el blanco\n\n";
			n=b;
			break;
		case 1: // perdemos si o si
			cout<<"\nUna bala a detonado dentro del ca?on y lo ha destruido, ya no puedes seguir tirando.\n\n";
			n=b;
			break;
		case 2: // ganamos un disparo m?s (es m?s frecuente 2 posibilidades en 8)
		case 3:
			cout<<"\nEl grupo de abastecimiento te ha traido una bala extra, ahora tienes "<<++b<<" disparos.\n\n";
			break;
		default: //no hay novedades
			cout<<"\nSin novedades, sigue intentandolo\n\n";
		}
		
		++n; //siguiente disparo, incrementamos nuestro contador de disparo en 1
	}
	// si la ejecuci?n llega aca es porque n>b
	cout<<"\n\nEL PROGRAMA HA TERMINADO\n"<<M_PI;
	
	system("PAUSE"); //espera la pulsaci?n de una tecla
	return 0;
}
