#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Emitter.h"

class ParticleSystem {
	public:
	// definicion de la clase particula
	struct Particle : public sf::Sprite
	{	
		float life;
		float vx, vy;
	};
	
	// numero maximo de particulas y
	// cantidad de particulas vivas
	unsigned nMaxParticles, nParticles;
	// puntero a las particulas
	Particle *particles;
	// el emisor del sistema
	Emitter *emitter;
	
	bool cycle;

	ParticleSystem(Emitter &e, unsigned nMaxParticles=10);
	~ParticleSystem();
	// mueve el sistema de particulas
	void Move(float &dt);
	// devuelve la cantidad de particulas vivas
	unsigned GetNumParticles(){return nParticles;};
};

#endif

