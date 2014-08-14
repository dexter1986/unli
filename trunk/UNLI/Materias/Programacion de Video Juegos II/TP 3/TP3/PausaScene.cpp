#include "PausaScene.h"
#include "TextureManager.h"

PausaScene::PausaScene(void)
{
	contador = 0;
}


PausaScene::~PausaScene(void)
{

}

void PausaScene::Init()
{
	spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Intro1.png"));	
}

void PausaScene::ProcessEvent(const sf::Event &e)
{
	if(e.Type == e.Closed)
	{
		isFinished = true;
	}
	if (e.Type == sf::Event::KeyPressed)
	{
		if(e.Key.Code == sf::Key::Escape || e.Key.Code == sf::Key::Return)
		{
			isFinished = true;
		}
	}
}

void PausaScene::Update(const float &dt)
{	
}

void PausaScene::Render(sf::RenderWindow &w)
{
	w.Draw(spriteIntro);
}

void PausaScene::Cleanup()
{
	isFinished = true;
}
