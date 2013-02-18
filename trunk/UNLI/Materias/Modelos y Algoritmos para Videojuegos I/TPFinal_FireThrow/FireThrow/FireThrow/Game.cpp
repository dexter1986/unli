#include"Game.h"

void Game::Go(){
	
	//Oculta el cursor	
	//pWnd->ShowMouseCursor(false);

	pWnd->SetFramerateLimit(30);
	//objeto para recibir eventos
	Event evt;

	//Inicializa los objetos del juego
	Init();
	
	
	if(pWnd->IsOpened())
	{
		Intro();
		ShowMenu();		
	}
	
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
	//pWnd = new RenderWindow(VideoMode(wnd_ancho,wnd_alto,32),titulo,sf::Style::Fullscreen);
	pWnd = new RenderWindow(VideoMode(wnd_ancho,wnd_alto,32),titulo);
	
	in = &pWnd->GetInput();	 
	srand((unsigned int) time(NULL));
}

void Game::Init()
{
	LoadSound();
	
	isGame = false;
	
	force = MIN_FORCE;
	windTime = 0;
	windNextTime = 10;

	menu = new Menu();
	menu->Init(pWnd);

	background = new Background();
	background->Init(pWnd);	
	cannon = new Cannon();
	cannon->Init(pWnd);

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
	delete cannon;	
	delete background;
	delete menu;
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
	menu->Draw(pWnd);
	background->Draw(pWnd);
	cannon->Draw(pWnd);
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
		
	}
}

void Game::UpdateGame()
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
		cannon->Update(pWnd);	
	//}
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
	snd_load.Stop();
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
	bool salir = false;
	Event evt;
	
	while(pWnd->IsOpened() && !salir){	
		
		while (pWnd->GetEvent(evt))
		{	
			if(evt.Type == Event::Closed)
			{	
				Quit();
			}
		}
		
		if(in->IsMouseButtonDown(Mouse::Left))
		{
			if(menu->Hit(in->GetMouseX(),in->GetMouseY()))
			{			
				if(menu->GetState() == Menu::MENU_STATE::SALIR)
				{
					Quit();
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

	if(pWnd->IsOpened())
	{
		StopMusic();
		MusicGame();
	}
}



