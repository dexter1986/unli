#include "PhysicManager.h"
#include "Constantes.h"

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
	phyWorld = new b2World(b2Vec2(0.0f,C::G()),true);
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


//-------------------------------------------------------------
//Crea un body dinámico sin fixtures centrado en 0,0
//-------------------------------------------------------------
	b2Body* PhysicManager::CreateDynamicBody(){
		
		//Declaramos el body
		b2Body * body;
		
		//Llenamos la definición		
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 0.0f);		
		body = phyWorld->CreateBody(&bodyDef);
		return body;
	}

//-------------------------------------------------------------
//Crea un body estático sin fixtures centrado en 0,0
//-------------------------------------------------------------
	b2Body* PhysicManager::CreateStaticBody(){		
		//Declaramos el body
		b2Body * body;		
		//Llenamos la definición		
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(0.0f, 0.0f);
		body = phyWorld->CreateBody(&bodyDef);
		return body;
	}

//-------------------------------------------------------------
//Crea un body cinemático sin fixtures centrado en 0,0
//-------------------------------------------------------------
	b2Body* PhysicManager::CreateKinematicBody(){
		//Declaramos el body
		b2Body * body;
		
		//Llenamos la definición		
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(0.0f, 0.0f);
		body = phyWorld->CreateBody(&bodyDef);
		return body;
	}

//-------------------------------------------------------------
//Crea un fixture rectangular con el 0,0 en el medio
//-------------------------------------------------------------
	b2FixtureDef PhysicManager::CreateRectangularFixtureDef(float sizeX, float sizeY, float density, float friction,float restitution){
		
		b2PolygonShape* box= new b2PolygonShape();
		
		box->SetAsBox(sizeX/2.0f, sizeY/2.0f,b2Vec2(0.0f,0.0f),0.0f);
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = box;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution=restitution;
	
		return fixtureDef;
	}

	//-------------------------------------------------------------
	//Crea un fixture circular con el 0,0 en el medio
	//-------------------------------------------------------------
	b2FixtureDef PhysicManager::CreateCircularFixtureDef(float radius, float density, float friction,float restitution){
		b2CircleShape *circle = new b2CircleShape();
		circle->m_p.Set(0.0f,0.0f);
		circle->m_radius=radius;

		b2FixtureDef fixtureDef;		
		fixtureDef.shape = circle;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution=restitution;
		return fixtureDef;
	}


	//-------------------------------------------------------------
	//Crea un fixture poligonal dado un conj de puntos
	//-------------------------------------------------------------
	b2FixtureDef PhysicManager::CreatePolyFixtureDef(b2Vec2* v,int n, float density, float friction,float restitution){
		b2PolygonShape *poly= new b2PolygonShape();
		poly->Set(v,n);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = poly;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution=restitution;
		return fixtureDef;
	}
	

	//-------------------------------------------------------------
	//Crea un fixture triangular (triángulo equilátero) 
	//-------------------------------------------------------------
	b2FixtureDef PhysicManager::CreateTriangularFixtureDef(b2Vec2 c,float h, float density, float friction,float restitution){
		b2Vec2 verts[3];
		verts[0].x=-h/2;
		verts[0].y=-h/2;
		verts[1].x=h/2;
		verts[1].y=-h/2;
		verts[2].x=0;
		verts[2].y=h/2;
		return CreatePolyFixtureDef(verts,3,density,friction,restitution);
	}
	

	//-------------------------------------------------------------
	//Crea un body dinámico con un fixture rectangular centrado en el origen
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreateRectangularDynamicBody(float sizeX, float sizeY, float density, float friction, float restitution){
			
		b2Body* body= CreateDynamicBody();
		b2FixtureDef box=CreateRectangularFixtureDef(sizeX,sizeY,density,friction,restitution);
		body->CreateFixture(&box);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body cinemático con un fixture rectangular centrado en el origen
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreateRectangularKinematicBody(float sizeX, float sizeY){
			
		b2Body* body= CreateKinematicBody();
		b2FixtureDef box=CreateRectangularFixtureDef(sizeX,sizeY,0.0f,0.0f,0.0f);
		body->CreateFixture(&box);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body estático con un fixture rectangular centrado en el origen
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreateRectangularStaticBody(float sizeX, float sizeY,float density, float friction, float restitution){
		
		b2Body* body= CreateStaticBody();
		b2FixtureDef box=CreateRectangularFixtureDef(sizeX,sizeY,density,friction,restitution);
		body->CreateFixture(&box);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body dinámico con un fixture circular centrado en el origen
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreateCircularDynamicBody(float radius, float density, float friction, float restitution){
			
		b2Body* body= CreateDynamicBody();
		b2FixtureDef cir=CreateCircularFixtureDef(radius,density,friction,restitution);
		
		body->CreateFixture(&cir);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body cinemático con un fixture circular centrado en el origen
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreateCircularKinematicBody(float radius){
			
		b2Body* body= CreateKinematicBody();
		b2FixtureDef cir=CreateCircularFixtureDef(radius,0.0f,0.0f,0.0f);
		body->CreateFixture(&cir);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body estático con un fixture circular centrado en el origen
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreateCircularStaticBody(float radius){
			
		b2Body* body= CreateStaticBody();
		b2FixtureDef cir=CreateCircularFixtureDef(radius,0.0f,0.0f,0.0f);
		body->CreateFixture(&cir);
		return body;
	}
	
	//-------------------------------------------------------------
	//Crea un body dinámico con un fixture triangular centrado en el origen
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreateTriangularDynamicBody(b2Vec2 center, float h,float density, float friction, float restitution){
			
		b2Body* body= CreateDynamicBody();
		b2FixtureDef tri=CreateTriangularFixtureDef(center,h,density,friction,restitution);
		body->CreateFixture(&tri);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body cinemático con un fixture triangular centrado en el origen
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreateTriangularKinematicBody(b2Vec2 center, float h){
			
		b2Body* body= CreateKinematicBody();
		b2FixtureDef tri=CreateTriangularFixtureDef(center,h,0.0f,0.0f,0.0f);
		body->CreateFixture(&tri);
		return body;
	}

		//-------------------------------------------------------------
	//Crea un body estático con un fixture triangular centrado en el origen
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreateTriangularStaticBody(b2Vec2 center, float h){
			
		b2Body* body= CreateStaticBody();
		b2FixtureDef tri=CreateTriangularFixtureDef(center,h,0.0f,0.0f,0.0f);
		body->CreateFixture(&tri);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body dinámico con un fixture poligonal 
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreatePolyDynamicBody(b2Vec2 *v, int n,float density, float friction, float restitution){
			
		b2Body* body= CreateDynamicBody();
		b2FixtureDef tri=CreatePolyFixtureDef(v,n,density,friction,restitution);
		body->CreateFixture(&tri);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body cinemático con un fixture poligonal 
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreatePolyKinematicBody(b2Vec2 *v, int n){
			
		b2Body* body= CreateKinematicBody();
		b2FixtureDef tri=CreatePolyFixtureDef(v,n,0.0f,0.0f,0.0f);
		body->CreateFixture(&tri);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body estático con un fixture poligonal
	//-------------------------------------------------------------
	b2Body* PhysicManager::CreatePolyStaticBody(b2Vec2 *v, int n){
			
		b2Body* body= CreateDynamicBody();
		b2FixtureDef tri=CreatePolyFixtureDef(v,n,0.0f,0.0f,0.0f);
		body->CreateFixture(&tri);
		return body;
	}


