#include "glew.h"
#include "ParticleSystemManager.h"
#include "TextureManager.h"
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
	Clear();
	ClearAffectors();
}

void ParticleSystemManager::Clear()
{	ParticleSystem *ptemp;
	list<ParticleSystem *>::iterator ps=particlesystems.begin();
	while(ps!=particlesystems.end()){
		ptemp = (*(ps));		
		ps=particlesystems.erase(ps);
		delete ptemp;				
	}
	
	particlesystems.clear();
	globalManager = NULL;	
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
	float t = GetTickCount();

	list<ParticleSystem *>::iterator ps=particlesystems.begin();

	ParticleSystem *ptemp;
	// mueve todos los sistemas
	while(ps!=particlesystems.end()){
		ptemp = (*(ps));
		ptemp->Move(dt);
		if(ptemp->nParticles==0 && ptemp->emitter->kill)
		{	
			ps=particlesystems.erase(ps);			
			delete ptemp->emitter;			
			delete ptemp;			
		}
		else
		{
			ps++;
		}
	}
	t = GetTickCount() - t;
	cout << " Time -> " << t << "\n";
}

// dibuja las particulas de todos los sistemas
void ParticleSystemManager::Render(sf::RenderWindow &w){
	if(usePointSprites) 
	{
		Render_PointSprites(w);
	}
	else
	{
		float t = GetTickCount();

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
		
		t = GetTickCount() - t;
		cout << " Time R-> " << t << "\n";
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
				glColor4f(1,1,1,p->GetColor().a/255.0f);
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

void ParticleSystemManager::AddAffector(Affector *a)
{
	affectors.push_back(a);
}

void ParticleSystemManager::ClearAffectors()
{
	for(int i=0;i<affectors.size();i++)
	{
		Affector *a = affectors[i];
		if(a)
		{
			delete a;
			a = NULL;
		}
	}
	affectors.clear();
}

void ParticleSystemManager::CreateEmiterOneShoot(float x, float y)
{
	Emitter &e = AddParticleSystem(3);
	e.Spawn(false);
	e.SetImage(TextureManager::GetInstance().GetTexture("../data/particula.png"));
	e.SetEmmitVel(200,200);
	e.SetEmmitLife(1,1);
	e.SetBlendMode(sf::Blend::Add);
	e.SetSpawnRate(100);

	for(int i=0;i< affectors.size();i++)
	{
		e.AddAffector(*affectors[i]);
	}
	
	e.isOneTime = true;	
	e.SetPosition(x,y);
	e.Spawn(true);		
	e.Kill();
}

void ParticleSystemManager::CreateEmiterOneExplosion(float x, float y,sf::Color color)
{
	Emitter &e = AddParticleSystem(10);
	e.Spawn(false);
	e.SetImage(TextureManager::GetInstance().GetTexture("../data/particula.png"));
	e.SetEmmitVel(200,50);
	e.SetEmmitLife(1,1);
	e.SetBlendMode(sf::Blend::Add);
	e.SetSpawnRate(100);
	e.SetColor(color);
	
	for(int i=0;i< affectors.size();i++)
	{
		e.AddAffector(*affectors[i]);
	}
	
	e.isOneTime = true;	
	e.SetPosition(x,y);
	e.Spawn(true);		
	e.Kill();
}