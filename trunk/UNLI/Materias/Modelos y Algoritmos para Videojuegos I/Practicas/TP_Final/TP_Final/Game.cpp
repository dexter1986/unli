#include"Game.h"

void Game::Go(){
	//pWnd->ShowMouseCursor(false);

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

		//procesar colisiones
		ProcessCollisions();
		
		//actualizar estados de objetos
		UpdateGame();
		
		pWnd->Clear();
		
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

void Game::ProcessCollisions()
{
	if(!letra->Enable())
	{
		letra_fail.Play();
		vidas--;
		hud->UpdateVidas(vidas);
		letra->Reset();
	}
}

void Game::DrawGame()
{
	zone->Draw(pWnd);
	circulo->Draw(pWnd);
	hud->Draw(pWnd);		
	letra->Draw(pWnd);
}

void Game::UpdateGame()
{
	circulo->Update(pWnd);	
	letra->Update(pWnd);

	if(vidas < 1)
	{	
		StopMusic();
		//Juego finalizado
		level_fail.Play();
		
		//Mostrar puntaje			
		Creditos();
		pWnd->Close();
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
	StopMusic();
	if(isGame)
		ShowPuntaje();	
	
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
}

void Game::ProcessEvent(Event &evt)
{
	if(evt.Type == Event::Closed)
	{	
		Creditos();
		pWnd->Close();
	}
	
	if(evt.Type == Event::KeyPressed)
	{
		if(evt.Key.Code == Key::Escape)
		{	
			Creditos();
			pWnd->Close();
		}else
		{
			char tecla =  evt.Key.Code;
			if(zone->Hit(letra->GetRect()))
			{
				if(letra->Compare(tecla))
				{
					letra_ok.Play();
					count_letras++;
					puntos += 10;
					extra_pnt++;
					if(extra_pnt > 10) 
					{
						puntos += puntos / 10 + 20;
						extra_pnt = 0;						
						extra_puntos.Play();
					}
					hud->UpdatePuntos(puntos);					
				}else
				{
					letra_fail.Play();
					vidas--;
					hud->UpdateVidas(vidas);
					circulo->Enable(false);
				}
			}else
			{
				letra_fail.Play();
				vidas--;
				hud->UpdateVidas(vidas);
				circulo->Enable(false);
			}
			letra->Reset();
		}
	}

	if(evt.Type == Event::MouseButtonPressed)
	{
		if(evt.MouseButton.Button == Mouse::Left)
		{
			if(circulo->Hit(evt.MouseButton.X,evt.MouseButton.Y))	
				vida_up.Play();
				vidas++;
			    hud->UpdateVidas(vidas);
		}
	}
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

void Game::Init()
{
	LoadSound();
	
	isGame = false;
	letra = new Letra(wnd_ancho,wnd_alto,1);

	zone = new	Zone(wnd_ancho,wnd_alto);
	circulo = new Circulo(wnd_ancho,wnd_alto);
	vidas = 5;
	puntos = 0;
	extra_pnt = 0;
	count_letras = 0;
	hud = new Hud(wnd_ancho,wnd_alto);
	hud->UpdatePuntos(puntos);
	hud->UpdateVidas(vidas);
	hud->Enable(true);
}

void Game::LoadSound()
{
	vida_up_bff.LoadFromFile("..\\Musica\\mario_1-up.wav");
	vida_up.SetBuffer(vida_up_bff);
	letra_fail_bff.LoadFromFile("..\\Musica\\mario_stomp.wav");
	letra_fail.SetBuffer(letra_fail_bff);
	letra_ok_bff.LoadFromFile("..\\Musica\\mario_coin.wav");
	letra_ok.SetBuffer(letra_ok_bff);
	level_fail_bff.LoadFromFile("..\\Musica\\mario_key.wav");
	level_fail.SetBuffer(level_fail_bff);
	extra_puntos_bff.LoadFromFile("..\\Musica\\mario_throw.wav");
	extra_puntos.SetBuffer(extra_puntos_bff);
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
				pWnd->Close();
			}
			if(evt.Type == Event::KeyPressed)
			{
				if(evt.Key.Code == Key::Escape)
				{	
					Creditos();
					pWnd->Close();
				}else if(evt.Key.Code == Key::Space)
				{
					salir = true;
					isGame = true;
					break;
				}
			}
		}

		pWnd->Clear();
			
			zone->Draw(pWnd);	
			hud->Draw(pWnd);		
			letra->Draw(pWnd);

			pWnd->Draw(menu);

		pWnd->Display();
				
	}

	if(pWnd->IsOpened())
	{
		StopMusic();
		MusicGame();
	}
}

void Game::ShowPuntaje()
{
	Image img;
	img.LoadFromFile("..//Imagenes//resumen.png");
	Sprite resumen;
	resumen.SetImage(img);
	resumen.SetPosition(200,200);	

	Font font;
	font.LoadFromFile("..\\Fonts\\Bolstbo_.ttf");
	String resumen_text;
	resumen_text.SetFont(font);
	resumen_text.SetPosition(240,270);

	stringstream st_s;
	string aux;
	string str;
		
	st_s << count_letras;			
	st_s >> aux;
	
	str = "Letras: " + aux;
	
	st_s.clear();
	st_s << puntos;
	st_s >> aux;

	str += "\nPuntos: " + aux;
		
	resumen_text.SetText(str);

	float sleep = 0.0;

	while(sleep < 5.0)
	{
		pWnd->Clear();
		
		DrawGame();
		pWnd->Draw(resumen);
		pWnd->Draw(resumen_text);
		
		pWnd->Display();
	
		sleep += pWnd->GetFrameTime();
	}
}

Game::~Game()
{
	delete letra;
	delete zone;
	delete hud;
	delete circulo;
	delete  pWnd;
}

