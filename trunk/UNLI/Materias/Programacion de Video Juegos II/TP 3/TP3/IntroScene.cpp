#include "IntroScene.h"
#include "TextureManager.h"

IntroScene::IntroScene(void)
{
	contador = 0;
	isIntro = false;
}

IntroScene::~IntroScene(void)
{

}

void IntroScene::Init()
{
	spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Intro1.png"));	
}

void IntroScene::ProcessEvent(const sf::Event &e)
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

void IntroScene::Update(const float &dt)
{	
	contador += dt;	
	if(contador > 3 && !isIntro)
	{
		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Intro2.png"));	
		isIntro = true;
	}	
	else if(contador > 6)
	{
		isFinished = true;
	}
}

void IntroScene::Render(sf::RenderWindow &w)
{
	w.Draw(spriteIntro);
}

void IntroScene::Cleanup()
{

}
