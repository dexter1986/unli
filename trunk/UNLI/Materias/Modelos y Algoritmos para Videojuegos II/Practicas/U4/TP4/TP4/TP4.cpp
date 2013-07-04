#include "TP4.h"

TP4::TP4(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{
	EnableDebugPhysics(true);
	isGamePause = false;

	text.setFont(ImageManager::Instance()->GetFont());	
	text.setCharacterSize(22);		
	text.setPosition(80.0f,70.0f);	
	text.scale(0.25f,0.25f);
	
}

TP4::~TP4(void)
{		
	delete _cronometro;
}

void TP4::Init()
{
	_cronometro = new Cronometro(60);
	_cronometro->Init();

	InitSFML();
}

void TP4::DrawGame()
{
	Draw(_cronometro->DrawObject());
	Draw(text);
	Draw(box);
}

void TP4::UpdatePoolEvents(Event evt)
{	
	switch(evt.type)
	{
		case Event::MouseButtonPressed:
		{	
			Vector2f pos = mapPixelToCoords(Vector2i(evt.mouseButton.x,evt.mouseButton.y));
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
	/*isGamePause =  true;
	if(isGamePause)
	{
		text.setString("El Jugador Pierde");
		PhysicManager::Instance()->isPause = true;
	}*/
}

void TP4::UpdatePhysics()
{
	b2Vec2 pos = controlBody->GetPosition();
	box.setPosition(pos.x,pos.y);

	//Seteamos la orientación
	float m_angAux = controlBody->GetAngle();//entrega el angulo en radianes	
	box.setRotation(m_angAux*180/3.14f);//recibe el angulo en grados

}

void TP4::UpdateState()
{
	if(!isGamePause)
	{
		ActualizarContador();
	}
}

void TP4::InitPhysics()
{		
	groundWallBody[0] = PhysicManager::Instance()->CreateRectangularStaticBody(150.0f,5.0f,1.0f,0.2f,0.2f);
	groundWallBody[0]->SetTransform(b2Vec2(100.0f,140.0f),0.0f);
	
	groundWallBody[1] = PhysicManager::Instance()->CreateRectangularStaticBody(150.0f,5.0f,1.0f,0.2f,0.2f);
	groundWallBody[1]->SetTransform(b2Vec2(100.0f,10.0f),0.0f);

	groundWallBody[2] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,135.0f,1.0f,0.2f,0.2f);
	groundWallBody[2]->SetTransform(b2Vec2(22.0f,75.0f),0.0f);

	groundWallBody[3] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,135.0f,1.0f,0.2f,0.1f);
	groundWallBody[3]->SetTransform(b2Vec2(178.0f,75.0f),0.0f);

	controlBody = PhysicManager::Instance()->CreateRectangularDynamicBody(8.0f,16.0f,0.12f,0.1f,0.2f);			
	controlBody->SetTransform(b2Vec2(35.0f,30.0f),0.0f);
	
	b2MassData d; 
	d.mass = 1.0f; 
	d.I = 30.0f; 
	d.center.x = 0.0f;
	d.center.y = 0.0f;
	
	controlBody->SetMassData(&d);

}

void TP4::InitSFML()
{
	box.setSize(Vector2f(8.0f,16.0f));
	box.setFillColor(Color::Red);
	box.setOrigin(4.0f,8.0f);
	box.setPosition(100.0f,50.0f);

	//controlBody->SetUserData(&box);
}

void TP4::ActualizarContador()
{
	_cronometro->Update();
	isGamePause = ((Cronometro*)_cronometro)->isEndTime();
	if(isGamePause)
	{
		text.setString("El Jugador Gana");
		PhysicManager::Instance()->isPause = true;
	}
}