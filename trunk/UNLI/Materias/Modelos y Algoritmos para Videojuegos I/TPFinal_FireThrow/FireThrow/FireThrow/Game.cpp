#include"Game.h"

void Game::Go(){
	
	//Oculta el cursor	
	//pWnd->ShowMouseCursor(false);	
	pWnd->SetFramerateLimit(30);
	
	LoadSound();
	
	//Inicializa los objetos del juego
	Instance();

	PrincipalLoop();	
}


void Game::PrincipalLoop()
{   
	isShowIntro = false;
	isQuit = false;
	
	while(pWnd->IsOpened() && !isQuit){
		isPause = false;
		isMenuGeneral = false;
		
		Init();	

		if(!isShowIntro && pWnd->IsOpened())
		{
			Intro();	
			isShowIntro = true;
		}
	
		if(pWnd->IsOpened())
		{
			ShowMenu();	
		}	

		while(pWnd->IsOpened() && !isQuit && !isMenuGeneral){
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
	}
	
	StopMusic();	
	Quit();
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
	isGame = false;
	
	force = MIN_FORCE;
	windTime = 0;
	windNextTime = 10;

	menu->Init(pWnd);

	background->Init(pWnd);		
	
	edificio->Init(pWnd);
	
	Vector2f *vect = edificio->GetPos(true);

	cannon_p1->Init(pWnd,vect);

	delete vect;

	vect = edificio->GetPos(false);

	cannon_p2->Init(pWnd,vect);

	delete vect;
}

void Game::Instance()
{
	menu = new Menu();
	background = new Background();
	edificio = new Edificio();

	cannon_p1 = new Cannon();
	cannon_p2 = new Cannon();
	
}

void Game::LoadSound()
{
	/*snd_disparo_bff.LoadFromFile("..\\Musica\\Disparo.wav");
	snd_disparo.SetBuffer(snd_disparo_bff);	

	snd_pato_hit_bff.LoadFromFile("..\\Musica\\Pato hit.wav");
	snd_pato_hit.SetBuffer(snd_pato_hit_bff);

	snd_loadbff.LoadFromFile("..\\Musica\\Load.wav");
	snd_load.SetBuffer(snd_loadbff);	
	snd_load.SetLoop(true);	
	snd_load.SetVolume(10.0f);	*/
}

Game::~Game()
{	
	delete cannon_p1;	
	delete cannon_p2;	
	delete edificio;
	delete background;	
	delete menu;	
}

void Game::ProcessEvent(Event &evt)
{
	if(evt.Type == Event::Closed)
	{		
		isQuit = true;		
	}
	
	if(isPause)
	{
		if(in->IsMouseButtonDown(Mouse::Left))
		{
			if(menu->Hit(in->GetMouseX(),in->GetMouseY()))
			{			
				if(menu->GetState() == Menu::MENU_STATE::CONTINUAR)
				{
					isPause = false;
				}
				else if(menu->GetState() == Menu::MENU_STATE::REINICIAR)
				{
					
				}
				else if(menu->GetState() == Menu::MENU_STATE::MENU)
				{
					isMenuGeneral = true;
				}
			}
		}
		else
		{
			menu->Test(in->GetMouseX(),in->GetMouseY());
		}
	}
	else
	{
		if(evt.Type == Event::KeyPressed)
			{
				if(evt.Key.Code == Key::Escape)
				{	
					isPause = true;			
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
			
				}
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
	
}

void Game::DrawGame()
{
	background->Draw(pWnd);
	
	edificio->Draw(pWnd);
	
	cannon_p1->Draw(pWnd);
	cannon_p2->Draw(pWnd);

	if(isPause)
		menu->Draw(pWnd);
	
}

void Game::ProcessInput()
{
	if(!isPause)
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
		cannon_p1->Rotate(rad);
		cannon_p2->Rotate(rad);

		if(in->IsMouseButtonDown(Mouse::Left))
		{
		
		}
	}
}

void Game::UpdateGame()
{	
	if(!isPause)
	{
		//if(vidas == 0)
		//{	
		//	StopMusic();
		//	//Juego finalizado
		//	GameOver();		
		//	//Mostrar puntaje			
		//	Creditos();
		//	Quit();
		//}
		//else
		//{
			background->Update(pWnd);	
			edificio->Update(pWnd);
			cannon_p1->Update(pWnd);	
			cannon_p2->Update(pWnd);	
		//}
	}
}

void Game::Intro()
{
	IntroGame intro;

	MusicMenu();

	Event evt;

	float maxIntro = 1.0;

	while(maxIntro > 0)
	{		
		//procesar eventos
		while (pWnd->GetEvent(evt))
		{
		
		}

		pWnd->Clear();

		intro.Draw(pWnd);
		
		pWnd->Display();
		
		maxIntro -= pWnd->GetFrameTime();
	}
}

void Game::GameOver()
{	
	/*snd_load.Stop();*/
	Event evt;
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
		//procesar eventos
		while (pWnd->GetEvent(evt))
		{}

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
	Event evt;
	float sleep = 0.0;

	while(sleep < 2.0)
	{
		//procesar eventos
		while (pWnd->GetEvent(evt))
		{}

		pWnd->Clear();
		
		pWnd->Draw(intro);
		
		pWnd->Display();
	
		sleep += pWnd->GetFrameTime();
	}

	StopMusic();
}

void Game::MusicGame()
{
	/*
	if(musica.OpenFromFile("..//Musica//music.ogg"))
	{
		isMusicEnable = true;		
		musica.SetLoop(true);
		musica.Play();
	}else
	{
		isMusicEnable = false;
	}
	*/
}

void Game::MusicMenu()
{
	/*
	if(musica.OpenFromFile("..//Musica//music2.ogg"))
	{
		isMusicEnable = true;		
		musica.SetLoop(true);
		musica.Play();
	}else
	{
		isMusicEnable = false;
	}
	*/
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
	bool salir = false;
	Event evt;
	
	while(pWnd->IsOpened() && !salir && !isQuit){	
		
		while (pWnd->GetEvent(evt))
		{	
			if(evt.Type == Event::Closed)
			{	
				isQuit = true;
			}
		}
		
		if(in->IsMouseButtonDown(Mouse::Left))
		{
			if(menu->Hit(in->GetMouseX(),in->GetMouseY()))
			{			
				if(menu->GetState() == Menu::MENU_STATE::SALIR)
				{
					isQuit = true;
				}
				else if(menu->GetState() == Menu::MENU_STATE::JUGAR)
				{
					salir = true;
				}
			}
		}
		else
		{
			menu->Test(in->GetMouseX(),in->GetMouseY());
		}

		pWnd->Clear();
		
			background->Draw(pWnd);
			menu->Draw(pWnd);

		pWnd->Display();
	}
	
	menu->SetMenu(Menu::MENU_TYPE::PAUSA);

	if(pWnd->IsOpened())
	{		

		StopMusic();
		MusicGame();
	}
}



