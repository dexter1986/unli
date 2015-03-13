#pragma once
#include "scenebase.h"
#include "EntityManager.h"
#include "Personaje.h"
#include "Cronometro.h"
#include "Disparos.h"
#include "SFML\Graphics.hpp"


class MainScene : public SceneBase
{
private:
	sf::Font font;
	sf::String text;
	Sprite keysHUD;
	Sprite vidasHUD;
	sf::Clock clkPerf;
	
	GameEngine *engine;
	
	Personaje *prince;
	
	EntityManager *entities;	
	ManejadorDisparos *disparos;
	Nivel *nivel;
	Cronometro *cronometro;
	ParticleSystemManager *mg;
	string lastLevelFile;
	
	bool isSlowTime;
	bool isGameWon;
	bool isPause;
	bool isContinue;
	float slowTime;
	float slowTimeCount;
	void GameFinish();
	
	void IntLevel(string fileLevel, RenderWindow *w,bool reload);
	void ShowHUD(RenderWindow &w);
	void ActualizarContador();

public:	
	void AgregarEnemigo(float x, float y,int tipo);
	bool HayColision(float x, float y,sf::Color &color,bool isNPC);
	MainScene(GameEngine *engine);
	virtual ~MainScene(void);
	virtual void Init();
	virtual void ProcessEvent(const sf::Event &e);
	virtual void Update(const float &dt);
	virtual void Render(sf::RenderWindow &w);
	virtual void Cleanup();
};

