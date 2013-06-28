#include "TP4.h"

TP4::TP4(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{	
	text.setFont(ImageManager::Instance()->GetFont());	
	text.setCharacterSize(20);		
	text.setPosition(300,150);	
		
	text_piso.setFont(ImageManager::Instance()->GetFont());	
	text_piso.setCharacterSize(15);		

	isGamePause = false;

	_is3 =  true;
	_is5 =  true;
	_is7 =  true;
		
}

TP4::~TP4(void)
{	
	delete puerta;
	delete cronometro;
	delete personaje;
	delete fondo;
	for(int i=0;i<9;i++)
	{
		delete managers[i];
	}
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
	
	//creacion de las colas
	CrearColas(0,C::TipoUbicacion::Derecha,1);
	CrearColas(1,C::TipoUbicacion::Derecha,3);
	CrearColas(2,C::TipoUbicacion::Derecha,5);

	//Creacion de la pilas
	CrearPila(3,C::TipoUbicacion::Izquierda,2,true);
	CrearPila(4,C::TipoUbicacion::Derecha,2);

	CrearPila(5,C::TipoUbicacion::Izquierda,4,true);
	CrearPila(6,C::TipoUbicacion::Derecha,4);
	
	CrearPila(7,C::TipoUbicacion::Izquierda,6,true);
	CrearPila(8,C::TipoUbicacion::Derecha,6);

}

void TP4::CrearColas(int index,C::TipoUbicacion ubicacion,int piso)
{
	Enemigo* aux;	

	managers[index] = new EnemigoManager(ubicacion);
	int val = rand()%1+4;
	for(int i=0;i<val;i++)
	{
		aux = managers[index]->CrearEnemigo(piso);
		aux->Init();
		managers[index]->Encolar(aux);
	}
}

void TP4::CrearPila(int index,C::TipoUbicacion ubicacion,int piso,bool isCreateData)
{
	managers[index] = new EnemigoManager(ubicacion);
	if(isCreateData)
	{
		Enemigo* aux;	
		int val = rand()%1+4;
		for(int i=0;i<val;i++)
		{
			aux = managers[index]->CrearEnemigo(piso);
			aux->Init();
			managers[index]->Push(aux);
		}
	}
}

void TP4::DrawGame()
{
	Draw(fondo->DrawObject());	
	Draw(cronometro->DrawObject());
	//Dibujar texto pisos
	string str;
	for(int i=0;i<7;i++)
	{	
		str = "Piso " + C::NumberToString(i);
		text_piso.setString(str);

		if(i == 6)
			text_piso.setPosition(10.0f,455.0f - 75.0f * i);
		else
			text_piso.setPosition(10.0f,463.0f - 75.0f * i);
		
		Draw(text_piso);
	}

	Draw(puerta->DrawObject());
	Draw(personaje->DrawObject());

	RenderWindow* app = _Draw();

	for(int i=0;i<9;i++)
	{
		managers[i]->Render(app);
	}
	
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
	{
		personaje->Update();

		for(int i=0;i<9;i++)
		{
			if(i<3)
			{
				managers[i]->Update();
			}
			else
			{
				if(i == 3)
				{
					if(_is3)
					{
						if(managers[i]->Top() != NULL)
							managers[i]->Update();
						else
							_is3 = false;
					}
					else
					{
						if(managers[i+1]->Top() != NULL)
							managers[i+1]->Update();
						else
							_is3 = true;
					}
				}
				else if(i == 5)
				{
					if(_is5)
					{
						if(managers[i]->Top() != NULL)						
							managers[i]->Update();
						else
							_is5 = false;						
					}
					else
					{
						if(managers[i+1]->Top() != NULL)						
							managers[i+1]->Update();
						else
							_is5 = true;
					}
				}
				else if(i == 7)
				{
					if(_is7)
					{
						if(managers[i]->Top() != NULL)
							managers[i]->Update();
						else
							_is7 = false;
					}else
					{	
						if(managers[i+1]->Top() != NULL)						
							managers[i+1]->Update();
						else
							_is7 = true;
					}
				}				
			}
		}
	}
}

void TP4::CheckCollitions()
{	
	if(personaje->TestCollitions(*puerta))
	{
		isGamePause = true;
		text.setString("El jugador gana....");
	}
	else
	{
		Enemigo* aux = NULL;
		float x = 0;
		for(int i=0;i<9;i++)
		{
			//Son colas
			if(i<3)
			{
				aux = managers[i]->Top();
				if(aux != NULL)
				{
					x = aux->GetPosition().x;
					//Si se va de la pantalla
					if(x < -10 || x > 900)
					{
						managers[i]->DesEncolar();					
						managers[i]->Encolar(aux);
						continue;
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				if(i == 3)
				{
					if(_is3)
					{
						aux = managers[i]->Top();
						if(aux != NULL)
						{
							x = aux->GetPosition().x;
							if(x <= 0 || x >= 800)
							{
								managers[i]->Pop();							
								managers[i+1]->Push(aux);								
								continue;
							}
						}
					}
					else
					{	
						aux = managers[i+1]->Top();
						if(aux != NULL)
						{
							x = aux->GetPosition().x;
							if(x <= 0 || x >= 800)
							{
								managers[i+1]->Pop();							
								managers[i]->Push(aux);								
								continue;
							}
						}
					}					
				}
				else if(i == 5)
				{
					if(_is5)
					{
						aux = managers[i]->Top();
						if(aux != NULL)
						{
							x = aux->GetPosition().x;
							if(x <= 0 || x >= 800)
							{
								managers[i]->Pop();							
								managers[i+1]->Push(aux);
								continue;
							}
						}
					}
					else
					{	
						aux = managers[i+1]->Top();
						if(aux != NULL)
						{
							x = aux->GetPosition().x;
							if(x <= 0 || x >= 800)
							{
								managers[i+1]->Pop();							
								managers[i]->Push(aux);
								continue;
							}
						}
					}
				}
				else if(i == 7)
				{
					if(_is7)
					{
						aux = managers[i]->Top();
						if(aux != NULL)
						{
							x = aux->GetPosition().x;
							if(x <= 0 || x >= 800)
							{
								managers[i]->Pop();							
								managers[i+1]->Push(aux);
								continue;
							}
						}
					}
					else
					{	
						aux = managers[i+1]->Top();
						if(aux != NULL)
						{
							x = aux->GetPosition().x;
							if(x <= 0 || x >= 800)
							{
								managers[i+1]->Pop();							
								managers[i]->Push(aux);
								continue;
							}
						}
					}
				}
				else
				{
					continue;
				}
			}

			if(aux != NULL && personaje->TestCollitions((GameObject&)*aux))
			{
				((Personaje*)personaje)->InitPosition();
			}
		}		
	}
}

void TP4::UpdatePhysics()
{

}

void TP4::InitPhysics()
{		
		
}
