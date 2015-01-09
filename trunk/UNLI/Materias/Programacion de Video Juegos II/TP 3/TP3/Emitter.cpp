#include "Emitter.h"


// constructor
Emitter::Emitter(float emitVel, float emitAngle, float emitLife, float deltaVel, float deltaAngle, float deltaLife, float spawnRate,bool oneTime){
	this->emitVel=emitVel;
	this->emitAngle=emitAngle;
	this->emitLife=emitLife;
	this->deltaVel=deltaVel;
	this->deltaAngle=deltaAngle;
	this->deltaLife=deltaLife;
	spawn=true;
	kill=false;
	this->spawnRate=spawnRate;
	isOneTime = oneTime;
}


// agrega un efecto al sistema de particulas del emisor
void Emitter::AddAffector(Affector &e){
	affectors.push_back(&e);
}

// avisa al emisor si debe o no emitir particulas
void Emitter::Spawn(bool spawn=true){
	this->spawn=spawn;
}


// avisamos que ya no utilizaremos mas el emisor
void Emitter::Kill(){
	this->kill=true;
}


// funciones para modificar otros parametros del emisor
void Emitter::SetEmmitVel(float vel, float deltaVel){
	emitVel=vel;
	this->deltaVel=deltaVel;
}
void Emitter::SetEmmitAngle(float angle, float deltaAngle){
	emitAngle=angle;
	this->deltaAngle=deltaAngle;
}
void Emitter::SetEmmitLife(float life, float deltaLife){
	emitLife=life;
	this->deltaLife=deltaLife;
}
void Emitter::SetSpawnRate(float newSpawnRate){
	spawnRate=newSpawnRate;
}

Emitter::~Emitter()
{
	affectors.clear();	
}
