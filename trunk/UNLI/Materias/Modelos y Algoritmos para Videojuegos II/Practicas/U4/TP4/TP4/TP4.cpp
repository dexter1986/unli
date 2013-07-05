#include "TP4.h"

TP4::TP4(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{
	EnableDebugPhysics(false);
	
	text.setFont(ImageManager::Instance()->GetFont());	
	text.setCharacterSize(22);		
	text.setPosition(80.0f,70.0f);	
	text.scale(0.25f,0.25f);
	isEndGame = false;
}

TP4::~TP4(void)
{	
	delete fondo;
	for(std::list<Lata*>::const_iterator it = m_latas.begin();it != m_latas.end();++it)
	{
		delete *it;
	}
	m_latas.clear();

	delete _cronometro;	
}

void TP4::Init()
{
	_cronometro = new Cronometro(30);
	_cronometro->Init();

	int max = rand()%2+3;

	Lata* lata;

	for(int i=0;i<max;i++)
	{
		lata = new Lata(rand()%8+8.0f,rand()%8+16.0f,rand()%40+10.0f,rand()%50+50.0f+rand()%50,30.0f);
		m_latas.push_back(lata);
		lata->Init();
	}

	fondo = new Fondo();
	fondo->Init();

	PhysicManager::Instance()->SetContactListener(&_listener);
}

void TP4::DrawGame()
{
	Draw(fondo->DrawObject());
	if(!isEndGame)
	{
		Draw(_cronometro->DrawObject());	
	}

	for(std::list<Lata*>::const_iterator it = m_latas.begin();it != m_latas.end();++it)
	{
		Draw(((Lata*)*it)->DrawObject());
	}

	Draw(text);
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
	if(!isEndGame)
	{
		for(b2ContactEdge* ce = groundWallBody[0]->GetContactList();ce;ce = ce->next)
		{
			b2Contact* c = ce->contact;
			//SetPause(true);		
			text.setString("El Jugador Pierde");		
			isEndGame = true;
		}
	}

}

void TP4::UpdatePhysics()
{
	for(std::list<Lata*>::const_iterator it = m_latas.begin();it != m_latas.end();it++)
	{
		((Lata*)*it)->UpdatePhysics();
	}
}

void TP4::UpdateState()
{
	ActualizarContador();
}

void TP4::InitPhysics()
{		
	//Piso
	groundWallBody[0] = PhysicManager::Instance()->CreateRectangularStaticBody(150.0f,5.0f,1.0f,0.2f,0.2f);
	groundWallBody[0]->SetTransform(b2Vec2(100.0f,140.0f),0.0f);
	
	//Techo
	groundWallBody[1] = PhysicManager::Instance()->CreateRectangularStaticBody(150.0f,5.0f,1.0f,0.2f,0.2f);
	groundWallBody[1]->SetTransform(b2Vec2(100.0f,10.0f),0.0f);
	
	//Pared Izquierda
	groundWallBody[2] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,135.0f,1.0f,0.2f,0.2f);
	groundWallBody[2]->SetTransform(b2Vec2(22.0f,75.0f),0.0f);

	//Pared Derecha
	groundWallBody[3] = PhysicManager::Instance()->CreateRectangularStaticBody(5.0f,135.0f,1.0f,0.2f,0.1f);
	groundWallBody[3]->SetTransform(b2Vec2(178.0f,75.0f),0.0f);

}

void TP4::ActualizarContador()
{
	if(!isEndGame)
	{
		_cronometro->Update();	
		if(((Cronometro*)_cronometro)->isEndTime())
		{
			text.setString("El Jugador Gana");
			isEndGame = true;
		}
	}
}