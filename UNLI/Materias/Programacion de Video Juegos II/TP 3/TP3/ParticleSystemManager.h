#ifndef PARTICLESYSTEMMANAGER_H
#define PARTICLESYSTEMMANAGER_H

#include <list>
#include <vector>
#include "Emitter.h"
#include "Affectors.h"
#include "ParticleSystem.h"


using namespace std;

class ParticleSystemManager{
private:
	// los sistemas de particulas
	vector<ParticleSystem *> particlesystems;
	// el manejador global de sistemas de particulas
	
	//static ParticleSystemManager *globalManager;
	static ParticleSystemManager globalManager;


	// algunas variables utiles
	bool usePointSprites;
	bool pointSpritesSuported;

	ParticleSystemManager();
	
	vector<Affector *> affectors;

	
public:

	void AddAffector(Affector *a);
	void ClearAffectors();
	void Clear();
	void CreateEmiterOneShoot(float x, float y);
	void CreateEmiterOneExplosion(float x, float y,sf::Color color);
	~ParticleSystemManager();
	// devuelve el manejador global
	static ParticleSystemManager &GetManager();
	// agrega un sistemas de particulas
	Emitter &AddParticleSystem(unsigned nMaxParticles=10);
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

