#include "U3_EJ3.h"

U3_EJ3::U3_EJ3(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{
	EnableDebugPhysics(true);
}

U3_EJ3::~U3_EJ3(void)
{
	phyWorld->DestroyBody(controlBody);	
	phyWorld->DestroyBody(groundBody);
	phyWorld->DestroyBody(obstaculoBody);	
	phyWorld->DestroyBody(groundRightBody);
	phyWorld->DestroyBody(groundLeftBody);
	phyWorld->DestroyBody(groundTopBody);
}


void U3_EJ3::DrawGame()
{
	/*Draw(box);*/
	//Draw(pelota);
	//Draw(ground);
}

void U3_EJ3::UpdatePoolEvents(Event evt)
{	
}

void U3_EJ3::UpdateEvents()
{		
	if(Keyboard::isKeyPressed(Keyboard::Left))
		obstaculoBody->SetLinearVelocity(b2Vec2(-30.0f,0));
	if(Keyboard::isKeyPressed(Keyboard::Right))
		obstaculoBody->SetLinearVelocity(b2Vec2(30.0f,0));
}

void U3_EJ3::CheckCollitions()
{
}

void U3_EJ3::UpdatePhysics()
{		
	/*b2Vec2 pos = controlBody->GetPosition();
	box.setPosition(pos.x,pos.y);*/
}

void U3_EJ3::InitPhysics()
{
	//creamos un piso
	groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,150.0f,5.0f,10.0f,0.5f,0.0f);
	groundBody->SetTransform(b2Vec2(100.0f,140.0f),0.0f);

	groundTopBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,150.0f,5.0f,10.0f,0.5f,0.0f);
	groundTopBody->SetTransform(b2Vec2(100.0f,10.0f),0.0f);

	groundLeftBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,5.0f,135.0f,10.0f,0.5f,0.0f);
	groundLeftBody->SetTransform(b2Vec2(22.0f,75.0f),0.0f);

	groundRightBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,5.0f,135.0f,10.0f,0.5f,0.0f);
	groundRightBody->SetTransform(b2Vec2(178.0f,75.0f),0.0f);
	

	//Creamos un círculo que controlaremos con el teclado
	/*controlBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld,10.0f,10.0f,1.0f,0.5,0.8f);		
	controlBody->SetTransform(b2Vec2(100.0f,50.0f),0.0f);*/

	controlBody = Box2DHelper::CreateCircularDynamicBody(phyWorld,5.0f,1.0f,0.5,2.0f);		
	controlBody->SetTransform(b2Vec2(100.0f,50.0f),0.0f);		

	obstaculoBody = Box2DHelper::CreateRectangularKinematicBody(phyWorld,10.0f,10.0f);		
	obstaculoBody->SetTransform(b2Vec2(100.0f,100.0f),0.0f);		
	
	//controlBody->SetAwake(false);
}

void U3_EJ3::InitSFML()
{
	ground.setSize(Vector2f(150.0f,5.0f));
	ground.setFillColor(Color::Green);
	ground.setOrigin(75.0f,2.5f);
	ground.setPosition(100.0f,140.0f);

	box.setSize(Vector2f(10.0f,10.0f));
	box.setFillColor(Color::Red);
	box.setOrigin(5.0f,5.0f);
	box.setPosition(100.0f,50.0f);

	pelota.setRadius(5.0f);
	pelota.setOrigin(5.0f,5.0f);
	pelota.setFillColor(Color::Red);
	pelota.setPosition(100.0f,50.0f);
}