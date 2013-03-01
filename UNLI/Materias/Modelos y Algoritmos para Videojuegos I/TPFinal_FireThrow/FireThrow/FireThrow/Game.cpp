#include"Game.h"
#include "Helper.h"

void Game::Go(){
	
	//Oculta el cursor	
	//pWnd->ShowMouseCursor(false);	
	pWnd->SetFramerateLimit(30);
	
	LoadSound();
	
	//Inicializa los objetos del juego
	Instance();

	PrincipalLoop();	

	Creditos();

	StopMusic();	

	Quit();
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

		InitLevel();

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
	
	menu->Init(pWnd);
	hud->Init(pWnd);

	background->Init(pWnd);		
	
	RefreshLevel();
}

void Game::InitLevel()
{
	background->InitWind();
	hud->InitLevel();
	hud->SetWind(background->wind_force);

	cannon_p1->SetVidas(hud->GetVidas());
	cannon_p1->SetAngulo(90.0f);
	cannon_p1->SetVelocidad(0.0f);
	cannon_p1->Fire(true);

	cannon_p2->SetVidas(hud->GetVidas());
	cannon_p2->SetAngulo(90.0f);
	cannon_p2->SetVelocidad(0.0f);
	cannon_p2->Fire(false);
	
	int aux_t = rand()%2;
	isTurnoP1 =  aux_t == 1;

	hud->SetTurno(isTurnoP1);

	isTurnoSec = 0;
	isNextTurnSec = false;
	delay_oneplayermode = 2.0f;
	aux = "";
	
	isOnePlayer = hud->GetCantJugadores() == 1;

	if(balas != NULL)
	{
		delete balas;
		balas = NULL;
	}
}

void Game::RefreshLevel()
{
	delay_oneplayermode = 2.0f;
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
	hud = new Hud();
	cannon_p1 = new Cannon();
	cannon_p2 = new Cannon();
	balas = NULL;
}

void Game::LoadSound()
{
	snd_disparo_bff.LoadFromFile("..\\Musica\\Heavy stomp.ogg");
	snd_disparo.SetBuffer(snd_disparo_bff);	
	snd_disparo.SetVolume(100);

	snd_loadbff.LoadFromFile("..\\Musica\\Explosion, rocky.ogg");
	snd_load.SetBuffer(snd_loadbff);		
	snd_load.SetVolume(100);
}

Game::~Game()
{	
	if(balas != NULL)
	{
		delete balas;
	}
	delete cannon_p1;	
	delete cannon_p2;	
	delete edificio;
	delete background;	
	delete hud;
	delete menu;	
}

void Game::ProcessEvent(Event &evt)
{
	if(evt.Type == Event::Closed)
	{		
		isQuit = true;	
		return;
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
					return;
				}
				else if(menu->GetState() == Menu::MENU_STATE::REINICIAR)
				{
					InitLevel();
					isPause = false;
					return;
				}
				else if(menu->GetState() == Menu::MENU_STATE::MENU)
				{
					isMenuGeneral = true;
					return;
				}
			}
		}
		else
		{
			menu->Test(in->GetMouseX(),in->GetMouseY());
			return;
		}
	}
	else if(isTurnoSec == 7)
	{
		if(evt.Type == Event::KeyPressed)
		{
			if(evt.Key.Code == Key::Return)
			{
				isMenuGeneral = true;					
			}
		}
	}
	else
	{
		if(!isOnePlayer || (isOnePlayer && isTurnoP1))
		{
			if(evt.Type == Event::KeyPressed)
			{
				if(evt.Key.Code == Key::Escape)
				{	
					isPause = true;	
					return;
				}

				if(evt.Key.Code == Key::Return)
				{
					isNextTurnSec = true;		
					return;
				}
				else
				{	
					if(evt.Key.Code == Key::Back)
					{
						if(!aux.empty())
						{
							aux.erase(aux.length()-1,1);
						}					
					}				
					else if(evt.Key.Code == Key::Num0 ||evt.Key.Code == Key::Num1 || evt.Key.Code == Key::Num2 ||
							evt.Key.Code == Key::Num3 ||evt.Key.Code == Key::Num4 || evt.Key.Code == Key::Num5 ||
							evt.Key.Code == Key::Num6 ||evt.Key.Code == Key::Num7 || evt.Key.Code == Key::Num8 ||
							evt.Key.Code == Key::Num9)
					{
						aux += evt.Key.Code;					
					}				
				}
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
	bool ret = false;
	if(balas != NULL)
	{
		//balas->GetPos().x > 0 && balas->GetPos().x < wnd_ancho &&
		if(balas->GetPos().y > wnd_alto*-3 && balas->GetPos().y < wnd_alto)
		{
			if(cannon_p2->Hit(balas->GetPos()))
			{
				isPlayer1Lost = false;
				ret = true;
			}
			else if(cannon_p1->Hit(balas->GetPos()))
			{	
				isPlayer1Lost = true;
				ret = true;
			}
			
			if(edificio->Hit(balas->GetPos()))
			{
				snd_load.Play();				
				isTurnoSec = 6;
				delete balas;
				balas = NULL;	
			}

			if(ret)
			{
				snd_load.Play();
				hud->InitFXTime();
				isTurnoSec = 4;				
			}
		}
		else
		{
			ret = true;
			isTurnoSec = 6;
		}

		if(balas != NULL && (balas->GetPos().x < 0 || balas->GetPos().x > wnd_ancho))
			balas->InvPosX(wnd_ancho);
		
		if(ret)
		{	
			delete balas;
			balas = NULL;			
		}
	}
}

void Game::DrawGame()
{
	background->Draw(pWnd);
	
	if(isTurnoSec == 7)
	{	
		if(cannon_p1->GetVidas() == 0)
			hud->ShowGano(pWnd,false);
		if(cannon_p2->GetVidas() == 0)
			hud->ShowGano(pWnd,true);
	}	
	else
	{
		edificio->Draw(pWnd);

		if(isTurnoSec == 4)
		{	
			if(hud->ShowLostVida(pWnd,isPlayer1Lost))
			{
				isTurnoSec = 5;
			}
			else
			{
				if(isPlayer1Lost)
				{
					cannon_p1->Blink(pWnd);
					cannon_p2->Draw(pWnd);
				}
				else
				{
					cannon_p2->Blink(pWnd);
					cannon_p1->Draw(pWnd);
				}
			}
		}
		else
		{
			cannon_p1->Draw(pWnd);
			cannon_p2->Draw(pWnd);
		}

		hud->Draw(pWnd);
		
		if(balas != NULL)
		{
			balas->Draw(pWnd);
		}		
	}

	if(isPause)
		menu->Draw(pWnd);
}

void Game::ProcessInput()
{
	if(!isPause)
	{
		/*int x = in->GetMouseX();
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
		
		}*/
	}
}

void Game::UpdateGame()
{	
	if(!isPause)
	{	
		background->Update(pWnd);	
		edificio->Update(pWnd);
		cannon_p1->Update(pWnd);	
		cannon_p2->Update(pWnd);	
		hud->Update(pWnd);
		hud->SetWind(background->wind_force);						
		
		if(balas != NULL)
		{
			balas->Update(pWnd);
		}

		if(isTurnoSec == 0)
		{
			hud->SetIsAng();
			if(!aux.empty())
			{
				if(isTurnoP1)
				{
					cannon_p1->SetAngulo((float)Helper::ToString(aux));	
					hud->SetStatePlayer1(cannon_p1->GetAngulo(),cannon_p1->GetVelocidad(),cannon_p1->GetVidas());
					cannon_p1->Fire(true);
				}
				else
				{
					cannon_p2->SetAngulo((float)Helper::ToString(aux));
					hud->SetStatePlayer2(cannon_p2->GetAngulo(),cannon_p2->GetVelocidad(),cannon_p2->GetVidas());
					cannon_p2->Fire(false);
				}
			}
			if(isNextTurnSec)
			{
				isNextTurnSec = false;					
				isTurnoSec = 1;	
				aux = "";
			}
		}
		else if(isTurnoSec == 1)
		{	
			hud->SetIsVel();
			if(!aux.empty())
			{
				if(isTurnoP1)
				{
					cannon_p1->SetVelocidad((float)Helper::ToString(aux));
					hud->SetStatePlayer1(cannon_p1->GetAngulo(),cannon_p1->GetVelocidad(),cannon_p1->GetVidas());
					cannon_p1->Fire(true);
				}
				else
				{
					cannon_p2->SetVelocidad((float)Helper::ToString(aux));
					hud->SetStatePlayer2(cannon_p2->GetAngulo(),cannon_p2->GetVelocidad(),cannon_p2->GetVidas());
					cannon_p2->Fire(false);
				}
			}
			if(isNextTurnSec)
			{
				isNextTurnSec = false;
				isTurnoSec = 2;			
				aux = "";
			}
		}
		else if(isTurnoSec == 2)
		{
			hud->SetIsFire();			
			isTurnoSec = 3;							
		}
		else if(isTurnoSec == 3)
		{
			if(balas == NULL)
			{
				bool ret;
				if(isTurnoP1)
				{
					ret = cannon_p1->Fire(true);				
				}
				else
				{
					ret = cannon_p2->Fire(false);
				}

				if(ret)		
				{

					if(isTurnoP1)
					{
						balas =  new Bala(cannon_p1->GetPosCano(),cannon_p1->GetLargoCano(),cannon_p1->GetRad(),
										  cannon_p1->GetVelocidad(),background->wind_force);
					}
					else
					{
						balas =  new Bala(cannon_p2->GetPosCano(),cannon_p2->GetLargoCano(),cannon_p2->GetRad(),
										  cannon_p2->GetVelocidad(),background->wind_force);
					}
					snd_disparo.Play();
				}
			}
		}
		else if(isTurnoSec == 5)
		{
			isTurnoSec = 6;
			RefreshLevel();
		}
		else if(isTurnoSec == 6)
		{			
			isTurnoP1 = !isTurnoP1;
			if(isOnePlayer && !isTurnoP1)
			{
				delay_oneplayermode = 2.0f;
			}
			hud->SetTurno(isTurnoP1);

			hud->SetStatePlayer1(cannon_p1->GetAngulo(),cannon_p1->GetVelocidad(),cannon_p1->GetVidas());
			hud->SetStatePlayer2(cannon_p2->GetAngulo(),cannon_p2->GetVelocidad(),cannon_p2->GetVidas());
			
			
			if(cannon_p1->GetVidas() == 0 || cannon_p2->GetVidas() == 0)		
			{
				isTurnoSec = 7;
			}
			else
			{
				isTurnoSec = 0;		
			}
		}
		else if(isTurnoSec == 7)
		{	
				
		}		

		if(isOnePlayer && !isTurnoP1 && isTurnoSec == 0 && delay_oneplayermode <= 0)
		{
			cannon_p2->SetAngulo(rand()%180);
			cannon_p2->SetVelocidad(rand()%40+30);			
			isTurnoSec = 2;
		}
		else if(delay_oneplayermode > 0)
		{
			delay_oneplayermode -= pWnd->GetFrameTime();
		}
	}
}

void Game::Intro()
{
	IntroGame intro;

	MusicMenu();

	Event evt;

	float maxIntro = 7.0f;

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
	MusicGame();
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
	img.LoadFromFile("..//Imagenes//Salir.png");
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
	if(musica.OpenFromFile("..//Musica//AnOrangePlanet(loop).ogg"))
	{
		isMusicEnable = true;		
		musica.SetLoop(true);
		musica.SetAttenuation(2);
		musica.Play();
	}
	else
	{
		isMusicEnable = false;
	}	
}

void Game::MusicMenu()
{
	if(musica.OpenFromFile("..//Musica//Dark swish.ogg"))
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
	
	while(pWnd->IsOpened() && !salir && !isQuit){	
		
		while (pWnd->GetEvent(evt))
		{	
			if(evt.Type == Event::Closed)
			{	
				isQuit = true;
			}
			if(menu->GetState() == Menu::MENU_STATE::CREDITOS || menu->GetState() == Menu::MENU_STATE::AYUDA)
			{
				if(evt.Type == Event::KeyPressed)
				{
					if(evt.Key.Code == Key::Return)
					{
						menu->SetMenu(Menu::GENERAL);
					}
				}
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

	while(pWnd->IsOpened() && !isQuit){

		while (pWnd->GetEvent(evt))
		{	
			if(evt.Type == Event::Closed)
			{	
				isQuit = true;
			}else
			{
				hud->ProcessEvent(evt);
			}
		}	

		if(in->IsMouseButtonDown(Mouse::Left))
		{
			hud->Hit(in->GetMouseX(),in->GetMouseY());
		}
		else
		{
			hud->Test(in->GetMouseX(),in->GetMouseY());
		}

		pWnd->Clear();
		
			hud->Draw(pWnd);

		pWnd->Display();

		if(hud->GetState() == 4)
			break;
	}

	/*if(pWnd->IsOpened())
	{	
		StopMusic();
		MusicGame();
	}*/
}



