#include "TP5.h"

TP5::TP5(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{	
	text.setFont(ImageManager::Instance()->GetFont());	
	text.setColor(Color::Black);
	text.setCharacterSize(20);		
	text.setPosition(300,150);	
	isGameFinish = false;
	isGamePause = false;
	pos_x = 100.0f;
	pos_y = 52.0f; 
	vel_x = 3;	
	piso = 0;
}

TP5::~TP5(void)
{	
	for(int i=0;i<5;i++)
	{
		for(int x=0;x<8;x++)
		{
			if(vagones[i][x] != NULL)
			{
				delete vagones[i][x];
			}
		}
	}
	delete lista;
	delete cronometro;	
	delete cronometro_5seg;
	delete fondo;	
}

void TP5::Init()
{	
	fondo = new Fondo();
	fondo->Init();
	cronometro = new Cronometro(C::TIEMPO_JUEGO);
	cronometro->Init();

	cronometro_5seg = new Cronometro(5);
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
	
	for(int i=0;i<5;i++)
	{
		for(int x=0;x<8;x++)
		{
			vagones[i][x] = NULL;
		}
	}
	
	int vp = 0;
	int vpy = 0; 
	//Vagones x piso
	for(int i=1;i<5;i++)
	{
		vp = rand()%4;
		
		if(vp == 0)
			vp = 1;

		vpy = 2; 

		for(int y=0;y<vp;y++)
		{
			vpy += rand()%3+1;
			
			if(vpy > 6)
			{	
				vpy = 6;
				if(vagones[i][vpy] != NULL)
					break;
			}
			
			Vagon* v = new Vagon();
			v->Init();
			v->SetPosition(vpy * 70,52.0f + i*120.0f);
			v->Update();
			v->SetValue(-1);
			
			vagones[i][vpy] =  v;

			if(vpy >= 6)
				break;
		}
	}
	
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
			piso++;
			pos_y += 120.0f;
			pos_x = -(lista->GetLength() * 70.0f + 120);
		}
	}
}

void TP5::DrawGame()
{
	Draw(fondo->DrawObject());	
	Draw(cronometro->DrawObject());
	
	RenderWindow* app = _Draw();

	for(int i=0;i<5;i++)
	{
		for(int x=0;x<8;x++)
		{
			if(vagones[i][x] != NULL)
			{
				vagones[i][x]->Render(app);
			}
		}
	}

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

	if(isGameFinish)
	{
		Draw(text);
	}
}

void TP5::UpdatePoolEvents(Event& evt)
{	
	if(!isGameFinish)
	{

	}
}

void TP5::UpdateState()
{
	if(!isGameFinish)
	{
		ActualizarContador();
		
		if(isGamePause)
		{
			if(((Cronometro*)cronometro_5seg)->isEndTime())
			{
				if(!lista->IsEmpty())
				{
					lista->First();
					lista->Remove();
					Ordenar();
					isGamePause = false;
					if(lista->IsEmpty())
						isGameFinish =  true;
				}
				else
				{
					isGameFinish =  true;
					isGamePause = false;
				}
			}
		}
	}
}

void TP5::ActualizarContador()
{
	if(!((Cronometro*)cronometro_5seg)->isEndTime())
	{
		cronometro_5seg->Update();
	}

	cronometro->Update();
	isGameFinish = ((Cronometro*)cronometro)->isEndTime();
	if(isGameFinish)
	{
		text.setString("El tiempo ha finalizado....");
	}
}

void TP5::UpdateEvents()
{		
	if(!isGameFinish)
	{
		if(pos_y > 500 && (pos_x + lista->GetLength() * 70 + 100) > 770)
		{
			isGameFinish = true;
			text.setString("El jugador gana....");
		}
		else
		{				
			if(!isGamePause)
			{
				pos_x+=vel_x;			
				Ordenar();
			}
		}
	}
}

void TP5::CheckCollitions()
{	
	if(!isGameFinish && !isGamePause)
	{
		for(int i=0;i<8;i++)
		{
			if(vagones[piso][i] != NULL)
			{
				if(vagones[piso][i]->TestCollitions(*lista->Last()))
				{
					isGamePause = true;
					((Cronometro*)cronometro_5seg)->ReStart();
				}
			}
		}
	}

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
