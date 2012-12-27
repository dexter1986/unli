#include"Game.h"

void Game::Go(){
	//Oculta el cursor
	pWnd->ShowMouseCursor(false);
	pWnd->SetFramerateLimit(30);
	//objeto para recibir eventos
	Event evt;

	//Inicializa los objetos del juego
	Init();
	
	/*
	if(pWnd->IsOpened())
	{
		Intro();
		ShowMenu();		
	}
	*/
	while(pWnd->IsOpened()){
		//procesar eventos
		while (pWnd->GetEvent(evt))
			ProcessEvent(evt);

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
	
	vidas = 3;
	puntos = 0;

	background = new Background();
	nubes = new NubesParallax();

}

void Game::LoadSound()
{
	//sonido_bff.LoadFromFile("..\\Musica\\mario_1-up.wav");
	//sonido.SetBuffer(sonido_bff);	
}

Game::~Game()
{
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
	nubes->Draw(pWnd);
}

void Game::UpdateGame()
{
	background->Update(pWnd);
	nubes->Update(pWnd);

	if(rand()%1000 > 900)
		nubes->Sentido(rand()%2);

	if(vidas == 0)
	{	
		StopMusic();

		//Juego finalizado
				
		//Mostrar puntaje			
		Creditos();
		Quit();
	}
}

void Game::Intro()
{
	bool isHowto = false;
	Image img;
	img.LoadFromFile("..//Imagenes//Intro.png");
	Sprite intro;
	intro.SetImage(img);

	MusicMenu();

	float sleep = 0.0;

	while(sleep < 8.0)
	{
		pWnd->Clear();
		
		pWnd->Draw(intro);
		
		pWnd->Display();
		
		if(sleep > 3 && !isHowto)
		{
			isHowto =  true;
			img.LoadFromFile("..//Imagenes//HowTo.png");
			intro.SetImage(img);
			sleep = 3.0;
		}

		sleep += pWnd->GetFrameTime();
	}
}

void Game::Creditos()
{	
	/*StopMusic();
		
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
	}*/
}

void Game::MusicGame()
{
	if(musica.OpenFromFile("..//Musica//tema1.ogg"))
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
	if(musica.OpenFromFile("..//Musica//tema2.ogg"))
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
				
	}

	if(pWnd->IsOpened())
	{
		StopMusic();
		MusicGame();
	}
}



