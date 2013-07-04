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
	bool isPause;
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

	b2DistanceJoint* PhysicManager::CreateDistanceJoint(b2Body* first, b2Vec2 anchorFirst,b2Body* second,b2Vec2 anchorSecond, float distance,float freq, float damp  );
	b2RevoluteJoint* PhysicManager::CreateRevoluteJoint(b2Body* base, b2Vec2 anchorBase,b2Body* second, float angMin,float angMax, float motorSpeed, float maxTorque, bool enableMotor,bool enableLimits );
	b2PrismaticJoint* PhysicManager::CreatePrismaticJoint(b2Body* base, b2Vec2 anchorBase,b2Body* second, b2Vec2 axis ,float distMin,float distMax, float motorSpeed, float maxForce, bool enableMotor,bool enableLimits );
	b2PulleyJoint* PhysicManager::CreatePulleyJoint(b2Body* first, b2Vec2 anchorFirst, b2Vec2 worldAnchor1, b2Body* second,b2Vec2 anchorSecond, b2Vec2 worldAnchor2, float ratio );
	b2GearJoint* PhysicManager::CreateGearJoint(b2Body* first, b2Body* second, b2Joint* Joint1, b2Joint* Joint2, float ratio );
	b2MouseJoint* CreateMouseJoint(b2Body* second, float maxForce);

	void QueryAABB(b2QueryCallback* callback, const b2AABB& aabb) const;

	void QueryAABB(b2QueryCallback* callback,float x1,float y1,float x2, float y2);

	b2AABB& Createb2AABB(float x1,float y1,float x2, float y2);
	static PhysicManager* Instance();
	void InitPhysics(float timeStep,int32 velocityIterations,int32 positionIterations);	
	void EnableDebugPhysics(bool isEnable,RenderWindow *wnd);
	void UpdatePhysics();	
	void Draw();	
	~PhysicManager(void);
};

