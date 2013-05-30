#pragma once
#include "SFMLRenderer.h"
#include "Box2DHelper.h"

class PhysicManager: Box2DHelper
{
private:
	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	bool isEnableDebugPhysics;
	SFMLRenderer *debugRender;
	RenderWindow *wnd;
	b2World *phyWorld;
	PhysicManager(void);
	static PhysicManager* singleton;
	std::map<std::string,b2Body*> objects_;
public:
	static PhysicManager* Instance();
	void InitPhysics(float timeStep,int32 velocityIterations,int32 positionIterations);	
	void EnableDebugPhysics(bool isEnable,RenderWindow *wnd);
	void UpdatePhysics();	
	void Draw();	
	~PhysicManager(void);
};

