#include "Disparos.h"

bool Disparo::init=false;

Disparo::Disparo(float x0, float y0, float vel,bool isNPC){	
	// inicializamos posicion, vel e imagen del disparo
	const sf::Image &imgDisparo = TextureManager::GetInstance().GetTexture("../data/disparo.png");
	SetPosition(x0, y0);
	SetImage(imgDisparo);
	SetScale(0.9,0.9);
	velx=vel;
	this->isNPC = isNPC;
};

Disparo::~Disparo(void)
{

}

void ManejadorDisparos::Init()
{
	disparos.clear();	
};


 ManejadorDisparos::ManejadorDisparos()
{
};

void  ManejadorDisparos::SetScene(SceneBase *s)
{
	scene = s;
}

ManejadorDisparos::~ManejadorDisparos()
{
	Disparo *disparoTemp;
	list<Disparo *>::iterator p=disparos.begin();
	while(p!=disparos.end()){
		disparoTemp = (*p);
		p=disparos.erase(p);
		delete disparoTemp;
	}
	disparos.clear();	
}

void ManejadorDisparos::SetLevelManager(Nivel *n)
{
	nivel = n;
}

// recorre la lista de disparos, si el disparo se encuentra fuera de la region
// dada por r, el disparo se elimina de la lista, sino se mueve
void ManejadorDisparos::MoverDisparos(float dt, sf::View &v){	
	float misilx;
	float misily;
	bool isNPC;
	int tipo  = 0;
	Color color = Color::White;
	sf::FloatRect r=v.GetRect();

	Disparo *disparoTemp;

	list<Disparo *>::iterator p=disparos.begin();
	while(p!=disparos.end()){
		
		(*p)->Move((*p)->velx*dt, 0);
		
		misilx = (*p)->GetPosition().x;
		misily = (*p)->GetPosition().y;
		isNPC = (*p)->isNPC;
		//verifica colision con las paredes
		if(misilx > r.Left && misilx < r.Right * 2)
		{
			if(nivel->HayColision(misilx,misily,tipo))
			{
				ParticleSystemManager::GetManager().CreateEmiterOneShoot(misilx,misily);
				
				// al borrar, el iterador p se invalida, por lo que
				// debemos actualizarlo
				disparoTemp = (*p);
				p=disparos.erase(p);
				delete disparoTemp;
			}
			else if(scene->HayColision(misilx,misily,color,isNPC))
			{
				ParticleSystemManager::GetManager().CreateEmiterOneExplosion(misilx,misily,color);

				// al borrar, el iterador p se invalida, por lo que
				// debemos actualizarlo
				disparoTemp = (*p);
				p=disparos.erase(p);
				delete disparoTemp;
			}
			else
			{			
				p++;
			}
		}
		else
		{
			// al borrar, el iterador p se invalida, por lo que
			// debemos actualizarlo
			disparoTemp = (*p);
			p=disparos.erase(p);
			delete disparoTemp;
		}		
	}
}

// agrega un nuevo disparo a la lista con la posicion y velocidad dadas
void ManejadorDisparos::AgregarDisparo(float x, float y, float vel,bool isNPC){
	disparos.push_back(new Disparo(x, y, vel,isNPC));
}

// recorre la lista de disparos y los dibuja
void ManejadorDisparos::DibujarDisparos(sf::RenderWindow &w){	
	list<Disparo *>::iterator p=disparos.begin();
	while(p!=disparos.end()){		
		Disparo *d = (*p);
		w.Draw(*d);
		p++;
	}
}
