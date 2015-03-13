#include "MenuScene.h"
#include "TextureManager.h"

MenuScene::MenuScene(void)
{
	contador = 0;
}

MenuScene::MenuScene(GameEngine *engine)
{
	contador = 0;
}

MenuScene::~MenuScene(void)
{

}

void MenuScene::Init()
{
	spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Menu.png"));
}

void MenuScene::ProcessEvent(const sf::Event &e)
{
	if(e.Type == e.Closed)
	{
		isFinished = true;
	}
	if (e.Type == sf::Event::KeyPressed)
	{
		if(contador == 0)
		{			
			if(e.Key.Code == sf::Key::Space)
			{
				isFinished = true;
			}

			if(e.Key.Code == sf::Key::Escape || e.Key.Code == sf::Key::Return)
			{	
					isExit = true;
			}

			if(e.Key.Code == sf::Key::A)
			{
				spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Elementos.png"));
				contador = 1;
			}
		}
		else
		{		
			if(contador == 1)
			{
				spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/HUD.png"));	
				contador = 2;
			}
			else if(contador == 2)
			{
				spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Mandos.png"));
				contador = 3;
			}
			else if(contador == 3)
			{
				spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Menu.png"));
				contador = 0;
			}			
		}
	}
}

void MenuScene::Update(const float &dt)
{		
	
}

void MenuScene::Render(sf::RenderWindow &w)
{
	w.Draw(spriteIntro);
}

void MenuScene::Cleanup()
{

}
