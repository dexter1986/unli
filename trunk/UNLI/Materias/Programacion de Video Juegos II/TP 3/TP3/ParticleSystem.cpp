#include "ParticleSystem.h"

// construye el sistema de particulas asociandole un emisor
// y con la cantidad maxima de particulas dada
ParticleSystem::ParticleSystem(Emitter &e, unsigned nMaxParticles){
	this->emitter=&e;
	nParticles=0;
	cycle = false;
	// inicializa las particulas
	this->nMaxParticles=nMaxParticles;
	particles=new Particle[nMaxParticles];
	for(unsigned i=0; i<nMaxParticles; i++){
		// inicializa la vida de las particulas en -1 para que sean
		// reiniciadas al mover
		particles[i].life=-1;
	}
}

// destructor: elimina la memoria de las particulas
ParticleSystem::~ParticleSystem() {
	if(particles == NULL)
	{
		delete []particles;
		particles = NULL;
	}
}


// devuelve un numero aleatorio con distribucion uniforme entre
// [media-desv, media+desv]
#define RAND_MEDIA_DESV(media, desv) media-desv+(rand()/float(RAND_MAX))*2*desv

void ParticleSystem::Move(float &dt){
	// la cantidad de particulas que podemos lanzar
	float static particlesToSpawn=0;
	
	// aplica a las particulas los efectos asociados al emisor
	vector<Affector *>::iterator e=emitter->affectors.begin();
	while(e!=emitter->affectors.end()){
		(*e)->Apply(*this, dt);
		e++;
	}
	
	// actualizamos la cantidad de particulas que podemos crear
	// en base al tiempo transcurrido y al spawnRate del emisor
	if(emitter->spawn && !cycle)
	{
		if(emitter->isOneTime)
		{
			cycle = true;
			particlesToSpawn = nMaxParticles;
		}
		else
		{
			particlesToSpawn+=emitter->spawnRate*dt;
		}
	}

	if(emitter->isOneTime && !emitter->spawn)
	{
		cycle = false;
	}
	
	// movemos las particulas
	for(unsigned i=0; i<nMaxParticles; i++){
		Particle &p=particles[i];
		
		// si esta muerta
		if(p.life<=0){
			// si podemos, creamos otra particula que tome su lugar
			if(emitter->spawn && particlesToSpawn>0){
				float vel, angle;
				// inicializa propiedades de la particula segun el emisor
				p.SetImage(*emitter->GetImage());
				p.SetBlendMode(emitter->GetBlendMode());
				p.SetColor(emitter->GetColor());
				p.SetPosition(emitter->GetPosition().x, emitter->GetPosition().y);
				p.SetCenter(emitter->GetImage()->GetWidth()/2,emitter->GetImage()->GetHeight()/2);
				
				// inicializa los parametros aleatorios de la particula
				// divide la velocidad en sus componentes segun el angulo
				p.life=RAND_MEDIA_DESV(emitter->emitLife, emitter->deltaLife);
				vel=RAND_MEDIA_DESV(emitter->emitVel, emitter->deltaVel);
				angle=RAND_MEDIA_DESV(emitter->emitAngle, emitter->deltaAngle);
				p.vx=vel*cos(angle);
				p.vy=vel*sin(angle);
				
				// aumentamos el nro de particulas del sistema y restamos
				// la aprticula creada al radio de particulas que podemos crear
				nParticles++;
				particlesToSpawn-=1;
			}
		}
		else{
			// decrementamos el tiempo de vida de la particula
			p.life-=dt;
//			p.SetBlendMode(sf::Blend::Add);
			if(p.life<0) nParticles--;
			// mueve la particula (con la funcion Move() de sprite)
			else p.Move(p.vx*dt, p.vy*dt);
		}
	}
}



