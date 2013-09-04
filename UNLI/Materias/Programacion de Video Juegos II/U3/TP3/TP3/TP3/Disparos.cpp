#include "Disparos.h"

sf::Image Disparo::imgDisparo;
bool Disparo::init=false;

Disparo::Disparo(float x0, float y0, float vel){
	// cargamos la imagen solo una vez, por eso tanto la imagen como
	// init son estaticas
	if(!init){
		imgDisparo.LoadFromFile("../disparo.png");
		init=true;
	}
	// inicializamos posicion, vel e imagen del disparo
	SetPosition(x0, y0);
	SetImage(imgDisparo);
	velx=vel;
};


// recorre la lista de disparos, si el disparo se encuentra fuera de la region
// dada por r, el disparo se elimina de la lista, sino se mueve
void ManejadorDisparos::MoverDisparos(float dt, sf::FloatRect &r){
	list<Disparo>::iterator p=disparos.begin();
	float misilx;
	while(p!=disparos.end()){
		misilx=(*p).GetPosition().x;
		if(misilx<r.Left || misilx>r.Right){
			// al borrar, el iterador p se invalida, por lo que
			// debemos actualizarlo
			p=disparos.erase(p);
		}else{
			// movemos el disparo
			p->Move(p->velx*dt, 0);
			p++;
		}
	}
}


// agrega un nuevo disparo a la lista con la posicion y velocidad dadas
void ManejadorDisparos::AgregarDisparo(float x, float y, float vel){
	disparos.insert(disparos.end(), Disparo(x, y, vel));
}


// recorre la lista de disparos y los dibuja
void ManejadorDisparos::DibujarDisparos(sf::RenderWindow &w){
	list<Disparo>::iterator p=disparos.begin();
	while(p!=disparos.end()){
		w.Draw(*p);
		p++;
	}
}
