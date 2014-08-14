#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <list>
#include "Enemigo.h"
#include "Disparos.h"

class EntityManager
{
private:
	list<Enemigo *> enemigos;	
	Personaje *target;
	ManejadorDisparos *disparos;
	Nivel *nivel;
public:
	bool HayColision(float x, float y,sf::Color &color);
	void SetEnvironment(ManejadorDisparos *d,Nivel *n);
	void AiTracker(Personaje *p);	
	void Init();
	void Mover(Joystick j, float dt);	
	void Agregar(Enemigo *entity);
	void Dibujar(sf::RenderWindow &w);	
	EntityManager(void);
	~EntityManager(void);
};

