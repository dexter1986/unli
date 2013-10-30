#ifndef EMITTER_H
#define EMITTER_H
#include <SFML/Graphics.hpp>
#include "Affector.h"
#include <vector>
#include <cmath>
using namespace std;

#ifndef M_PI
	#define M_PI 3.1416
#endif


class Emitter: public sf::Sprite{
	private:
	// medias de velocidad y angulo de emision y vida
	float emitVel, emitAngle, emitLife;
	// desvios de velocidad y angulo de emision y vida
	float deltaVel, deltaAngle, deltaLife;
	// tasa de creacion de particulas
	float spawnRate;
	// si debe crear nuevas particulas o destruirse
	bool spawn, kill;
	
	// los afectadores del sistema de particulas
	vector<Affector *> affectors;
	
	// constructor, es utilizado por
	// la clase ParticleSystemManager
	Emitter(float emitVel=5, float emitAngle=M_PI,
			float emitLife=3, float deltaVel=0,
			float deltaAngle=M_PI, float deltaLife=1,
			float spawnRate=10,bool oneTime=false);
	
	public:
	//Solo emite una vez. simula una explosion
	bool isOneTime;

	// agrega un affector al emisor
	void AddAffector(Affector &e);
	// permite controlar parametros de la emision
	void SetEmmitVel(float vel, float deltaVel=0);
	void SetEmmitAngle(float angle, float deltaAngle=0);
	void SetEmmitLife(float life, float deltaLife=0);
	void SetSpawnRate(float newSpawnRate);
	float GetSpawnRate(){return spawnRate;};
	
	// indica si el emisor debe o no crear
	// nuevas particulas
	void Spawn(bool spawn);
	
	// senala que el emisor no seguira
	// emitiendo particulas y puede
	// liberarse
	void Kill();
	
	friend class ParticleSystem;
	friend class ParticleSystemManager;
};

#endif

