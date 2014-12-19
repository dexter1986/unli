#include "EntityManager.h"

EntityManager::EntityManager(GameEngine *e)
{
	engine = e;
}

EntityManager::~EntityManager(void)
{
	Init();
}

void EntityManager::AiTracker(Personaje *p)
{
	target = p;
}

void EntityManager::Init()
{
	if(enemigos.size() > 0)
	{
		Enemigo *etemp;
		list<Enemigo *>::iterator e = enemigos.begin();
		while(e != enemigos.end())
		{
			etemp = (*e);
			e = enemigos.erase(e);
			delete etemp;
		}
		enemigos.clear();
	}
}

void EntityManager::Mover(Joystick &j, float dt)
{
	list<Enemigo *>::iterator e=enemigos.begin();
	while(e!=enemigos.end())
	{
		(*e)->Mover_y_Animar(j,dt);
		e++;
	}
}


bool EntityManager::HayColision(float x, float y,sf::Color &color)
{
	list<Enemigo *>::iterator e=enemigos.begin();
	while(e!=enemigos.end())
	{
		if((*e)->RecibirImpacto(x,y))
		{
			color = (*e)->GetColor();
			Enemigo *temp = (*e);
			enemigos.erase(e);
			delete temp;
			return true;
		}
		e++;
	}
	return false;
}


void EntityManager::SetEnvironment(ManejadorDisparos *d,Nivel *n)
{
	disparos = d;	
	nivel = n;
}

void EntityManager::Agregar(Enemigo *entity)
{
	entity->Inicializar(disparos,nivel);		
	entity->AiTracker(target);
	enemigos.push_back(entity);
}

void EntityManager::Dibujar(sf::RenderWindow &w)
{
	list<Enemigo *>::iterator e= enemigos.begin();
	while(e!=enemigos.end())
	{
		(*e)->Draw(w);	
		e++;
	}
}

