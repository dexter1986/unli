#include "TP5.h"

TP5::TP5(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{	
	text.setFont(ImageManager::Instance()->GetFont());	
	text.setColor(Color::Black);
	text.setCharacterSize(20);		
	text.setPosition(300,150);	
	
	txt_nro.setFont(ImageManager::Instance()->GetFont());
	txt_nro.setColor(Color::Black);
	txt_nro.setCharacterSize(14);		
	txt_nro.setPosition(305,205);
		
	isGameFinish = false;
	isGamePause = false;
	pos_x = 100.0f;
	pos_y = 52.0f; 
	vel_x = 3;	
	piso = 0;
	resultado_suma= 0;
	vagon_index = 0;
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
	delete ventana;
	delete lista;
	delete cronometro;	
	delete cronometro_5seg;
	delete fondo;	
}

void TP5::Init()
{	
	ventana = new Ventana();
	ventana->ReStart();

	fondo = new Fondo();
	fondo->Init();
	cronometro = new Cronometro(C::TIEMPO_JUEGO);
	cronometro->Init();

	cronometro_5seg = new Cronometro(C::TIEMPO_RESPUESTA);
	cronometro->Init();
	
	lista = new	Lista();

	GameObject* obj = new Locomotora();
	
	obj->Init();
	
	lista->Add(-1,obj);

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
		int count = lista->GetLength();

		/*lista->Last()->SetPosition(pos_x + count * 70,pos_y);
		lista->Last()->Update();
		count--;
		lista->First()->SetPosition(pos_x+count*70.0f,pos_y);
		lista->First()->Update();*/

		GameObject* obj = lista->First();
		while(obj != NULL)
		{	
			obj->SetPosition(pos_x + count * 70.0f,pos_y);
			obj->Update();			
			obj = lista->Next();
			count--;					
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

	if(isGamePause)
	{
		ventana->Render(app);
		Draw(txt_nro);
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
		if(isGamePause)
		{
			if(evt.type == Event::KeyPressed)
			{
				switch(evt.key.code)
				{
					case Keyboard::Num0:
						resultado_suma = 0;
						break;
					case Keyboard::Num1:
						resultado_suma = 1;
						break;
					case Keyboard::Num2:
						resultado_suma = 2;
						break;
					case Keyboard::Num3:
						resultado_suma = 3;
						break;
					case Keyboard::Num4:
						resultado_suma = 4;
						break;
					case Keyboard::Num5:
						resultado_suma = 5;
						break;
					case Keyboard::Num6:
						resultado_suma = 6;
						break;
					case Keyboard::Num7:
						resultado_suma = 7;
						break;
					case Keyboard::Num8:
						resultado_suma = 8;
						break;
					case Keyboard::Num9:
						resultado_suma = 8;
						break;
					case Keyboard::Return:						
							resultado_suma = stoi(valor_suma);
							if(ventana->GetValue() == resultado_suma)
							{
								valor_suma = "";
								Vagon* v = (Vagon*)vagones[piso][vagon_index];
								v->SetValue(resultado_suma);
								lista->Add(resultado_suma,v);
								vagones[piso][vagon_index] = NULL;
							}
							else
							{
								valor_suma = "";
								resultado_suma = 0;
								lista->Last();
								lista->Remove();
							}
							Ordenar();
							isGamePause = false;						
						break;
					default:
						resultado_suma = -1;
						break;
				}

				if(resultado_suma != -1)
				{
					valor_suma += C::NumberToString(resultado_suma);
					txt_nro.setString("\n\n\n\t\t\t\t\t\t\t\t"+valor_suma);				
				}
			}			
		}
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
					lista->Last();
					lista->Remove();
					Ordenar();
					isGamePause = false;
					if(lista->IsEmpty())
					{
						isGameFinish =  true;
						text.setString("El jugador pierde....");
					}
						
				}
				else
				{
					isGameFinish =  true;
					isGamePause = false;
					text.setString("El jugador pierde....");
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
				if(vagones[piso][i]->TestCollitions(*lista->First()))
				{
					vagon_index = i;					
					ventana->ReStart();
					txt_nro.setString("");
					valor_suma = "";
					resultado_suma = 0;
					((Cronometro*)cronometro_5seg)->ReStart();
					isGamePause = true;
					return;
				}
			}
		}
	}
}

void TP5::UpdatePhysics()
{

}

void TP5::InitPhysics()
{		
		
}
