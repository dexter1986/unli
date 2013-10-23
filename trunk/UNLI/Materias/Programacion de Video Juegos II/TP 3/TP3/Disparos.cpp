#include "Disparos.h"


bool Disparo::init=false;

Disparo::Disparo(float x0, float y0, float vel){	
	// inicializamos posicion, vel e imagen del disparo
	const sf::Image &imgDisparo = TextureManager::GetInstance().GetTexture("../data/disparo.png");
	SetPosition(x0, y0);
	SetImage(imgDisparo);
	SetScale(0.9,0.9);
	velx=vel;
};

void ManejadorDisparos::Init()
{
	disparos.clear();	
};

ManejadorDisparos::~ManejadorDisparos()
{
	disparos.clear();	
}

// recorre la lista de disparos, si el disparo se encuentra fuera de la region
// dada por r, el disparo se elimina de la lista, sino se mueve
void ManejadorDisparos::MoverDisparos(float dt, sf::View &v){
	list<Disparo>::iterator p=disparos.begin();
	float misilx;
	sf::FloatRect r=v.GetRect();
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
