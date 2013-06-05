#include "TP3.h"

TP3::TP3(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{
	
}

TP3::~TP3(void)
{	
	for(int i=0;i<10;i++)
	{
		delete bloques[i];		
	}
	delete personaje;
	delete fondo;
}

void TP3::Init()
{	
	fondo = new Fondo();
	fondo->Init();
	personaje = new Personaje();
	personaje->Init();

	for(int i=0;i<10;i++)
	{
		bloques[i] = new Bloque();
		Vector2f pos = bloques[i]->GetPosition();
		pos.x = i * 45.0f + 200.0f;
		bloques[i]->SetPosition(pos.x,pos.y);
		bloques[i]->Init();
	}
}

void TP3::DrawGame()
{
	Draw(fondo->DrawObject());
	for(int i=0;i<10;i++)
	{	
		Draw(bloques[i]->DrawObject());
	}
	Draw(personaje->DrawObject());
}

void TP3::UpdatePoolEvents(Event& evt)
{	
	personaje->UpdatePoolEvents(evt);
}

void TP3::UpdateEvents()
{		
	if(Keyboard::isKeyPressed(Keyboard::Up))
	{
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Down))
	{
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Left))
	{
	}

	if(Keyboard::isKeyPressed(Keyboard::Right))	
	{
	}
	personaje->Update();
}

void TP3::CheckCollitions()
{	
}

void TP3::UpdatePhysics()
{

}

void TP3::InitPhysics()
{		
		
}
