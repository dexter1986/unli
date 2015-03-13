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
		vector<Enemigo *>::iterator e = enemigos.begin();
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
	vector<Enemigo *>::iterator e=enemigos.begin();
	while(e!=enemigos.end())
	{
		(*e)->Mover_y_Animar(j,dt);
		e++;
	}
}


bool EntityManager::HayColision(float x, float y,sf::Color &color)
{
	bool isColl = false;

	vector<Enemigo *>::iterator e=enemigos.begin();
	while(e!=enemigos.end())
	{
		if((*e)->RecibirImpacto(x,y))
		{
			color = (*e)->GetColor();
			Enemigo *temp = (*e);
			e = enemigos.erase(e);
			delete temp;
			isColl = true;			
		}
		else
		{
			e++;
		}
	}

	return isColl;
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
	vector<Enemigo *>::iterator e= enemigos.begin();
	while(e!=enemigos.end())
	{
		(*e)->Draw(w);	
		e++;
	}
}

