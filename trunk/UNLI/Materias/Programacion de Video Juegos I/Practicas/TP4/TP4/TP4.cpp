#include "TP4.h"

TP4::TP4(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{	
	text.setFont(ImageManager::Instance()->GetFont());	
	text.setCharacterSize(20);		
	text.setPosition(300,150);	
	isGamePause = false;
}

TP4::~TP4(void)
{	
	delete puerta;
	delete cronometro;
	delete personaje;
	delete fondo;
}

void TP4::Init()
{	
	fondo = new Fondo();
	fondo->Init();
	personaje = new Personaje();
	personaje->Init();
	cronometro = new Cronometro(C::TIEMPO_JUEGO);
	cronometro->Init();
	puerta = new Puerta();
	puerta->Init();
}

void TP4::DrawGame()
{
	Draw(fondo->DrawObject());	
	Draw(cronometro->DrawObject());
	Draw(puerta->DrawObject());

	Draw(personaje->DrawObject());
	if(isGamePause)
	{
		Draw(text);
	}
}

void TP4::UpdatePoolEvents(Event& evt)
{	
	if(!isGamePause)
		personaje->UpdatePoolEvents(evt);
}

void TP4::UpdateState()
{
	if(!isGamePause && (contador == 0 || tiempoFin == -1))
	{
		isGamePause = true;		
	}

	if(!isGamePause)
	{
		ActualizarContador();
	}
}

void TP4::ActualizarContador()
{
	cronometro->Update();
	isGamePause = ((Cronometro*)cronometro)->isEndTime();
	if(isGamePause)
	{
		text.setString("El tiempo ha finalizado....");
	}
}

void TP4::UpdateEvents()
{		
	if(!isGamePause)
		personaje->Update();
}

void TP4::CheckCollitions()
{	
	if(personaje->TestCollitions(*puerta))
	{
		isGamePause = true;
		text.setString("El jugador gana....");
	}
}

void TP4::UpdatePhysics()
{

}

void TP4::InitPhysics()
{		
		
}
