#include "MisionScene.h"
#include "TextureManager.h"

MisionScene::MisionScene(void)
{
	contador = 0;
}


MisionScene::~MisionScene(void)
{

}

void MisionScene::Init()
{
	spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Mision.png"));	
}

void MisionScene::ProcessEvent(const sf::Event &e)
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

void MisionScene::Update(const float &dt)
{		
}

void MisionScene::Render(sf::RenderWindow &w)
{
	w.Draw(spriteIntro);
}

void MisionScene::Cleanup()
{
}
