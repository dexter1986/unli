#ifndef PARTICLESYSTEMMANAGER_H
#define PARTICLESYSTEMMANAGER_H

#include <list>
#include "Emitter.h"
#include "Affectors.h"
#include "ParticleSystem.h"


using namespace std;

class ParticleSystemManager{
private:
	// los sistemas de particulas
	list<ParticleSystem *> particlesystems;
	// el manejador global de sistemas de particulas
	static ParticleSystemManager *globalManager;

	// algunas variables utiles
	bool usePointSprites;
	bool pointSpritesSuported;

	ParticleSystemManager();
	
	
public:
	~ParticleSystemManager();
	// devuelve el manejador global
	static ParticleSystemManager &GetManager();
	// agrega un sistemas de particulas
	Emitter &AddParticleSystem(unsigned nMaxParticles=1000);
	// mueve todos los sistemas de particulas
	void Simulate(float dt);
	// dibuja todos los sistemas de particulas
	void Render(sf::RenderWindow &w);
	// dibuja todos los sistemas de particulas
	// utilizando la extension GL_POINT_SPRITES
	void Render_PointSprites(sf::RenderWindow &w);
	// devuelve la cantidad de particulas entre
	// todos los sistemas
	unsigned GetNumParticles();
};

#endif

