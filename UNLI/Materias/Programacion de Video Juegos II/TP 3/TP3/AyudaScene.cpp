#include "AyudaScene.h"
#include "TextureManager.h"

AyudaScene::AyudaScene(void)
{
	contador = 0;
}


AyudaScene::~AyudaScene(void)
{
	contador = 0;
}

void AyudaScene::Init()
{
	spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Intro1.png"));	
}

void AyudaScene::ProcessEvent(const sf::Event &e)
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

void AyudaScene::Update(const float &dt)
{	
	contador += dt;	
	if(contador > 3 && contador < 4)
	{
		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Intro2.png"));		
	}
	else if(contador > 6 && contador < 7)
	{	
		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/HUD.png"));				
	}
	else if(contador > 11 && contador < 12)
	{
		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Mandos.png"));				
	}
	else if(contador > 16 && contador < 17)
	{
		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Elementos.png"));					
	}
	else if(contador > 21 && contador < 22 )
	{
		spriteIntro.SetImage(TextureManager::GetInstance().GetTexture("../data/Mision.png"));				
	}
	else if(contador > 22)
	{
		isFinished = true;
	}
}

void AyudaScene::Render(sf::RenderWindow &w)
{
	w.Draw(spriteIntro);
}

void AyudaScene::Cleanup()
{

}
