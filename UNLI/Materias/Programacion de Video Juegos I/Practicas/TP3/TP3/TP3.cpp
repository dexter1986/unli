#include "TP3.h"

TP3::TP3(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{
	contador = 10;
	for(int i=0;i<10;i++)
	{
		_c_bloques[i] = false;
	}
	

	for(int i=0;i<10;i++)
	{
		_n_bloques[i] = i;
	}
	
	isGamePause = false;
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
		bloques[i] = new Bloque(i,i);
		Vector2f pos = bloques[i]->GetPosition();
		pos.x = i * 45.0f + 200.0f;
		bloques[i]->SetPosition(pos.x,pos.y);
		bloques[i]->Init();
	}
}

void TP3::DrawGame()
{
	Draw(fondo->DrawObject());
	RenderWindow* wnd;
	wnd = _Draw();

	for(int i=0;i<10;i++)
	{	
		Draw(bloques[i]->DrawObject());
		bloques[i]->Draw(wnd);
	}
	Draw(personaje->DrawObject());
}

void TP3::UpdatePoolEvents(Event& evt)
{	
	if(!isGamePause)
		personaje->UpdatePoolEvents(evt);
}

void TP3::UpdateState()
{
	if(!isGamePause && contador==0)
	{
		isGamePause = true;
		for(int i=0;i<10;i++)
		{
			((Bloque*)bloques[i])->SetNro(_n_bloques[i],_c_bloques[i]);
		}
	}
}

void TP3::UpdateEvents()
{		
	if(!isGamePause)
		personaje->Update();
}

void TP3::CheckCollitions()
{	
	for(int i=0;i<10;i++)
	{
		if(!_c_bloques[i] && personaje->TestCollitions(*bloques[i]))
		{
			bloques[i]->CheckCollitions(true);
			_c_bloques[i] = true;
			contador--;
			break;
		}
	}
}

void TP3::UpdatePhysics()
{

}

void TP3::InitPhysics()
{		
		
}
