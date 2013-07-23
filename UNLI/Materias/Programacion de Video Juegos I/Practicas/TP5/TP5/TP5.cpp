#include "TP5.h"

TP5::TP5(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{	
	text.setFont(ImageManager::Instance()->GetFont());	
	text.setColor(Color::Black);
	text.setCharacterSize(20);		
	text.setPosition(300,150);	
	
	isGamePause = false;
	pos_x = 100.0f;
	pos_y = 52.0f; 
}

TP5::~TP5(void)
{	
	delete lista;
	delete cronometro;	
	delete fondo;	
}

void TP5::Init()
{	
	fondo = new Fondo();
	fondo->Init();
	cronometro = new Cronometro(C::TIEMPO_JUEGO);
	cronometro->Init();
	
	lista = new	Lista();

	GameObject* obj = new Locomotora();
	obj->Init();
	lista->Add(1000,obj);
	for(int i=0;i<2;i++)
	{
		obj = new Vagon();
		obj->Init();
		lista->Add(((Vagon*)obj)->GetValue(),obj);
	}
	Ordenar();
}

void TP5::Ordenar()
{
	if(!lista->IsEmpty())
	{
		int count = lista->GetLength() - 1;

		lista->Last()->SetPosition(pos_x + count * 70,pos_y);
		lista->Last()->Update();
		count--;
		lista->First()->SetPosition(pos_x+count*70.0f,pos_y);
		lista->First()->Update();
		GameObject* obj = NULL;
		while(lista->IsNext())
		{
			count--;			
			obj = lista->Next();
			if(obj != NULL)
			{
				obj->SetPosition(pos_x+count*70.0f,pos_y);
				obj->Update();
			}
			if(count == 0)
				break;
		}

		if(800 < pos_x  )
		{
			pos_y += 120.0f;
			pos_x = -(lista->GetLength() * 70 + 120);
		}
	}
}

void TP5::DrawGame()
{
	Draw(fondo->DrawObject());	
	Draw(cronometro->DrawObject());
	
	RenderWindow* app = _Draw();

	if(!lista->IsEmpty())
	{
		lista->First()->Render(app);
		GameObject* obj = NULL;
		while(lista->IsNext())
		{
			obj = lista->Next();
			if(obj != NULL)
				obj->Render(app);
		}
	}

	if(isGamePause)
	{
		Draw(text);
	}
}

void TP5::UpdatePoolEvents(Event& evt)
{	
	if(!isGamePause)
	{

	}
}

void TP5::UpdateState()
{
	if(!isGamePause)
	{
		ActualizarContador();
	}
}

void TP5::ActualizarContador()
{
	cronometro->Update();
	isGamePause = ((Cronometro*)cronometro)->isEndTime();
	if(isGamePause)
	{
		text.setString("El tiempo ha finalizado....");
	}
}

void TP5::UpdateEvents()
{		
	if(!isGamePause)
	{
		if(pos_y > 500 && (pos_x + lista->GetLength() * 70 + 100) > 770)
		{
			isGamePause = true;
			text.setString("El jugador gana....");
		}
		else
		{
			pos_x+=3;		
			Ordenar();
		}
	}
}

void TP5::CheckCollitions()
{	
	/*if(personaje->TestCollitions(*locomotora))
	{
		isGamePause = true;
		text.setString("El jugador gana....");
	}
	else
	{
		
	}*/
}

void TP5::UpdatePhysics()
{

}

void TP5::InitPhysics()
{		
		
}
