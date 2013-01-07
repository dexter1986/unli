#include"Game.h"

void Game::Go(){
	//Oculta el cursor
	pWnd->ShowMouseCursor(false);
	pWnd->SetFramerateLimit(30);
	//objeto para recibir eventos
	Event evt;

	//Inicializa los objetos del juego
	Init();
	
	
	/*if(pWnd->IsOpened())
	{
		Intro();
		ShowMenu();		
	}*/
	
	while(pWnd->IsOpened()){
		//procesar eventos
		while (pWnd->GetEvent(evt))
			ProcessEvent(evt);

		ProcessInput();

		//procesar colisiones
		ProcessCollisions();
		
		//actualizar estados de objetos
		UpdateGame();
		
		pWnd->Clear();

		//Dibuja los objetos
		DrawGame();
		
		pWnd->Display();
	}
	StopMusic();	
}

Game::Game(int alto, int ancho, string titulo)
{	
	wnd_alto = alto;
	wnd_ancho = ancho;	
	pWnd = new RenderWindow(VideoMode(wnd_ancho,wnd_alto,32),titulo);
	in = &pWnd->GetInput();	 
	srand((unsigned int) time(NULL));
}

void Game::Init()
{
	LoadSound();
	
	isGame = false;
	
	vidas = MAX_VIDAS;
	puntos = 0;
	cant_balas = 0;
	cant_patos = 0;
	force = MIN_FORCE;
	windTime = 0;
	windNextTime = 10;

	for(int i=0;i<MAX_BALAS;i++)
	{
		balas[i] = NULL;
	}

	patosNextTime = 0;
	patosTime = 0;
	for(int i=0;i<MAX_PATOS;i++)
	{
		patos[i] = NULL;
	}

	for(int i=0;i<MAX_VIDAS;i++)
	{
		patosNegro [i] = NULL;
	}

	background = new Background();
	background->Init(pWnd);
	nubes = new NubesParallax();
	nubes->Init(pWnd);
	cannon = new Cannon();
	cannon->Init(pWnd);
	energyLevel = new EnergyLevel(cannon->GetPos(),cannon->GetSize());
	energyLevel->Init(pWnd);
	wind = new WindBlow();
	wind->Init(pWnd);
}

void Game::LoadSound()
{
	snd_disparo_bff.LoadFromFile("..\\Musica\\Disparo.wav");
	snd_disparo.SetBuffer(snd_disparo_bff);	

	snd_pato_hit_bff.LoadFromFile("..\\Musica\\Pato hit.wav");
	snd_pato_hit.SetBuffer(snd_pato_hit_bff);

	snd_loadbff.LoadFromFile("..\\Musica\\Load.wav");
	snd_load.SetBuffer(snd_loadbff);	
	snd_load.SetLoop(true);	
	snd_load.SetVolume(10.0f);
	
}

Game::~Game()
{	
	
	for(int i=0;i<MAX_VIDAS;i++)
	{
		if(patosNegro[i] != NULL)
			delete patosNegro[i];
	}

	for(int i=0;i<MAX_PATOS;i++)
	{
		if(patos[i] != NULL)
			delete patos[i];
	}

	for(int i=0;i<MAX_BALAS;i++)
	{
		if(balas[i] != NULL)
			delete balas[i];
	}

	delete wind;
	delete energyLevel;
	delete cannon;
	delete nubes;
	delete background;
	delete pWnd;
}

void Game::ProcessEvent(Event &evt)
{
	if(evt.Type == Event::Closed)
	{	
		Creditos();
		Quit();
	}
	
	if(evt.Type == Event::KeyPressed)
	{
		if(evt.Key.Code == Key::Escape)
		{	
			Creditos();
			Quit();
		}
	}

	if(evt.Type == Event::MouseButtonPressed)
	{
		if(evt.MouseButton.Button == Mouse::Left)
		{
			
		}
	}
	else if(evt.Type == Event::MouseButtonReleased)
	{
		if(evt.MouseButton.Button == Mouse::Left)
		{
			if(cant_balas < MAX_BALAS)
			{
				cant_balas++;
				for(int i=0;i<MAX_BALAS;i++)
				{
					if(balas[i] == NULL)
					{
						balas[i] = new Bala(cannon->GetPosCano(),cannon->GetLargoCano(),cannon->GetRad(),force,wind->GetForceLevel());						
						snd_load.Stop();						
						snd_disparo.Play();						
						break;
					}
				}				
			}
			force = MIN_FORCE;
			energyLevel->SetForceLevel(force);
		}
	}
}

void Game::Quit()
{
	//Muestra el cursor
	pWnd->ShowMouseCursor(true);
	pWnd->Close();
}

void Game::ProcessCollisions()
{
	for(int i=0;i<MAX_BALAS;i++)
	{
		if(balas[i] != NULL)
		{
			Vector2f pos = balas[i]->GetPos();
			if(pos.x > 0 && pos.x < pWnd->GetWidth() && pos.y > 0 && pos.y < pWnd->GetHeight())
			{
				//Comprobar si le pega a un pato
				for(int i=0;i<MAX_PATOS;i++)
				{
					if(patos[i] != NULL)
					{	
						if(patos[i]->Hit((int)pos.x,(int)pos.y))
						{
							snd_pato_hit.Play();
							CrearPatos(patos[i]);
						}						
					}
				}
			}
			else
			{
				delete balas[i];
				balas[i] = NULL;
				cant_balas--;
			}
		}
	}

	for(int i=0;i<MAX_PATOS;i++)
	{
		if(patos[i] != NULL)
		{
			Vector2f pos_pato = patos[i]->GetPos();
			if(pos_pato.x > 0 && pos_pato.x  < pWnd->GetWidth() && pos_pato.y < pWnd->GetHeight())
			{
				if(pos_pato.y > pWnd->GetHeight() - 130)
				{	
					delete patos[i];
					patos[i] = NULL;
					cant_patos--;
					
					vidas--;
					patosNegro[vidas] = new PatoNegro(vidas);
					patosNegro[vidas]->Init(pWnd);					
				}
			}
			else
			{
				delete patos[i];
				patos[i] = NULL;
				cant_patos--;
			}
		}
	}
}

void Game::CrearPatos(Pato *pato)
{
	int count = 0;
	patosTime = 0;
	if(cant_patos < 10 && rand()%1 == 0)
	{
		count++;
		CrearPato(0,pato->getForce());
	}

	if(cant_patos < 10 && rand()%1 == 0)
	{
		count++;
		CrearPato(0,pato->getForce() + rand()%20+20);
	}

	if(cant_patos < 10 && count < 2 && rand()%1 == 0)
	{
		count++;
		int cant = rand()%1+2;
		for(int i=0;i<cant;i++)
		{	
			CrearPato(0,0);
		}
	}

}

void Game::CrearPato(float angulo,float force)
{
	if(cant_patos < MAX_PATOS)
	{
		cant_patos++;
		for(int i=0;i<MAX_PATOS;i++)
		{
			if(patos[i] == NULL)
			{
				patos[i] = new Pato(angulo,force);
				patos[i]->Init(pWnd);
				break;
			}
		}				
	}
}

void Game::DrawGame()
{
	background->Draw(pWnd);
	cannon->Draw(pWnd);

	for(int i=0;i<MAX_VIDAS;i++)
	{
		if(patosNegro[i] != NULL)
			patosNegro[i]->Draw(pWnd);
	}

	energyLevel->Draw(pWnd);
	for(int i=0;i<MAX_BALAS;i++)
	{
		if(balas[i] != NULL)
			balas[i]->Draw(pWnd);
	}

	for(int i=0;i<MAX_PATOS;i++)
	{
		if(patos[i] != NULL)
			patos[i]->Draw(pWnd);
	}

	nubes->Draw(pWnd);
	wind->Draw(pWnd);
}

void Game::ProcessInput()
{
	int x = in->GetMouseX();
	float c =  pWnd->GetWidth() /2.0f;
	float rad;
	if(x == c)
	{
		rad = 0;
	}
	else
	{
		rad = 90 - (x * 90 / c);
	}
	cannon->Rotate(rad);

	if(in->IsMouseButtonDown(Mouse::Left))
	{
		if(cant_balas < MAX_BALAS && force < MAX_FORCE)
		{
			if(snd_load.GetStatus() != Sound::Status::Playing)
				snd_load.Play();
			
			force++;
			energyLevel->SetForceLevel(force);
		}
	}
}

void Game::UpdateGame()
{	
	if(vidas == 0)
	{	
		StopMusic();
		//Juego finalizado
		GameOver();		
		//Mostrar puntaje			
		Creditos();
		Quit();
	}
	else
	{
		background->Update(pWnd);	
		cannon->Update(pWnd);
		energyLevel->Update(pWnd);

		for(int i=0;i<MAX_BALAS;i++)
		{
			if(balas[i] != NULL)
				balas[i]->Update(pWnd);
		}

		for(int i=0;i<MAX_PATOS;i++)
		{
			if(patos[i] != NULL)
			{
				patos[i]->Update(pWnd);
				if(patos[i]->getEstado() == Pato::Estado::borrar)
				{
					delete patos[i];
					patos[i] = NULL;
					cant_patos--;
				}
			}
		}

		float t = pWnd->GetFrameTime();

		patosTime += t;
		if(patosNextTime < patosTime)
		{
			patosNextTime = (float) (rand()%5+5);
			patosTime = 0;
			CrearPato(0,0);
		}
	
		windTime += t;
	
		if(windNextTime <= windTime)
		{
			windNextTime =(float) (rand()%10 + 10);		
			windTime = 0;
			wind->InitWind();
			nubes->SetWindForce(wind->GetForceLevel());		
		}

		nubes->Update(pWnd);
		wind->Update(pWnd);
	}
}

void Game::Intro()
{
	IntroGame intro;

	MusicMenu();
	
	float maxIntro = 0.0f;
	float maxFrame = 0.0f;
	float old_vol = musica.GetVolume();
	bool isIntroEnd = false;
	
	while(maxIntro < 100.0)
	{		
		if(!isIntroEnd && maxFrame > 10.0f)
		{
			maxFrame = 0.0f;
			intro.NextFrame();
			if(!intro.isNextFrame())
				isIntroEnd = true;
		}

		if(isIntroEnd)
		{
			if(musica.GetVolume() > 2)
			{
				musica.SetVolume(musica.GetVolume()-0.5f);
			}
			else
			{
				break;
			}
		}

		pWnd->Clear();

		intro.Draw(pWnd);
		
		pWnd->Display();
		
		maxFrame += pWnd->GetFrameTime();
		maxIntro += pWnd->GetFrameTime();
	}

	musica.Stop();
	musica.SetVolume(old_vol);
}

void Game::GameOver()
{	
	snd_load.Stop();

	int alpha = 0;
	Image img;
	img.LoadFromFile("..//Imagenes//Background - Game over.png");
	Sprite intro;
	intro.SetImage(img);

	intro.SetColor(sf::Color(255, 255, 255, alpha));

	MusicGameOver();

	float sleep = 0.0;
		
	while(sleep < 10.0)
	{	
		if ((alpha < 255))
		{
			intro.SetColor(sf::Color(255, 255, 255, alpha += 1));
		}

		pWnd->Clear();

		pWnd->Draw(intro);
				
		pWnd->Display();
		
		sleep += pWnd->GetFrameTime();
	}
}

void Game::Creditos()
{	
	Image img;
	img.LoadFromFile("..//Imagenes//Creditos.png");
	Sprite intro;
	intro.SetImage(img);

	float sleep = 0.0;

	while(sleep < 2.0)
	{
		pWnd->Clear();
		
		pWnd->Draw(intro);
		
		pWnd->Display();
	
		sleep += pWnd->GetFrameTime();
	}

	StopMusic();
}

void Game::MusicGame()
{
	if(musica.OpenFromFile("..//Musica//music.ogg"))
	{
		isMusicEnable = true;		
		musica.SetLoop(true);
		musica.Play();
	}else
	{
		isMusicEnable = false;
	}					
}

void Game::MusicMenu()
{
	if(musica.OpenFromFile("..//Musica//music2.ogg"))
	{
		isMusicEnable = true;		
		musica.SetLoop(true);
		musica.Play();
	}else
	{
		isMusicEnable = false;
	}
}

void Game::MusicGameOver()
{
	if(musica.OpenFromFile("..//Musica//Game Over.ogg"))
	{
		isMusicEnable = true;		
		musica.SetLoop(true);
		musica.Play();
	}else
	{
		isMusicEnable = false;
	}	
}

void Game::StopMusic()
{
	if(isMusicEnable)		
		musica.Stop();
}

void Game::ShowMenu()
{
	/*bool salir = false;
	Event evt;
	Image img;
	img.LoadFromFile("..//Imagenes//Menu.png");
	Sprite menu;
	menu.SetImage(img);
	menu.SetPosition(200,200);
	
	while(pWnd->IsOpened() && !salir){	
		
		while (pWnd->GetEvent(evt))
		{
			if(evt.Type == Event::Closed)
			{	
				Creditos();
				Quit();
			}
			if(evt.Type == Event::KeyPressed)
			{
				if(evt.Key.Code == Key::Escape)
				{	
					Creditos();
					Quit();
				}else if(evt.Key.Code == Key::Space)
				{
					salir = true;
					isGame = true;
					break;
				}
			}
		}

		pWnd->Clear();

			pWnd->Draw(menu);

		pWnd->Display();
				
	}*/

	if(pWnd->IsOpened())
	{
		StopMusic();
		MusicGame();
	}
}



