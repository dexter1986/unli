#pragma once
#include "SFMLRenderer.h"

class PhysicManager
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
	b2Body* CreateDynamicBody();
	b2Body* CreateStaticBody();
	b2Body* CreateKinematicBody();
	b2FixtureDef CreateRectangularFixtureDef(float sizeX, float sizeY, float density, float friction,float restitution);
	b2FixtureDef CreateCircularFixtureDef(float radius, float density, float friction,float restitution);
	b2FixtureDef CreatePolyFixtureDef(b2Vec2* v,int n, float density, float friction,float restitution);
	b2FixtureDef CreateTriangularFixtureDef(b2Vec2 c,float h, float density, float friction,float restitution);
	b2Body* CreateRectangularDynamicBody(float sizeX, float sizeY, float density, float friction, float restitution);
	b2Body* CreateRectangularKinematicBody(float sizeX, float sizeY);
	b2Body* CreateRectangularStaticBody(float sizeX, float sizeY,float density, float friction, float restitution);
	b2Body* CreateCircularDynamicBody(float radius, float density, float friction, float restitution);
	b2Body* CreateCircularKinematicBody(float radius);
	b2Body* CreateCircularStaticBody(float radius);
	b2Body* CreateTriangularDynamicBody(b2Vec2 center, float h,float density, float friction, float restitution);
	b2Body* CreateTriangularKinematicBody(b2Vec2 center, float h);
	b2Body* CreateTriangularStaticBody(b2Vec2 center, float h);
	b2Body* CreatePolyDynamicBody(b2Vec2 *v, int n,float density, float friction, float restitution);
	b2Body* CreatePolyKinematicBody(b2Vec2 *v, int n);
	b2Body* CreatePolyStaticBody(b2Vec2 *v, int n);
	static PhysicManager* Instance();
	void InitPhysics(float timeStep,int32 velocityIterations,int32 positionIterations);	
	void EnableDebugPhysics(bool isEnable,RenderWindow *wnd);
	void UpdatePhysics();	
	void Draw();	
	~PhysicManager(void);
};

