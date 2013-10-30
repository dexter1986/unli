#ifndef AFFECTORS_H
#define AFFECTORS_H

#include "Affector.h"
#include "ParticleSystem.h"

class Gravity:public Affector{
private:
	float gx, gy;
public:
	Gravity(float gx, float gy);
	virtual void Apply(ParticleSystem &ps, float dt);
};


class Fade:public Affector{
private:
	float time;
public:
	Fade(float time);
	virtual void Apply(ParticleSystem &ps, float dt);
};


class ScreenCollision:public Affector{
private:
	float left, top, right, bottom;
public:
	ScreenCollision(float left, float top, float right, float bottom);
	virtual void Apply(ParticleSystem &ps, float dt);
};



class SeekerGonzalo:public Affector{
private:
	float gravity, dampingRebote, velAttract;
	float left, top, right, bottom;
	unsigned seek_x, seek_y;
public:
	SeekerGonzalo(const sf::View &v, float gravity, float dampingRebote=0.7, float velAttract=5);
	void Seek(unsigned x, unsigned y);
	virtual void Apply(ParticleSystem &ps, float dt);
};



#endif
