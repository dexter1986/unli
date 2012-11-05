#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;
#define G 9.8 //aceleracion de la gravedad 9,8 m/s
#define PI 3.14162

int main(int argc, char *argv[]) {
	float a; //variable que contendra el angulo del disparo
	float d; //variable que contendra la distancia
	float V0; //velocidad inicial
	int x;
	srand(time(NULL)); //se obtiene una distancia al azar
	x=rand()%501+1000;
	cout.precision(2);	
	cout<<"******************************************************************"<<endl;	
	cout<<"*"<<"                         Tiro al Blanco                         "<<"*"<<endl;;
	cout<<"******************************************************************"<<endl;
	cout<<"* Instrucciones                                                  *"<<endl;
	cout<<"* Intenta dar en el Blanco para ello tienes cinco balas          *"<<endl;	
	cout<<"******************************************************************"<<endl;
	cout<<endl<<endl<<"El blanco se encuentra a "<<x<<" metros"<<endl;	
	cout<<endl<<"Estas listo para comenzar?"<<endl<<endl;
	system("PAUSE");
		
	cout<<endl<<endl<<"Pimer intento\n\n";	
	cout<<"introduce la velocidad de disparo: ";
	cin>>V0;
	cout<<"introduce el angulo de disparo: ";
	cin>>a;
	d=pow(V0,2)*sin(2*a*PI/180)/G; //calculo de la distancia		
	cout<<fixed<<"\nLa bala cayo a "<<d<<" metros.\n";	
	cout<<fixed<<"Estuviste a "<<d-x<<" metros del blanco.\n";	
	
	cout<<endl<<endl<<"Segundo intento\n";
	cout<<"introduce la velocidad de disparo: ";
	cin>>V0;
	cout<<"introduce el angulo de disparo: ";
	cin>>a;
	d=pow(V0,2)*sin(2*a*PI/180)/G; //calculo de la distancia
	cout<<fixed<<"\nLa bala cayo a "<<d<<" metros.\n";	
	cout<<fixed<<"Estuviste a "<<d-x<<" metros del blanco.\n";
	
	cout<<endl<<endl<<"Tercer intento:\n";
	cout<<"introduce la velocidad de disparo: ";
	cin>>V0;
	cout<<"introduce el angulo de disparo: ";
	cin>>a;
	d=pow(V0,2)*sin(2*a*PI/180)/G; //calculo de la distancia
	cout<<fixed<<"\nLa bala cayo a "<<d<<" metros.\n";	
	cout<<fixed<<"Estuviste a "<<d-x<<" metros del blanco.\n";
	
	cout<<endl<<"Cuarto intento:\n";
	cout<<"introduce la velocidad de disparo: ";
	cin>>V0;
	cout<<"introduce el angulo de disparo: ";
	cin>>a;
	d=pow(V0,2)*sin(2*a*PI/180)/G; //calculo de la distancia	
	cout<<fixed<<"\nLa bala cayo a "<<d<<" metros.\n";	
	cout<<fixed<<"Estuviste a "<<d-x<<" metros del blanco.\n";
	
	cout<<endl<<"Ultimo intento:\n";
	cout<<"introduce la velocidad de disparo: ";
	cin>>V0;
	cout<<"introduce el angulo de disparo: ";
	cin>>a;
	d=pow(V0,2)*sin(2*a*PI/180)/G; //calculo de la distancia
	cout<<fixed<<"\nLa bala cayo a "<<d<<" metros.\n";	
	cout<<fixed<<"Estuviste a "<<d-x<<" metros del blanco.\n";
	cout<<endl<<endl<<"Gracias por jugar";		
	cout<<endl<<"Porque no lo intentas otra vez?"<<endl;
	system("PAUSE"); //espera la pulsacion de una tecla
	cout<<endl<<"Hasta luego..";
	return 0;
}
