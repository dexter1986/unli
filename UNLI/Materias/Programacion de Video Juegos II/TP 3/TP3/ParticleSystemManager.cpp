#include "glew.h"
#include "ParticleSystemManager.h"
#include <iostream>
using namespace std;

ParticleSystemManager *ParticleSystemManager::globalManager=NULL;

// devuelve el manager global de particulas
ParticleSystemManager &ParticleSystemManager::GetManager(){
	if(!globalManager)
		globalManager=new ParticleSystemManager();
	return *globalManager;
}

// constructor, no hace nada
ParticleSystemManager::ParticleSystemManager() {
	usePointSprites = false;
	pointSpritesSuported = false;

	// averiguamos si podemos usar pointSprites
	if(glewIsSupported("GL_ARB_point_sprite")) 
		pointSpritesSuported=true;
	else{
		cerr<<"ERROR: la extension GL_ARB_point_sprite no esta disponible"<<endl;
	}
}


ParticleSystemManager::~ParticleSystemManager() {
	list<ParticleSystem *>::iterator ps=particlesystems.begin();
	while(ps!=particlesystems.end()){
		delete *ps;
	}
	//delete globalManager;
}


// crea un emisor y un nuevo sistema de particulas
// y nos devuelve una referencia a al emisor
Emitter &ParticleSystemManager::AddParticleSystem(unsigned nMaxParticles){
	Emitter *e=new Emitter;
	particlesystems.insert(	particlesystems.end(),
							new ParticleSystem(*e, nMaxParticles));
	return *e;
}


// mueve las particulas de todos los sistemas
void ParticleSystemManager::Simulate(float dt){
	list<ParticleSystem *>::iterator ps=particlesystems.begin();

	ParticleSystem *ptemp;
	// mueve todos los sistemas
	while(ps!=particlesystems.end()){
		(*(ps))->Move(dt);
		if((*(ps))->nParticles==0 && (*(ps))->emitter->kill){
			ptemp = (*(ps));
			ps=particlesystems.erase(ps);	
			delete ptemp->emitter;
			delete ptemp;
		}
		else
		{
			ps++;
		}
	}
}


// dibuja las particulas de todos los sistemas
void ParticleSystemManager::Render(sf::RenderWindow &w){
	if(usePointSprites) 
	{
		Render_PointSprites(w);
	}
	else
	{
		list<ParticleSystem *>::iterator ps=particlesystems.begin();
		while(ps!=particlesystems.end()){
			ParticleSystem::Particle *p=(*ps)->particles;
			for(unsigned i=0; i<(*ps)->nMaxParticles; i++, p++){
				if(p->life>=0){
					w.Draw(*p);
				}
			}
			ps++;
		}
	}
}

void ParticleSystemManager::Render_PointSprites(sf::RenderWindow &w){
	list<ParticleSystem *>::iterator ps=particlesystems.begin();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_POINT_SPRITE);
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	
	while(ps!=particlesystems.end()){
		ParticleSystem::Particle *p=(*ps)->particles;
		glPointSize(p->GetSize().x);
		(*ps)->emitter->GetImage()->Bind();
		
		glBegin(GL_POINTS);

		sf::Vector2f particlePosition;
		for(unsigned i=0; i<(*ps)->nMaxParticles; i++, p++){
			if(p->life>=0){
				glColor4f(1,1,1,p->GetColor().a/255.0);
				particlePosition=p->GetPosition();
				glVertex2f(particlePosition.x, particlePosition.y);
			}
		}
		ps++;
		glEnd();
	}
	glDisable(GL_POINT_SPRITE);
}

unsigned ParticleSystemManager::GetNumParticles(){
	unsigned numParticles=0;
	list<ParticleSystem *>::iterator ps=particlesystems.begin();
	while(ps!=particlesystems.end()){
		numParticles+=(*ps)->GetNumParticles();
		ps++;
	}
	return numParticles;
}
