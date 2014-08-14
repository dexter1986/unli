#include "MainScene.h"

MainScene::MainScene(GameEngine *engine)
{

}

MainScene::~MainScene(void)
{
}

void MainScene::Init()
{
	isGameWon = false;
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
	
	entities = new EntityManager();
	
	nivel = new Nivel(this);	
	
	disparos = new ManejadorDisparos(this);		
	disparos->SetLevelManager(nivel);
	
	prince = new Personaje();
	prince->Inicializar(disparos,nivel);

	entities->SetEnvironment(disparos,nivel);	
	entities->AiTracker(prince);
}

bool MainScene::HayColision(float x, float y,sf::Color &color)
{
	if(entities->HayColision(x,y,color)){
		return true;
	}

	if(prince->RecibirImpacto(x,y)){
		return true;
	}
	return false;
}

void MainScene::AgregarEnemigo(float x, float y,int tipo)
{
	Enemigo *e = new Enemigo(tipo);		
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
	//if (e.Type == sf::Event::KeyPressed){
	//	switch(e.Key.Code){
	//		case sf::Key::Up:		j.up=true; break; 
	//		case sf::Key::Down: 	j.down=true; break; 
	//		case sf::Key::Left: 	j.left=true; break; 
	//		case sf::Key::Right: 	j.right=true; break; 
	//		case sf::Key::A: 		j.a=true; break; 
	//		case sf::Key::S: 		j.b=true; break;
	//		case sf::Key::P:		
	//			if(!isContinue)
	//			{
	//				isPause = !isPause; 
	//				cronometro->Reset();
	//			}
	//			break;
	//		case sf::Key::Return:	
	//			if(isPause)
	//			{
	//				toReload = true;
	//			}
	//			break; 
	//		case sf::Key::Escape: 
	//			isGameFinish = true; 
	//			isExit = true; 
	//			break;
	//		case sf::Key::Q:    						
	//			isSlowTime = !isSlowTime;						
	//			if(isSlowTime)
	//			{
	//				fpsScale = 0.5f;							
	//				slowTimeCount = 0;
	//			}
	//			else
	//			{
	//				fpsScale = 1.0f;
	//			}
	//			break;
	//	}
	//}
			
	/*if (e.Type == sf::Event::KeyReleased){
		switch(e.Key.Code){
			case sf::Key::Up:		j.up=false; break; 
			case sf::Key::Down: 	j.down=false; break; 
			case sf::Key::Left: 	j.left=false; break; 
			case sf::Key::Right: 	j.right=false; break; 
			case sf::Key::A: 		j.a=false; break; 
			case sf::Key::S: 		j.b=false; break;
		}
	}	*/
}

void MainScene::Update(const float &dt)
{
	isGameWon = nivel->isGameWon;
}

void MainScene::IntLevel(string fileLevel, RenderWindow &w,bool reload)
{
	entities->Init();
	disparos->Init();
	nivel->Load(fileLevel,reload);
	prince->SetPosition(nivel->vEntryPoint);
	//nivel->InitLevelView(resx, resy,10,8);
	View &v = nivel->GetView();
	w.SetView(v);
}

void MainScene::ActualizarContador()
{

	/*cronometro->Update();
	isGameFinish = ((Cronometro*)cronometro)->isEndTime();*/
}

void MainScene::ShowHUD(RenderWindow &w)
{
	//FloatRect rect = nivel->levelView.GetRect();	
	//Vector2f center;
	//center.y = rect.Top + rect.GetHeight() / 2;
	//center.x = rect.Left + rect.GetWidth() /2;
	//
	//cronometro->SetPosition(rect.Right - 50.0f,rect.Top + 5);
	//w.Draw(cronometro->DrawObject());
	//
	//for(int i = 0;i<prince->vidas;i++)
	//{
	//	vidasHUD.SetPosition(rect.Left + 5 + i * 10 ,rect.Top + 5);		
	//	w.Draw(vidasHUD);
	//}
	//
	//for(int i = 0;i<5;i++)
	//{
	//	if(nivel->irKeys[i] == 0)
	//	{
	//		keysHUD.SetColor(Color::Color(255,255,255,150));
	//	}
	//	else
	//	{
	//		keysHUD.SetColor(Color::Color(255,255,255,255));
	//	}

	//	keysHUD.SetPosition(rect.Left + 135 + i * 15 ,rect.Top + 5);
	//	w.Draw(keysHUD);
	//}

	//text.SetText(nivel->name);
	//text.SetPosition(center.x - 10,rect.Top);
	//text.SetColor(Color::Color(255,255,255,250));
	//w.Draw(text);

	//if(isSlowTime)
	//{
	//	text.SetText("Slow Time");
	//	text.SetPosition(center.x  ,rect.Top + 30);
	//	text.SetColor(Color::Color(255,255,255,210));
	//	w.Draw(text);
	//}
	//
	//if(isGameWon)
	//{
	//	text.SetText("El jugador gana el juego");
	//	text.SetPosition(center.x - 40 ,center.y - 30);
	//	text.SetColor(Color::Color(255,255,255,255));
	//	w.Draw(text);
	//}
	//else if(isGameFinish)
	//{
	//	if(prince->vidas == 0)
	//	{
	//		text.SetText("Ya no hay mas vidas");
	//	}
	//	else
	//	{
	//		text.SetText("El tiempo ha finalizado");
	//	}
	//	text.SetPosition(center.x - 40,center.y - 30);
	//	text.SetColor(Color::Color(255,255,255,255));
	//	w.Draw(text);
	//}
	//else if(isContinue)
	//{
	//	text.SetText("Presione Enter");		
	//	text.SetPosition(center.x - 40 ,center.y - 30);
	//	text.SetColor(Color::Color(255,255,255,255));
	//	w.Draw(text);

	//	text.SetText("para continuar");
	//	text.SetPosition(center.x - 40 ,center.y - 20);
	//	text.SetColor(Color::Color(255,255,255,255));
	//	w.Draw(text);
	//}
	//else if(isPause)
	//{
	//	text.SetText("Pausa");
	//	text.SetPosition(center.x,center.y - 30);
	//	text.SetColor(Color::Color(255,255,255,255));
	//	w.Draw(text);
	//}
}

void MainScene::Render(sf::RenderWindow &w)
{

}

void MainScene::Cleanup()
{
	delete cronometro;
	delete entities;
	delete disparos;
	delete nivel;	
	delete prince;
	delete mg;
}
