#pragma once
#include "scenebase.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class JuegoGanadoScene : public SceneBase
{
private:
	float contador;
	sf::Sprite spriteIntro;
	sf::Clock clk;
public:
	JuegoGanadoScene(GameEngine *engine);
	JuegoGanadoScene(void);
	virtual ~JuegoGanadoScene(void);
	virtual void Init();
	virtual void ProcessEvent(const sf::Event &e);
	virtual void Update(const float &dt);
	virtual void Render(sf::RenderWindow &w);
	virtual void Cleanup();	
};

