#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

/****     CLASES       *****/

/********** Clase madre animal **********/

class animal {
	
	
public:
	int coordenadas[2]; // lleva las coordenadas del objeto
	
protected: 
  
	void avanzar(int); // un metodo que ambas clases derivadas tiene en comun
};


/********** Clase aguila, hereda animal **********/

class aguila : public animal {
	
	
public: 
	aguila();			// constructor
	void volar();		// llama al metodo avanzar, pero avanza 2 casilleros
	void costado(int);	// se mueve a los laterales segun el parametro
	void menu();		// muestras las opciones posibles del objeto
	
	
};

/********** Clase liebre, hereda animal **********/

class liebre : public animal {
	
public: 
	liebre();			// constructor
	void saltar();		// llama al metodo avanzar
	void diagonal(int); //se mueve en diagonal segun el parametro
	void menu();		//// muestras las opciones posibles del objeto
};

/********** Clase juego, es la que mantiene la llamada a los metodos 
contiene un objeto liebre y un objeto aguila
**********/

class juego {
	
public:
	juego();		//constructor
	aguila A;		// objeto aguila
	liebre L;		//objeto liebre
	
	bool ganador;	// bandera que se activa cuando hay un ganador
	char gano;		//la clase ganadora
	void start();	//metodo que mantiene el ciclo del juego
	int gano_liebre();	//metodo de interfaz cuando gana la liebre
	int gano_aguila();	//metodo de interfaz cuando gana el aguila
	
private:
	char terreno[7][20];	//Terreno de juego
	char turno;				//turno del jugador de turno
	
	void cambia_turno();	//cambia el turno del jugador
	void arma_terreno();	//arma el terreno por unica vez
	void mostrar();			//crea una interfaz
	void mostrar_menu();	//llama a los metodos de muestra de las clases
	void ingresar();		//maneja el ingreso de datos
	void actuar(int);		//toma accion sobre la opcion elegida por el usuario
	void busca_ganador();	//detecta si hay un ganador

}; 

/************ IMPLEMENTACIONES ******************/
/************************************************/
/************************************************/
/************************************************/


/************************************************/
/*             CLASE ANIMAL                     */
/************************************************/

/* metodo avanzar compartido por las cases derivadas */

void animal::avanzar(int a){
	
	coordenadas[1]+=a;
}


/************************************************/
/*             CLASE LIEBRE                      */
/************************************************/

/* constructor */

liebre::liebre(){
	coordenadas[0]=3;
	coordenadas[1]=5;
}

/* muestra el menu de las opciones */

void liebre::menu(){
	cout<<endl<<"Jugador Liebre elige movimiento"<<endl;
	cout<<setw(5)<<"1: saltar"<<endl;
	cout<<setw(5)<<"2: diagonal abajo"<<endl;
	cout<<setw(5)<<"3: diagonal arriba"<<endl;
	cout<<setw(5)<<"4: pasar turno"<<endl;
	
}

/* corre las coordendas hacia las diagonales */

void liebre::diagonal(int a){
			
	if (a == 1){
		if (coordenadas[0]<5)
			coordenadas[0]++;
		
		
	}	
	else{
		if (coordenadas[0]>1)
			coordenadas[0]--;
		
	}
	
	coordenadas[1]++;	
	
}

/* usa el metodo de la case base, avanza 1 */

void liebre::saltar(){
	avanzar(1);
}


/************************************************/
/*             CLASE AGUILA                      */
/************************************************/


/* constructor */

aguila::aguila(){
	coordenadas[0]=3;
	coordenadas[1]=2;
}

/* muestra el menu de las opciones */

void aguila::menu(){
	cout<<endl<<"Jugador Aguila elige movimiento"<<endl;
	cout<<setw(5)<<"1: volar"<<endl;
	cout<<setw(5)<<"2: abajo"<<endl;
	cout<<setw(5)<<"3: arriba"<<endl;
	cout<<setw(5)<<"4: pasar turno"<<endl;
	
}        

/* corre las coordendas hacia los laterales */
void aguila::costado(int a){
	
	
	if (a == 1){
		if (coordenadas[0]<5)
			coordenadas[0]++;
		
		
	}	
	else{
		if (coordenadas[0]>1)
			coordenadas[0]--;
		
	}
		
}

/* usa el metodo de la case base, avanza 2 */

void aguila::volar(){
	avanzar(2);
}

/************************************************/
/*             CLASE JUEGO                      */
/************************************************/

/* constructor */

juego::juego(){
	arma_terreno();
	turno = 'L';
	ganador=false;
	gano = 'A';
}

/* arma terreno por unica vez */

void juego::arma_terreno(){
	
	
	for(int i=0;i<20;i++){
		terreno[0][i]='=';
		terreno[6][i]='=';
	}
	
	for(int i=0;i<7;i++){
		terreno[i][0] ='|';
		terreno[i][19]='|';
	}
	
	for (int i=1;i<6;i++){
		for (int j=1;j<19;j++){
			terreno[i][j]=' ';
		}
	}
	

	
	terreno[A.coordenadas[0]][A.coordenadas[1]]='A';
	terreno[L.coordenadas[0]][L.coordenadas[1]]='L';
	}
    

/* crea la interfaz grafica */

void juego::mostrar(){
	
	for (int i=1;i<6;i++){
		for(int k=1;k<19;k++){
			terreno[i][k]=' ';
		}
	}
	
	terreno[A.coordenadas[0]][A.coordenadas[1]]='A';
	terreno[L.coordenadas[0]][L.coordenadas[1]]='L';
	
	for (int i=0;i<7;i++){
		for(int k=0;k<20;k++){
			cout<<setw(2)<<terreno[i][k];
		}
		cout<<endl<<endl;;
		
	}
	
	
	
	
	
}

/* muestra el menu de los objetos */

void juego::mostrar_menu(){
	(turno == 'L') ? L.menu() : A.menu();
}

/* controla el ingreso de datos del usuario */

void juego::ingresar(){
	
	mostrar_menu();
	int op;
	cout<<"Elige: ";
	cin>>op;
	
	while (op>4 || op<1){
		mostrar_menu();
		cout<<"Opcion incorrecta, eliga nuevamente: ";
		cin>>op;           
	}
	
	actuar(op);
	
}

/* toma aciones segun la opcion elegida por el usuario */

void juego::actuar(int op){
	
	switch(op){
	case 1:
		(turno == 'L') ? L.saltar() : A.volar();break;
	case 2:	
		(turno == 'L') ? L.diagonal(1) : A.costado(1);break;
	case 3:	
		(turno == 'L') ? L.diagonal(2) : A.costado(2);break;	
	case 4:	
		(turno == 'L') ? turno = 'L' : turno = 'A';break;
	}
}

/* cambia el turno del jugador*/

void juego::cambia_turno(){
	turno = (turno == 'L') ? 'A' : 'L';
}

/* detecta si hay un ganador */

void juego::busca_ganador(){
	
	if (L.coordenadas[1]>18){
		
		gano = 'L';
		ganador=true;
	}
	
	if(L.coordenadas[0] == A.coordenadas[0] && L.coordenadas[1] == A.coordenadas[1])
	{	
		gano = 'A';
		ganador=true;
	}
}


/* muestra interfaz de la victoria de la liebre */

int juego::gano_liebre(){
	
	cout<<"Gano Liebre"<<endl<<endl;
	cout<<" () ()"<<endl;
	cout<<" (`.`)"<<endl;
	cout<<"(``)(``)"<<endl;
	
	return 1;
	
}

/* muestra interfaz de la victoria del aguila */

int juego::gano_aguila(){
	
	cout<<"LIEBRE CAPTURADA"<<endl;
	
	return 1;
}

/* metodo que controla el ciclo de juego */

void juego::start(){
	
	int cont=0;
	
	while((!ganador) && (cont<40)){
		mostrar();
		ingresar();
		mostrar();
		cambia_turno();
		busca_ganador();
		cout<<"Quedan: "<<30-cont<<" turnos"<<endl;
		cont++;
	}
	
	if(cont==30){
		cout<<endl<<"Gano aguila por pasar 30 turnos";
	}
	else{
		int a=(gano == 'L') ? gano_liebre() : gano_aguila();
	}
	
}



/************************************************/
/*            MAIN                              */
/************************************************/

int main(int argc, char *argv[])
{
	
	juego J;
	J.start();
	
	
	return 1;
}
