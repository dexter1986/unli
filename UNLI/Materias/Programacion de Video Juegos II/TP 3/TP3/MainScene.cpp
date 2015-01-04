#include "MainScene.h"

MainScene::MainScene(GameEngine *engine):engine(engine)
{
	
}

MainScene::~MainScene(void)
{
	delete cronometro;
	delete entities;			
	delete prince;
	delete mg;
}

void MainScene::Init()
{
	//IsDebug(true);
	isGameWon = false;
	isSlowTime = false;
	isPause = false;
	isContinue = false;
	slowTime = 3.0f;
	slowTimeCount = 0;

	font.LoadFromFile("../data/arialbd.ttf");
	text.SetFont(font);
	text.SetColor(Color::White);
	text.SetSize(10);

	keysHUD.SetImage(TextureManager::GetInstance().GetTexture("../data/megaman_iceman_level.png"));
	keysHUD.SetScale(0.7f,0.7f);
	keysHUD.SetBlendMode(sf::Blend::Alpha);
	keysHUD.SetColor(Color::Color(255,255,255,150));
	IntRect recKeys(32,128,64,160);
	
	keysHUD.SetSubRect(recKeys);
	keysHUD.SetCenter(0,0);
		
	vidasHUD.SetImage(TextureManager::GetInstance().GetTexture("../data/personaje.png"));
	vidasHUD.SetScale(0.4f,0.4f);
	vidasHUD.SetBlendMode(sf::Blend::Alpha);
	vidasHUD.SetColor(Color::Color(255,255,255,150));
	IntRect recVidas(145,285,145 + 22,285 + 57);
	
	vidasHUD.SetSubRect(recVidas);
	vidasHUD.SetCenter(0,0);
	
	cronometro = new Cronometro(600,font);	
	cronometro->Init();	

	
	nivel = engine->nivel;	
	
	disparos = engine->disparos;	
	disparos->SetScene(this);
	disparos->SetLevelManager(nivel);	

	
	entities = new EntityManager(engine);
	
	
	prince = new Personaje(engine);	
	prince->Inicializar(disparos,nivel);
	
	entities->SetEnvironment(disparos,nivel);	
	entities->AiTracker(prince);

	IntLevel("../data/level1.lev",engine->wnd,false);
	
	mg = &ParticleSystemManager::GetManager();	
	mg->AddAffector(new Gravity(0,1000));
	mg->AddAffector(new Fade(0.5));
}

bool MainScene::HayColision(float x, float y,sf::Color &color,bool isNPC)
{
	if(!isNPC)
	{
		if(entities->HayColision(x,y,color)){
			return true;
		}
	}
	if(prince->RecibirImpacto(x,y)){
		return true;
	}
	return false;
}

void MainScene::AgregarEnemigo(float x, float y,int tipo)
{
	Enemigo *e = new Enemigo(tipo,engine);		
	entities->Agregar(e);
	e->SetPosition(x,y);
}

void MainScene::GameFinish()
{
	//isGameWon = true;
}

void MainScene::ProcessEvent(const sf::Event &e)
{		
	//// actualizamos el estado del joystick segun los eventos
	if (e.Type == sf::Event::KeyPressed){
		switch(e.Key.Code){			
			case sf::Key::P:		
				if(!isContinue)
				{
					isPause = !isPause; 
					cronometro->Reset();
				}
				break;
			case sf::Key::Return:	
				if(isPause)
				{
					//toReload = true;
				}
				break; 
			case sf::Key::Escape: 
				//isGameFinish = true; 
				isExit = true; 
				break;
			case sf::Key::Q:    						
				isSlowTime = !isSlowTime;						
				if(isSlowTime)
				{
					engine->fpsScale = 0.5f;							
					slowTimeCount = 0;
				}
				else
				{
					engine->fpsScale = 1.0f;
				}
				break;
		}
	}	
}

void MainScene::Update(const float &dt)
{
	//clkPerf.Reset();
	//isGameWon = nivel->isGameWon;
	nivel->PrepareNivel();
	
	nivel->SetViewCenter(prince->GetPosition());	

	prince->Mover_y_Animar(engine->j,dt);	
	
	entities->Mover(engine->j,dt);	
	
	View &v = nivel->GetView();
	disparos->MoverDisparos(dt,v);
	
	mg->Simulate(dt);

	ActualizarContador();
	
	if(isSlowTime)
	{
		slowTimeCount += dt; 
		if(slowTimeCount > slowTime)
		{
			isSlowTime = false;
			engine->fpsScale = 1.0f;
		}
	}

	//cout << "U:" << clkPerf.GetElapsedTime() << "\n";
}

void MainScene::IntLevel(string fileLevel, RenderWindow *w,bool reload)
{
	entities->Init();
	disparos->Init();
	nivel->Load(fileLevel,reload);	
	
	if(!isDebug)
	{
		for(unsigned i=0; i<nivel->levelSize.y; i++){
			for(unsigned j=0; j<nivel->levelSize.x; j++){
				if(nivel->tiles[i][j].iEnemigo != -1)
				{	
					AgregarEnemigo(nivel->tileSize.x * j,nivel->tileSize.y * i,nivel->tiles[i][j].iEnemigo);
				}			
			}
		}
	}
	
	nivel->InitLevelView(800, 600,10,8);
	prince->SetPosition(nivel->vEntryPoint);
	prince->ResetState();
	View &v = nivel->GetView();
	w->SetView(v);
}

void MainScene::ActualizarContador()
{
	cronometro->Update();
	isFinished = ((Cronometro*)cronometro)->isEndTime();
}

void MainScene::ShowHUD(RenderWindow &w)
{
	FloatRect rect = nivel->levelView.GetRect();	
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
	else if(isFinished)
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

void MainScene::Render(sf::RenderWindow &w)
{
//	clkPerf.Reset();	
	nivel->Draw(w);
	/*cout << "N:" << clk.GetElapsedTime();
	clk.Reset();	*/
	prince->Draw(w);
	/*cout << "-P:" << clk.GetElapsedTime();
	clk.Reset();	*/
	entities->Dibujar(w);		
	/*cout << "-E:" << clk.GetElapsedTime();
	clk.Reset();*/
	disparos->DibujarDisparos(w);				
	/*cout << "-D:" << clk.GetElapsedTime();
	clk.Reset();		*/
	mg->Render(w);
	//cout << "-M:" << clk.GetElapsedTime();
	//clk.Reset();		
	nivel->DrawOverLayer(w);	
	/*cout << "-O:" << clk.GetElapsedTime();
	clk.Reset();	*/
	ShowHUD(w);
	//cout << "-H:" << clk.GetElapsedTime() << "\n";
//	cout << "R:" << clkPerf.GetElapsedTime() << "\n";
	if(isDebug)
	{
		nivel->DrawGrid(w);
	}
}

void MainScene::Cleanup()
{
	
}
