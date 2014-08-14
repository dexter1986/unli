#include "JuegoGanadoScene.h"
#include "TextureManager.h"

JuegoGanadoScene::JuegoGanadoScene(void)
{
	contador = 0;
}


JuegoGanadoScene::~JuegoGanadoScene(void)
{

}

void JuegoGanadoScene::Init()
{
	spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/GameWon.png"));	
}

void JuegoGanadoScene::ProcessEvent(const sf::Event &e)
{
	if(e.Type == e.Closed)
	{
		
	}
	if (e.Type == sf::Event::KeyPressed)
	{
		if(e.Key.Code == sf::Key::Escape || e.Key.Code == sf::Key::Return)
		{
			
		}
	}
}

void JuegoGanadoScene::Update(const float &dt)
{		
	contador += dt;		
	if(dt > 6)
	{
		isFinished = true;
	}			
}

void JuegoGanadoScene::Render(sf::RenderWindow &w)
{
	w.Draw(spriteIntro);
}

void JuegoGanadoScene::Cleanup()
{

}
