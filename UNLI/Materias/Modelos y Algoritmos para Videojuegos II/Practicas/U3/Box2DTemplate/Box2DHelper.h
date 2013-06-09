#include <Box2D/Box2D.h>
#pragma once

class Box2DHelper{

public:

	
	//-------------------------------------------------------------
	//Crea un body dinámico sin fixtures centrado en 0,0
	//-------------------------------------------------------------

	static b2Body* CreateDynamicBody(b2World *phyWorld){
		
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
	static b2Body* CreateStaticBody(b2World *phyWorld){
		
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
	static b2Body* CreateKinematicBody(b2World *phyWorld){
		
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
	static b2FixtureDef CreateRectangularFixtureDef(float sizeX, float sizeY, float density, float friction,float restitution){
		
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
	static b2FixtureDef CreateCircularFixtureDef(float radius, float density, float friction,float restitution){
	
		b2CircleShape *circle= new b2CircleShape();
		circle->m_p=b2Vec2(0.0f,0.0f);
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
	static b2FixtureDef CreatePolyFixtureDef(b2Vec2* v,int n, float density, float friction,float restitution){
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
	static b2FixtureDef CreateTriangularFixtureDef(b2Vec2 c,float h, float density, float friction,float restitution){
	
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
	static b2Body* CreateRectangularDynamicBody(b2World *phyWorld, float sizeX, float sizeY, float density, float friction, float restitution){
			
		b2Body* body= CreateDynamicBody(phyWorld);
		b2FixtureDef box=CreateRectangularFixtureDef(sizeX,sizeY,density,friction,restitution);
		body->CreateFixture(&box);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body cinemático con un fixture rectangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateRectangularKinematicBody(b2World *phyWorld, float sizeX, float sizeY){
			
		b2Body* body= CreateKinematicBody(phyWorld);
		b2FixtureDef box=CreateRectangularFixtureDef(sizeX,sizeY,0.0f,0.0f,0.0f);
		body->CreateFixture(&box);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body estático con un fixture rectangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateRectangularStaticBody(b2World *phyWorld, float sizeX, float sizeY){
			
		b2Body* body= CreateStaticBody(phyWorld);
		b2FixtureDef box=CreateRectangularFixtureDef(sizeX,sizeY,0.0f,0.0f,0.0f);
		body->CreateFixture(&box);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body dinámico con un fixture circular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateCircularDynamicBody(b2World *phyWorld, float radius, float density, float friction, float restitution){
			
		b2Body* body= CreateDynamicBody(phyWorld);
		b2FixtureDef cir=CreateCircularFixtureDef(radius,density,friction,restitution);
		body->CreateFixture(&cir);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body cinemático con un fixture circular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateCircularKinematicBody(b2World *phyWorld, float radius){
			
		b2Body* body= CreateKinematicBody(phyWorld);
		b2FixtureDef cir=CreateCircularFixtureDef(radius,0.0f,0.0f,0.0f);
		body->CreateFixture(&cir);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body estático con un fixture circular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateCircularStaticBody(b2World *phyWorld, float radius){
			
		b2Body* body= CreateStaticBody(phyWorld);
		b2FixtureDef cir=CreateCircularFixtureDef(radius,0.0f,0.0f,0.0f);
		body->CreateFixture(&cir);
		return body;
	}
	
	//-------------------------------------------------------------
	//Crea un body dinámico con un fixture triangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateTriangularDynamicBody(b2World *phyWorld, b2Vec2 center, float h,float density, float friction, float restitution){
			
		b2Body* body= CreateDynamicBody(phyWorld);
		b2FixtureDef tri=CreateTriangularFixtureDef(center,h,density,friction,restitution);
		body->CreateFixture(&tri);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body cinemático con un fixture triangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateTriangularKinematicBody(b2World *phyWorld, b2Vec2 center, float h){
			
		b2Body* body= CreateKinematicBody(phyWorld);
		b2FixtureDef tri=CreateTriangularFixtureDef(center,h,0.0f,0.0f,0.0f);
		body->CreateFixture(&tri);
		return body;
	}

		//-------------------------------------------------------------
	//Crea un body estático con un fixture triangular centrado en el origen
	//-------------------------------------------------------------
	static b2Body* CreateTriangularStaticBody(b2World *phyWorld, b2Vec2 center, float h){
			
		b2Body* body= CreateStaticBody(phyWorld);
		b2FixtureDef tri=CreateTriangularFixtureDef(center,h,0.0f,0.0f,0.0f);
		body->CreateFixture(&tri);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body dinámico con un fixture poligonal 
	//-------------------------------------------------------------
	static b2Body* CreatePolyDynamicBody(b2World *phyWorld, b2Vec2 *v, int n,float density, float friction, float restitution){
			
		b2Body* body= CreateDynamicBody(phyWorld);
		b2FixtureDef tri=CreatePolyFixtureDef(v,n,density,friction,restitution);
		body->CreateFixture(&tri);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body cinemático con un fixture poligonal 
	//-------------------------------------------------------------
	static b2Body* CreatePolyKinematicBody(b2World *phyWorld, b2Vec2 *v, int n){
			
		b2Body* body= CreateKinematicBody(phyWorld);
		b2FixtureDef tri=CreatePolyFixtureDef(v,n,0.0f,0.0f,0.0f);
		body->CreateFixture(&tri);
		return body;
	}

	//-------------------------------------------------------------
	//Crea un body estático con un fixture poligonal
	//-------------------------------------------------------------
	static b2Body* CreatePolyStaticBody(b2World *phyWorld, b2Vec2 *v, int n){
			
		b2Body* body= CreateDynamicBody(phyWorld);
		b2FixtureDef tri=CreatePolyFixtureDef(v,n,0.0f,0.0f,0.0f);
		body->CreateFixture(&tri);
		return body;
	}


	

};