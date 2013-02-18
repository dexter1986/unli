#include "IntroGame.h"

IntroGame::IntroGame():GameObject(false,"..//Imagenes//Intro.png")
{
	Enable(true);
	alpha = 0;
	sprite.SetColor(sf::Color(255, 255, 255, alpha));
}

void IntroGame::NextFrame()
{
	currentframe++;	
}

void IntroGame::Draw(RenderWindow *app)
{
	if (alpha < 230)
	{
		sprite.SetColor(sf::Color(255, 255, 255, alpha += 1));
	}
	else
	{
		sprite.SetColor(sf::Color(255, 255, 255, 230));
	}
	GameObject::Draw(app);
}

bool IntroGame::isNextFrame()
{
	if(currentframe < maxframes)
	{
		UpdateFrame();
		alpha = 0;
		sprite.SetColor(sf::Color(255, 255, 255, alpha));
		return true;
	}
	return false;
}
