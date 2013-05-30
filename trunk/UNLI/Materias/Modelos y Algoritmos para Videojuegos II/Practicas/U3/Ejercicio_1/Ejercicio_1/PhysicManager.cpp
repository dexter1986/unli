#include "PhysicManager.h"

PhysicManager* PhysicManager::singleton=NULL;

PhysicManager* PhysicManager::Instance()
{
	if(singleton == NULL)
		singleton =  new PhysicManager();
	return singleton;
}

PhysicManager::PhysicManager(void):objects_()
{
	debugRender = NULL;
	phyWorld = new b2World(b2Vec2(0.0f,9.8f) ,true);
}

PhysicManager::~PhysicManager(void)
{
	for( std::map<std::string, b2Body*>::const_iterator it = objects_.begin();
		 it != objects_.end(); ++it) 
	{	
	   	if(it->second != NULL ) {
			phyWorld->DestroyBody(it->second);            
		}
	}

	objects_.clear();

	if(debugRender != NULL)
		delete debugRender;

	if(phyWorld != NULL)
		delete phyWorld;
}

void PhysicManager::InitPhysics(float timeStep,int32 velocityIterations,int32 positionIterations)
{	
	this->timeStep = timeStep;
	this->velocityIterations = velocityIterations;
	this->positionIterations = positionIterations;
}

void PhysicManager::UpdatePhysics()
{
	phyWorld->Step(timeStep,velocityIterations,positionIterations);
	phyWorld->ClearForces();
}

void PhysicManager::Draw()
{
	if(isEnableDebugPhysics)
	{
		phyWorld->DrawDebugData();
	}
}

void PhysicManager::EnableDebugPhysics(bool isEnable,RenderWindow *wnd)
{
	this->wnd = wnd;
	if(debugRender == NULL)
	{		
		debugRender = new SFMLRenderer(wnd);	
		debugRender->SetFlags(UINT_MAX);
	}

	if(isEnable)
	{
		phyWorld->SetDebugDraw(debugRender);
	}
	else
	{
		phyWorld->SetDebugDraw(NULL);
	}

	isEnableDebugPhysics = isEnable;
}



