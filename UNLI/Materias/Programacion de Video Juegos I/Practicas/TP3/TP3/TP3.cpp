#include "TP3.h"
#include "Constantes.h"

TP3::TP3(int ancho, int alto,std::string titulo):GameBase(ancho,alto,titulo)
{
	textoContador.setFont(ImageManager::Instance()->GetFont());
	textoContador.setCharacterSize(24);
	textoContador.setPosition(650,20);
	tiempoInicio = _reloj.getElapsedTime().asSeconds() + C::TIEMPO_JUEGO;

	contador = 10;
	for(int i=0;i<10;i++)
	{
		_c_bloques[i] = false;
		_c_ord_bloques[i] = false;
	}
	
	int val = 0;
	bool exists = false;
	for(int i=0;i<10;++i)
	{
		val = rand()%999+1;
		exists = false;
		for(int j=0;j<i;++j)
		{
			if(_n_bloques[j] == val)
			{
				exists = true;
				break;
			}			
		}
		if(!exists)
		{
			_n_bloques[i] = val;
			_n_ord_bloques[i] = val;
		}
	}
	//Vector Ordenado
	//Ordenamiento por metodo de burbuja
	int aux=0;
	for(int i=0;i<10;++i)
	{
		for(int j=i+1;j<10;++j)
		{
			if(_n_ord_bloques[i] > _n_ord_bloques[j])
			{
				aux = _n_ord_bloques[i];
				_n_ord_bloques[i] = _n_ord_bloques[j];
				_n_ord_bloques[j] = aux;
			}
		}
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
		bloques[i] = new Bloque(_n_bloques[i],i);
		Vector2f pos = bloques[i]->GetPosition();
		pos.x = i * 45.0f + 200.0f;
		bloques[i]->SetPosition(pos.x,pos.y);
		bloques[i]->Init();
	}
}

void TP3::DrawGame()
{
	Draw(fondo->DrawObject());
	Draw(textoContador);

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
	if(!isGamePause && (contador == 0 || tiempoFin == -1))
	{
		isGamePause = true;
		for(int i=0;i<10;i++)
		{
			((Bloque*)bloques[i])->SetNro(_n_ord_bloques[i],_c_ord_bloques[i]);
		}
	}

	if(!isGamePause)
	{
		ActualizarContador();
	}
}

void TP3::ActualizarContador()
{
	tiempoFin = _reloj.getElapsedTime().asSeconds();
	
	int seconds = ((int)(tiempoInicio - tiempoFin));

	if(seconds >= 0){
		string str = "Tiempo: " + C::NumberToString(seconds);
		textoContador.setString(str);
	}else{
		textoContador.setString("El tiempo ha finalizado....");
		textoContador.setPosition(300,150);
		tiempoFin = -1;
	}
}

void TP3::UpdateEvents()
{		
	if(!isGamePause)
		personaje->Update();
}

void TP3::CheckCollitions()
{	
	int index = 0; 
	bool coll = false;
	for(int i=0;i<10;i++)
	{
		if(!_c_bloques[i])
		{
			coll = personaje->TestCollitions(*bloques[i]);
			if(coll)
			{
				index = 10 - contador;
				if(_n_bloques[i] == _n_ord_bloques[index])
				{
					bloques[i]->CheckCollitions(true);
					_c_bloques[i] = true;
					_c_ord_bloques[index] = true;
					contador--;				
				}else
				{
					tiempoInicio -= 10;				
				}
				break;
			}
		}
	}
}

void TP3::UpdatePhysics()
{

}

void TP3::InitPhysics()
{		
		
}
