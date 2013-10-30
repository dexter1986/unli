#ifndef AFFECTOR_H
#define AFFECTOR_H



class ParticleSystem;

class Affector {
private:
public:
	virtual void Apply(ParticleSystem &ps, float dt)=0;
};

#endif

