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
	int x,n;
	srand(time(NULL));  //se obtiene una distancia al azar
	x=rand()%201+100;
	cout<<"Intenta dar en el Blanco"<<endl<<"Para ello tienes cinco balas"<<endl;
	cout<<"Te indicare que tan lejos del blanco has hecho impacto"<<endl;
	cout<<"El blanco se encuentra a "<<x<<" metros"<<endl<<endl;
	n=1; //iniciamos el contador de disparos
	do //entramos a la estructura, la primera vez se ejecuta si o si
	{
		cout<<"introduce el angulo de disparo "<<n<<": ";
		cin>>a;
		d=pow(V0,2)*sin(2*a*PI/180)/G; //c?lculo de la distancia
		cout<<"\nLa bala "<<n<<" cayo a "<<d<<" metros.\n";
		++n; //siguiente disparo, incrementamos nuestro contador en 1
	}
	while(n<6); //mientras nuestro contador sea menor que 6 (n=1,2,3,4,5);
	// si la ejecuci?n llega aca es porque n>5 (n=6,7,8....)
	cout<<"\n\nEL PROGRAMA HA TERMINADO\n";
	
	system("PAUSE"); //espera la pulsaci?n de una tecla
	return 0;
}
