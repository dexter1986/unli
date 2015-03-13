#pragma once
#include "scenebase.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class JuegoPerdidoScene : public SceneBase
{
private:
	float contador;
	sf::Sprite spriteIntro;
	sf::Clock clk;
public:
	JuegoPerdidoScene(GameEngine *engine);
	JuegoPerdidoScene(void);
	virtual ~JuegoPerdidoScene(void);
	virtual void Init();
	virtual void ProcessEvent(const sf::Event &e);
	virtual void Update(const float &dt);
	virtual void Render(sf::RenderWindow &w);
	virtual void Cleanup();	
};

