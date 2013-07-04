#include "TP4.h"

TP4::TP4(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{
	EnableDebugPhysics(true);
}

TP4::~TP4(void)
{	
}

void TP4::Init()
{
}

void TP4::DrawGame()
{
}

void TP4::UpdatePoolEvents(Event evt)
{	
	switch(evt.type)
	{
		case Event::MouseButtonPressed:
		{
			//obtenemos las coordenadas del mouse transformadas por la vista
			Vector2f pos=wnd->ConvertCoords(evt.mouseButton.x,evt.mouseButton.y);
			map
			//Definimos un rectangulo que vamos a utilizar 
			//para preguntar que objetos lo intersectan
			_query.mousePos.x = pos.x;
			_query.mousePos.y = pos.y;

			PhysicManager::Instance()->QueryAABB(&_query,pos.x-5,pos.y-5,pos.x+5,pos.y+5);
		}
		break;
	}
}

void TP4::UpdateEvents()
{
}

void TP4::CheckCollitions()
{	
}

void TP4::UpdatePhysics()
{

}

void TP4::InitPhysics()
{		
	groundWallBody[0] = PhysicManager::Instance()->CreateRectangularStaticBody(150.0f,5.0f,1.0f,0.2f,0.1f);
	groundWallBody[0]->SetTransform(b2Vec2(100.0f,140.0f),0.0f);
	
	groundWallBody[1] = PhysicManager::Instance()->CreateRectangularStaticBody(150.0f,5.0f,1.0f,0.2f,0.1f);
	groundWallBody[1]->SetTransform(b2Vec2(100.0f,10.0f),0.0f);

	groundWallBody[2] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,135.0f,1.0f,0.2f,0.1f);
	groundWallBody[2]->SetTransform(b2Vec2(22.0f,75.0f),0.0f);

	groundWallBody[3] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,135.0f,1.0f,0.2f,0.1f);
	groundWallBody[3]->SetTransform(b2Vec2(178.0f,75.0f),0.0f);

	groundWallBody[4] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,20.0f,1.0f,0.2f,0.1f);
	groundWallBody[4]->SetTransform(b2Vec2(50.0f,127.0f),0.0f);	

	groundWallBody[5] = PhysicManager::Instance()->CreateRectangularStaticBody(50.0f,5.0f,1.0f,0.2f,0.1f);
	groundWallBody[5]->SetTransform(b2Vec2(50.0f,100.0f),0.0f);

	groundWallBody[6] = PhysicManager::Instance()->CreateRectangularStaticBody(65.0f,5.0f,1.0f,0.2f,0.1f);
	groundWallBody[6]->SetTransform(b2Vec2(125.0f,100.0f),0.0f);

	groundWallBody[7] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,20.0f,1.0f,0.2f,0.1f);
	groundWallBody[7]->SetTransform(b2Vec2(150.0f,127.0f),0.0f);	

	groundWallBody[7] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,20.0f,1.0f,0.2f,0.1f);
	groundWallBody[7]->SetTransform(b2Vec2(120.0f,113.0f),0.0f);	

	groundWallBody[8] = PhysicManager::Instance()->CreateRectangularStaticBody(120.0f,5.0f,1.0f,0.2f,0.1f);
	groundWallBody[8]->SetTransform(b2Vec2(100.0f,80.0f),0.0f);

	groundWallBody[9] = PhysicManager::Instance()->CreateRectangularStaticBody(50.0f,5.0f,1.0f,0.2f,0.1f);
	groundWallBody[9]->SetTransform(b2Vec2(50.0f,60.0f),0.0f);
	
	groundWallBody[10] = PhysicManager::Instance()->CreateRectangularStaticBody(115.0f,5.0f,1.0f,0.2f,0.1f);
	groundWallBody[10]->SetTransform(b2Vec2(100.0f,35.0f),0.0f);

	groundWallBody[11] = PhysicManager::Instance()->CreateRectangularStaticBody(50.0f,5.0f,1.0f,0.2f,0.1f);
	groundWallBody[11]->SetTransform(b2Vec2(150.0f,60.0f),0.0f);

	groundWallBody[12] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,20.0f,1.0f,0.2f,0.1f);
	groundWallBody[12]->SetTransform(b2Vec2(100.0f,67.0f),0.0f);	

	TargetBody = PhysicManager::Instance()->CreateRectangularKinematicBody(7.0f,7.0f);
	TargetBody->SetTransform(b2Vec2(100.0f,23.0f),0.0f);

	controlBody = PhysicManager::Instance()->CreateCircularDynamicBody(3.0f,1.0f,0.2f,0.1f);		
	controlBody->SetTransform(b2Vec2(35.0f,130.0f),0.0f);		
}

void TP4::InitSFML()
{
}