#pragma once
#include "scenebase.h"
#include "EntityManager.h"
#include "Personaje.h"
#include "Cronometro.h"
#include "Disparos.h"

class MainScene : public SceneBase
{
private:
	sf::Font font;
	sf::String text;
	Sprite keysHUD;
	Sprite vidasHUD;
	
	EntityManager *entities;
	Personaje *prince;
	ManejadorDisparos *disparos;
	Nivel *nivel;
	Cronometro *cronometro;
	ParticleSystemManager *mg;

	bool isGameWon;

	
	void GameFinish();
	
	void IntLevel(string fileLevel, RenderWindow &w,bool reload);
	void ShowHUD(RenderWindow &w);
	void ActualizarContador();

public:	
	void AgregarEnemigo(float x, float y,int tipo);
	bool HayColision(float x, float y,sf::Color &color);
	MainScene(GameEngine *engine);
	virtual ~MainScene(void);
	virtual void Init();
	virtual void ProcessEvent(const sf::Event &e);
	virtual void Update(const float &dt);
	virtual void Render(sf::RenderWindow &w);
	virtual void Cleanup();
};

