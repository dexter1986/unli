#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;
#define G 9.8 //aceleracion de la gravedad 9,8 m/s
#define PI 3.14162

int main(int argc, char *argv[]) {
	float d; //variable que contendra la distancia al blanco
	float V0; //velocidad del avion
	float t; //Temporizador
	int h; //altura del avion
	srand(time(NULL)); 
	h = rand()%1001+1000; //se obtiene la altura al azar
	V0 = rand()%201+100; //se obtiene la velocidad al azar
	d = rand()%2001+6000; //se obtiene una distancia al azar
	cout.precision(2);	
	cout<<"******************************************************************"<<endl;	
	cout<<"*"<<"                            Hiroshima                           "<<"*"<<endl;;
	cout<<"******************************************************************"<<endl;		
	cout<<"Agosto 6, 1945. 08:12AM."<<endl<<"Un B29 denominado Enola Gay sobrevuela cerca de la ciudad Hiroshima."<<endl;
	cout<<"Alguien de la tripulacion da la alerta diciendo \"Objetivo a la vista\""<<endl;	
	cout<<"Tu mision es configurar el temporizador de lanzamiento del Little Boy."<<endl;
	cout<<endl<<"Estas listo para comenzar?"<<endl;
	system("PAUSE");
	cout<<endl<<"Datos del vuelo"<<endl;
	cout<<"----------------------------"<<endl;
	cout<<fixed<<"Altura: "<<h<<" metros."<<endl;
	cout<<fixed<<"Velocidad: "<<V0<<" m/s."<<endl;
	cout<<fixed<<"Distancia objetivo: "<<d<<" metros."<<endl;
	cout<<fixed<<"Tiempo restante: "<<d/V0<<" segundos."<<endl<<endl;	
	cout<<"Es hora de configurar el temporizador."<<endl<<"Recuerda que el tiempo que ingreses sera el tiempo en que "<<endl<<"tarda en soltar la bomba"<<endl;
	cout<<"Dispones de 5 intentos."<<endl<<endl;
	cout<<"Primer intento"<<endl;
	cout<<"Ingresa el valor: ";
	cin>>t;
	float tv; //Tiempo vuelo de la bomba	
	float xv; //Distacia alcanzada por la bomba
	float xr; //distancia existente entre la bomba al momento de ser lanzada y el blanco
	tv = sqrt(2*h/G);
	xv = V0*tv;
	
	xr = (d/V0 - t)*V0;
	
	cout<<endl<<"--------------- Ayudita ----------------"<<endl;
	cout<<fixed<<"Distancia al blanco             "<<xr<<endl;
	cout<<fixed<<"tiempo de vuelo de la bomba       "<<tv<<endl;
	cout<<fixed<<"Distancia recorrida de la bomba "<<xv<<endl; 
	cout<<"----------------------------------------"<<endl<<endl;
	
	cout<<fixed<<"Estuviste a "<<xv-xr<<" metros del blanco."<<endl<<endl;
	
	cout<<"Segundo intento"<<endl;
	cout<<"Ingresa el valor: ";
	cin>>t;
	
	xr = (d/V0 - t)*V0;	
	
	cout<<endl<<"--------------- Ayudita ----------------"<<endl;
	cout<<fixed<<"Distancia al blanco             "<<xr<<endl;
	cout<<fixed<<"tiempo de vuelo de la bomba       "<<tv<<endl;
	cout<<fixed<<"Distancia recorrida de la bomba "<<xv<<endl; 
	cout<<"----------------------------------------"<<endl<<endl;
	
	cout<<fixed<<"Estuviste a "<<xv-xr<<" metros del blanco."<<endl<<endl;
		
	cout<<"Tercer intento"<<endl;
	cout<<"Ingresa el valor: ";
	cin>>t;
	
	xr = (d/V0 - t)*V0;	
	
	cout<<endl<<"--------------- Ayudita ----------------"<<endl;
	cout<<fixed<<"Distancia al blanco             "<<xr<<endl;
	cout<<fixed<<"tiempo de vuelo de la bomba       "<<tv<<endl;
	cout<<fixed<<"Distancia recorrida de la bomba "<<xv<<endl; 
	cout<<"----------------------------------------"<<endl<<endl;
	
	cout<<fixed<<"Estuviste a "<<xv-xr<<" metros del blanco."<<endl<<endl;
		
	cout<<"Cuarto intento"<<endl;
	cout<<"Ingresa el valor: ";
	cin>>t;
	
	xr = (d/V0 - t)*V0;	
	
	cout<<endl<<"--------------- Ayudita ----------------"<<endl;
	cout<<fixed<<"Distancia al blanco             "<<xr<<endl;
	cout<<fixed<<"tiempo de vuelo de la bomba       "<<tv<<endl;
	cout<<fixed<<"Distancia recorrida de la bomba "<<xv<<endl; 
	cout<<"----------------------------------------"<<endl<<endl;
	
	cout<<fixed<<"Estuviste a "<<xv-xr<<" metros del blanco."<<endl<<endl;
	
	cout<<"Ultimo intento"<<endl;
	cout<<"Ingresa el valor: ";
	cin>>t;
	
	xr = (d/V0 - t)*V0;	
	
	cout<<endl<<"--------------- Ayudita ----------------"<<endl;
	cout<<fixed<<"Distancia al blanco             "<<xr<<endl;
	cout<<fixed<<"tiempo de vuelo de la bomba       "<<tv<<endl;
	cout<<fixed<<"Distancia recorrida de la bomba "<<xv<<endl; 
	cout<<"----------------------------------------"<<endl<<endl;
	
	cout<<fixed<<"Estuviste a "<<xv-xr<<" metros del blanco."<<endl<<endl;
		
	cout<<endl<<endl<<"Gracias por jugar";		
	cout<<endl<<"Porque no lo intentas otra vez?"<<endl;
	system("PAUSE"); //espera la pulsacion de una tecla
	cout<<endl<<"Hasta luego..";
	return 0;
}
