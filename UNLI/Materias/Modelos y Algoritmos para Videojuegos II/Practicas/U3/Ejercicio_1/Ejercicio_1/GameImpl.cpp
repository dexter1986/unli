#include "GameImpl.h"
#include "Box2DHelper.h"


GameImpl::GameImpl(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{
}

GameImpl::~GameImpl(void)
{
	phyWorld->DestroyBody(controlBody);	
	phyWorld->DestroyBody(leftWallBody);
	phyWorld->DestroyBody(groundBody);
	phyWorld->DestroyBody(rightWallBody);
}

void GameImpl::DrawGame()
{

}

void GameImpl::UpdatePoolEvents(Event evt)
{
	switch(evt.type){		
			case Event::MouseButtonPressed:
				b2Body *body=Box2DHelper::CreateTriangularDynamicBody(phyWorld,b2Vec2(0.0f,0.0f),10.0f,1.0f,4.0f,0.1f);				
				//transformamos las coordenadas segun la vista activa
				Vector2f pos=wnd->mapPixelToCoords(sf::Vector2i(evt.mouseButton.x,evt.mouseButton.y));
				body->SetTransform(b2Vec2(pos.x,pos.y),0.0f);
				break;
		}
}

void GameImpl::UpdateEvents()
{	
	//movemos el cuerpo	
	controlBody->SetAwake(true);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		controlBody->SetLinearVelocity(b2Vec2 (-50.0f, 0.0f));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		controlBody->SetLinearVelocity(b2Vec2 (50.0f, 0.0f));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		controlBody->SetLinearVelocity(b2Vec2 (0.0f, 50.0f));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		controlBody->SetLinearVelocity(b2Vec2 (0.0f, -50.0f));
}

void GameImpl::CheckCollitions()
{

}

void GameImpl::Init_Physics()
{
	//creamos un piso y paredes
	groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,100,10);
	groundBody->SetTransform(b2Vec2(50.0f,100.0f),0.0f);

	leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,10,100);
	leftWallBody->SetTransform(b2Vec2(0.0f,50.0f),0.0f);

	rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,10,100);
	rightWallBody->SetTransform(b2Vec2(100.0f,50.0f),0.0f);
	
	//Creamos un círculo que controlaremos con el teclado
	controlBody = Box2DHelper::CreateCircularDynamicBody(phyWorld,5,1.0f,0.5,0.1f);		
	controlBody->SetTransform(b2Vec2(50.0f,50.0f),0.0f);
}