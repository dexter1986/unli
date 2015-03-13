#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <list>
#include <vector>
#include "Personaje.h"
#include "Enemigo.h"

class Enemigo;
class Personaje;

class EntityManager
{
private:
	vector<Enemigo *> enemigos;	
	Personaje *target;
	ManejadorDisparos *disparos;
	Nivel *nivel;
	GameEngine *engine;
public:
	bool HayColision(float x, float y,sf::Color &color);
	void SetEnvironment(ManejadorDisparos *d,Nivel *n);
	void AiTracker(Personaje *p);	
	void Init();
	void Mover(Joystick &j, float dt);		
	void Agregar(Enemigo *entity);
	void Dibujar(sf::RenderWindow &w);	
	EntityManager(GameEngine *e);
	~EntityManager(void);
};

