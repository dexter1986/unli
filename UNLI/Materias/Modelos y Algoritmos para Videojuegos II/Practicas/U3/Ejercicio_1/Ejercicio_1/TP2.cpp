#include "TP2.h"

TP2::TP2(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{
	EnableDebugPhysics(true);
}

TP2::~TP2(void)
{	
}

void TP2::Init()
{

}

void TP2::DrawGame()
{
	/*Draw(box);*/
	//Draw(pelota);
	//Draw(ground);
}

void TP2::UpdatePoolEvents(Event evt)
{	
}

void TP2::UpdateEvents()
{		
	if(Keyboard::isKeyPressed(Keyboard::Up))
		controlBody->SetLinearVelocity(b2Vec2(1000000000.0f,-1000.0f));//,controlBody->GetWorldCenter());
	if(Keyboard::isKeyPressed(Keyboard::Down))
		controlBody->ApplyLinearImpulse(b2Vec2(100000.0f,-10000.0f),controlBody->GetWorldCenter());
}

void TP2::CheckCollitions()
{

}

void TP2::UpdatePhysics()
{		
	/*b2Vec2 pos = controlBody->GetPosition();
	box.setPosition(pos.x,pos.y);*/
}

void TP2::InitPhysics()
{
	//creamos un piso
	groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,150.0f,5.0f,10.0f,0.5f,0.3f);
	groundBody->SetTransform(b2Vec2(100.0f,140.0f),0.0f);
	
	groundTopBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,150.0f,5.0f,10.0f,0.5f,0.3f);
	groundTopBody->SetTransform(b2Vec2(100.0f,10.0f),0.0f);

	groundLeftBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,5.0f,135.0f,10.0f,0.5f,0.3f);
	groundLeftBody->SetTransform(b2Vec2(22.0f,75.0f),0.0f);

	groundRightBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,5.0f,135.0f,10.0f,0.5f,0.3f);
	groundRightBody->SetTransform(b2Vec2(178.0f,75.0f),0.0f);

	baseBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,5.0f,10.0f,10.0f,0.5f,0.3f);
	baseBody->SetTransform(b2Vec2(45.0f,132.0f),0.0f);	

	controlBody = Box2DHelper::CreateCircularDynamicBody(phyWorld,5.0f,100000.0f,0.5f,0.1f);		
	controlBody->SetTransform(b2Vec2(45.0f,120.0f),0.0f);		

	obstaculoBody[0] = Box2DHelper::CreateRectangularDynamicBody(phyWorld,10.0f,10.0f,100.0f,0.5f,0.1f);		
	obstaculoBody[0]->SetTransform(b2Vec2(140.0f,110.0f),0.0f);

	obstaculoBody[1] = Box2DHelper::CreateRectangularDynamicBody(phyWorld,10.0f,10.0f,100.0f,0.5f,0.1f);		
	obstaculoBody[1]->SetTransform(b2Vec2(135.0f,120.0f),0.0f);

	obstaculoBody[2] = Box2DHelper::CreateRectangularDynamicBody(phyWorld,10.0f,10.0f,100.0f,0.5f,0.1f);		
	obstaculoBody[2]->SetTransform(b2Vec2(145.0f,120.0f),0.0f);
	
	obstaculoBody[3] = Box2DHelper::CreateRectangularDynamicBody(phyWorld,10.0f,10.0f,100.0f,0.5f,0.1f);		
	obstaculoBody[3]->SetTransform(b2Vec2(130.0f,130.0f),0.0f);
	
	obstaculoBody[4] = Box2DHelper::CreateRectangularDynamicBody(phyWorld,10.0f,10.0f,100.0f,0.5f,0.1f);		
	obstaculoBody[4]->SetTransform(b2Vec2(140.0f,130.0f),0.0f);
	
	obstaculoBody[5] = Box2DHelper::CreateRectangularDynamicBody(phyWorld,10.0f,10.0f,100.0f,0.5f,0.1f);		
	obstaculoBody[5]->SetTransform(b2Vec2(150.0f,130.0f),0.0f);
}

void TP2::InitSFML()
{
	/*ground.setSize(Vector2f(150.0f,5.0f));
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
	pelota.setPosition(100.0f,50.0f);*/
}