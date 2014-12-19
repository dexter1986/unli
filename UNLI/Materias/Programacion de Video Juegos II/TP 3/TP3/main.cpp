#include "GameEngine.h"
#include "MainScene.h"
#include "IntroScene.h"
#include "MenuScene.h"
#include "MisionScene.h"
/*
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SpriteSheetManager.h"
#include "Animation.h"

#include "Nivel.h"
#include "Personaje.h"
#include "Enemigo.h"
#include "Disparos.h"

#include "ParticleSystemManager.h"
#include "EntityManager.h"
#include "Cronometro.h"

#include "GameEngine.h"
*/
using namespace std;

int const resx=800, resy=600;

/*
void IntLevel(string fileLevel,RenderWindow &w,bool reload = false);
bool HayColisionEntityManager(float x, float y,sf::Color &color); 
//void AgregarEnemigo(float x, float y,int tipo);
void GameFinish();
void ShowHUD(RenderWindow &w);
void ActualizarContador();
void LoadVidasHUD();
void LoadKeysHUD();
void EndGame(RenderWindow &w);
void PreLoadUnits();
void InitUnits();
void ShowIntroduction(RenderWindow &w);
void ManageEvents(RenderWindow &w);

//EntityManager *entities;
//Personaje *prince;
//ManejadorDisparos *disparos;
//Nivel *nivel;
//Cronometro *cronometro;
//ParticleSystemManager *mg;

//sf::String text;
//Sprite vidasHUD;
//Sprite keysHUD;
Sprite spriteIntro;
sf::Clock clk;
sf::Event e;
View *v;
//sf::Font font;
Joystick j;

bool isDebugMode = true;
bool isGameFinish = false;
bool isGameWon = false;
bool isPause = false;
bool isContinue = false;
bool toReload = false;
bool isExit = false;
bool isSlowTime = false;
bool isSkipeFrame = false;
float slowTime = 3.0f;
float slowTimeCount = 0;
float FPS = 60.0f;
float fpsScale = 1.0f;
float fpsUnit = 1.0f/FPS;//run to 30fps
float minFpsUnit = 1.0f/30.0f;//min run to 10fps
*/

int main(int argc, char *argv[]) 
{
	GameEngine *engine = new GameEngine(resx,resy,"Extreme Mission",30);
//	engine->PushScene(new IntroScene(engine));	
//	engine->PushScene(new MenuScene(engine));
//	engine->PushScene(new MisionScene(engine));
	engine->PushScene(new MainScene(engine));
	engine->Loop();
	delete engine;

	return 0;
}


//int main1(int argc, char *argv[]) {
//
//	//PreLoadUnits();
//	
//	//// creamos la ventana y definimos la porcion visible del plano
//	//sf::RenderWindow w(VideoMode(resx,resy),"TP3",sf::Style::None);	
//	//
//	//w.SetFramerateLimit(FPS);
//	//
//	//srand((unsigned int)time(NULL));
//
//	// creamos e inicializamos nuestra estructura joystick	
//	//j.up=j.down=j.left=j.right=j.a=j.b=0;
//	
//	//InitUnits();
//	
//	//nivel->isDebug = true; //No carga los enemigos
//	
//	IntLevel("../data/level1.lev",w);
//
//	v = &w.GetDefaultView();	
//	mg = &ParticleSystemManager::GetManager();
//
//	Affector *g=new Gravity(0,1000);
//	Affector *f1=new Fade(0.5);
//	mg->AddAffector(g);
//	mg->AddAffector(f1);
//	
//	prince->Mover_y_Animar(j,fpsUnit);
//	entities->Mover(j,fpsUnit);
//
//	isPause = true;
//	isContinue = true;
//
//	if(!isDebugMode)
//	{
//		ShowIntroduction(w);
//	}
//
//	cronometro = new Cronometro(600,font);	
//	cronometro->Init();	
//
//	float dt = 0.0f;// fpsUnit;
//	float dt0 = 0.0f;
//	float dt1 = 0.0f;
//	//Main Loop	
//	while(w.IsOpened()) {	
//		//->aca
//		
//
//		//ManageEvents(w);
//
//	/*if(!isSkipeFrame)
//	{*/
//		nivel->PrepareNivel();
//		dt1 = clk.GetElapsedTime();
//		if(!isPause)
//		{
//			if(isSlowTime)
//			{
//				slowTimeCount += dt; 
//				if(slowTimeCount > slowTime)
//				{
//					isSlowTime = false;
//					fpsScale = 1.0f;
//				}
//			}
//
//			ActualizarContador();
//						
//			dt = (dt1 - dt0) * fpsScale;
//
//			nivel->SetViewCenter(prince->GetPosition());
//			prince->Mover_y_Animar(j,dt);	
//			disparos->MoverDisparos(dt, *v);	
//			entities->Mover(j,dt);	
//			
//			//<-
//			if(prince->isDead)
//			{
//				if(prince->vidas <= 0)
//				{
//					isGameFinish = true;
//				}
//				else
//				{
//					isContinue = true;
//					isPause = true;	
//					prince->pause = true;					
//				}
//			}
//			else
//			{
//				if(nivel->isNeedNextLoadLevel)
//				{	
//					prince->pause = true;
//					prince->SetPosition(0,0);
//					prince->ResetState();
//					j.left = false;
//					j.right = false;
//					j.down = false;
//					j.up = false;				
//					string file = nivel->fileNextLevel;		
//					disparos->Init();
//					mg->Clear();
//					IntLevel(file,w,true);	
//					prince->Mover_y_Animar(j,fpsUnit);
//					nivel->isNeedNextLoadLevel = false;
//					prince->pause = false;	
//					cronometro->Reset();
//					clk.Reset();			
//					dt0 = 0;
//					dt1 = 0;
//				}
//			}			
//		}
//		else
//		{
//			disparos->MoverDisparos(dt, *v);	
//			nivel->SetViewCenter(prince->GetPosition());
//			clk.Reset();
//			dt0 = 0;
//			dt1 = 0;
//		}
//		
//		dt0 = clk.GetElapsedTime();
//
//		if(toReload)
//		{
//			toReload = false;
//			isContinue = false;
//			isPause = false;
//			prince->SetPosition(nivel->vEntryPoint);
//			prince->ResetState();
//			prince->isDead = false;
//			prince->pause = false;			
//			nivel->SetViewCenter(prince->GetPosition());
//			disparos->Init();
//			mg->Clear();
//			cronometro->Reset();
//			clk.Reset();
//			clk.Reset();
//			dt0 = 0;
//			dt1 = 0;		
//		}	
//
//		if(isGameWon || isGameFinish || isExit) 
//		{
//			break;
//		}
//		
//		//nivel->SetViewCenter(prince->GetPosition());
//		mg->Simulate(dt);
//		w.Clear(Color(0,0,0));		
//		
//		nivel->Draw(w);
//		prince->Draw(w);
//		entities->Dibujar(w);		
//		disparos->DibujarDisparos(w);				
//		nivel->DrawOverLayer(w);
//		mg->Render(w);
//		ShowHUD(w);
//
//		w.Display();			
//    }
//
//	/*if(!isDebugMode)
//	{
//	   EndGame(w);
//	}*/
//
//	/*delete cronometro;
//	delete entities;
//	delete disparos;
//	delete nivel;	
//	delete prince;
//	delete mg;*/
//
//	w.Close();
//
//	return 0;
//}

/*
void ManageEvents(RenderWindow &w)
{
	//while(w.GetEvent(e)) {
	//		if(e.Type == e.Closed)
	//			w.Close();
	//		
	//		// actualizamos el estado del joystick segun los eventos
	//		if (e.Type == sf::Event::KeyPressed){
	//			switch(e.Key.Code){
	//				case sf::Key::Up:		j.up=true; break; 
	//				case sf::Key::Down: 	j.down=true; break; 
	//				case sf::Key::Left: 	j.left=true; break; 
	//				case sf::Key::Right: 	j.right=true; break; 
	//				case sf::Key::A: 		j.a=true; break; 
	//				case sf::Key::S: 		j.b=true; break;
	//				case sf::Key::P:		
	//					if(!isContinue)
	//					{
	//						isPause = !isPause; 
	//						cronometro->Reset();
	//					}
	//					break;
	//				case sf::Key::Return:	
	//					if(isPause)
	//					{
	//						toReload = true;
	//					}
	//					break; 
	//				case sf::Key::Escape: 
	//					isGameFinish = true; 
	//					isExit = true; 
	//					break;
	//				case sf::Key::Q:    						
	//					isSlowTime = !isSlowTime;						
	//					if(isSlowTime)
	//					{
	//						fpsScale = 0.5f;							
	//						slowTimeCount = 0;
	//					}
	//					else
	//					{
	//						fpsScale = 1.0f;
	//					}
	//					break;
	//			}
	//		}
	//		
	//		if (e.Type == sf::Event::KeyReleased){
	//			switch(e.Key.Code){
	//				case sf::Key::Up:		j.up=false; break; 
	//				case sf::Key::Down: 	j.down=false; break; 
	//				case sf::Key::Left: 	j.left=false; break; 
	//				case sf::Key::Right: 	j.right=false; break; 
	//				case sf::Key::A: 		j.a=false; break; 
	//				case sf::Key::S: 		j.b=false; break;
	//			}
	//		}			
	//	}	
}
*/
/*
void ShowIntroduction(RenderWindow &w)
{
	//int contador = 0;
	//clk.Reset();
	//while(w.IsOpened()) {		
	//	while(w.GetEvent(e)) {
	//		if(e.Type == e.Closed)
	//			w.Close();
	//		if (e.Type == sf::Event::KeyPressed){
	//			if(e.Key.Code == sf::Key::Escape)
	//			{
	//				contador = 1;
	//			}
	//			if(contador > 0)
	//			{
	//				switch(e.Key.Code){					
	//					case sf::Key::Return:	
	//						contador = 2;
	//					break; 
	//				}
	//			}
	//		}
	//	}

	//	if(contador == 2)
	//	{
	//		break;
	//	}
	//	else
	//	{
	////		Intro(contador);
	//	}
	//		
	//	// dibujamos
	//	w.Clear(Color(0,0,0));	
	//	w.Draw(spriteIntro);
	//	w.Display();
	//}
}
*/

/*
void PreLoadUnits()
{
	TextureManager::GetInstance().GetTexture("../data/Intro1.png");
	TextureManager::GetInstance().GetTexture("../data/Intro2.png");
	TextureManager::GetInstance().GetTexture("../data/HUD.png");
	TextureManager::GetInstance().GetTexture("../data/Mandos.png");
	TextureManager::GetInstance().GetTexture("../data/Elementos.png");
	TextureManager::GetInstance().GetTexture("../data/Mision.png");
	
	spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Intro1.png"));
	//spriteIntro.SetScale(0.4f,0.4f);

	LoadVidasHUD();
	LoadKeysHUD();	
		
	font.LoadFromFile("../data/arialbd.ttf");
	text.SetFont(font);
	text.SetColor(Color::White);
	text.SetSize(10);
}
*/

/*
void InitUnits()
{
	//entities = new EntityManager();
	//
	//nivel = new Nivel();	
	//nivel->SetEnemigoManagerDelegate(AgregarEnemigo);
	//nivel->SetGameWonDelegate(GameFinish);
	//
	//disparos = new ManejadorDisparos();		
	//disparos->SetLevelManager(nivel);
	//disparos->SetEnemigoManagerDelegate(HayColisionEntityManager);

	//prince = new Personaje();
	//prince->Inicializar(disparos,nivel);
	////prince->pause = true;

	//entities->SetEnvironment(disparos,nivel);	
	//entities->AiTracker(prince);
}
*/
/*
void EndGame(RenderWindow &w)
{
}
*/
//bool Intro(int &contador)
//{
//	float dt = clk.GetElapsedTime();
//	if(contador == 1)
//	{
//		if(dt < 21.0f)
//		{
//			dt = 21.5f;
//		}
//	}	
//	if(dt > 3 && dt < 4)
//	{
//		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Intro2.png"));
//		spriteIntro.SetScale(0.4f,0.4f);
//	}
//	else if(dt > 6 && dt < 7)
//	{	
//		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/HUD.png"));
//		spriteIntro.SetScale(0.4f,0.4f);
//	}
//	else if(dt > 11 && dt < 12)
//	{
//		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Mandos.png"));
//		spriteIntro.SetScale(0.4f,0.4f);
//	}
//	else if(dt > 16 && dt < 17)
//	{
//		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Elementos.png"));	
//		spriteIntro.SetScale(0.4f,0.4f);
//	}
//	else if(dt > 21 && dt < 22 )
//	{
//		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Mision.png"));
//		spriteIntro.SetScale(0.4f,0.4f);
//		contador = 1;
//		return false;
//	}	
//	return true;
//}
/*
void LoadKeysHUD()
{
	const sf::Image &tex = TextureManager::GetInstance().GetTexture("../data/megaman_iceman_level.png");	
	
	keysHUD.SetImage(tex);
	keysHUD.SetScale(0.7f,0.7f);
	keysHUD.SetBlendMode(sf::Blend::Alpha);
	keysHUD.SetColor(Color::Color(255,255,255,150));
	IntRect recKeys(32,128,64,160);
	
	keysHUD.SetSubRect(recKeys);
	keysHUD.SetCenter(0,0);
}
*/
/*
void LoadVidasHUD()
{
	const sf::Image &tex = TextureManager::GetInstance().GetTexture("../data/personaje.png");	
	
	vidasHUD.SetImage(tex);
	vidasHUD.SetScale(0.4f,0.4f);
	vidasHUD.SetBlendMode(sf::Blend::Alpha);
	vidasHUD.SetColor(Color::Color(255,255,255,150));
	IntRect recVidas(145,285,145 + 22,285 + 57);
	
	vidasHUD.SetSubRect(recVidas);
	vidasHUD.SetCenter(0,0);
}
*/
/*
void GameFinish()
{
	isGameWon = true;
}
*/

/*
void ActualizarContador()
{
	cronometro->Update();
	isGameFinish = ((Cronometro*)cronometro)->isEndTime();
}
*/

/*
void ShowHUD(RenderWindow &w)
{	
	/*FloatRect rect = nivel->levelView.GetRect();	
	Vector2f center;
	center.y = rect.Top + rect.GetHeight() / 2;
	center.x = rect.Left + rect.GetWidth() /2;
	
	cronometro->SetPosition(rect.Right - 50.0f,rect.Top + 5);
	w.Draw(cronometro->DrawObject());
	
	for(int i = 0;i<prince->vidas;i++)
	{
		vidasHUD.SetPosition(rect.Left + 5 + i * 10 ,rect.Top + 5);		
		w.Draw(vidasHUD);
	}
	
	for(int i = 0;i<5;i++)
	{
		if(nivel->irKeys[i] == 0)
		{
			keysHUD.SetColor(Color::Color(255,255,255,150));
		}
		else
		{
			keysHUD.SetColor(Color::Color(255,255,255,255));
		}

		keysHUD.SetPosition(rect.Left + 135 + i * 15 ,rect.Top + 5);
		w.Draw(keysHUD);
	}

	text.SetText(nivel->name);
	text.SetPosition(center.x - 10,rect.Top);
	text.SetColor(Color::Color(255,255,255,250));
	w.Draw(text);

	if(isSlowTime)
	{
		text.SetText("Slow Time");
		text.SetPosition(center.x  ,rect.Top + 30);
		text.SetColor(Color::Color(255,255,255,210));
		w.Draw(text);
	}
	
	if(isGameWon)
	{
		text.SetText("El jugador gana el juego");
		text.SetPosition(center.x - 40 ,center.y - 30);
		text.SetColor(Color::Color(255,255,255,255));
		w.Draw(text);
	}
	else if(isGameFinish)
	{
		if(prince->vidas == 0)
		{
			text.SetText("Ya no hay mas vidas");
		}
		else
		{
			text.SetText("El tiempo ha finalizado");
		}
		text.SetPosition(center.x - 40,center.y - 30);
		text.SetColor(Color::Color(255,255,255,255));
		w.Draw(text);
	}
	else if(isContinue)
	{
		text.SetText("Presione Enter");		
		text.SetPosition(center.x - 40 ,center.y - 30);
		text.SetColor(Color::Color(255,255,255,255));
		w.Draw(text);

		text.SetText("para continuar");
		text.SetPosition(center.x - 40 ,center.y - 20);
		text.SetColor(Color::Color(255,255,255,255));
		w.Draw(text);
	}
	else if(isPause)
	{
		text.SetText("Pausa");
		text.SetPosition(center.x,center.y - 30);
		text.SetColor(Color::Color(255,255,255,255));
		w.Draw(text);
	}
}
*/

/*
void IntLevel(string fileLevel, RenderWindow &w,bool reload)
{
	entities->Init();
	disparos->Init();
	nivel->Load(fileLevel,reload);
	prince->SetPosition(nivel->vEntryPoint);
	nivel->InitLevelView(resx, resy,10,8);
	View &v = nivel->GetView();
	w.SetView(v);
}
*/

/*
bool HayColisionEntityManager(float x, float y,sf::Color &color)
{
	if(entities->HayColision(x,y,color)){
		return true;
	}

	if(prince->RecibirImpacto(x,y)){
		return true;
	}
	return false;
}
*/
//void AgregarEnemigo(float x, float y,int tipo)
//{
//	/*Enemigo *e = new Enemigo(tipo);		
//	entities->Agregar(e);
//	e->SetPosition(x,y);*/
//}

