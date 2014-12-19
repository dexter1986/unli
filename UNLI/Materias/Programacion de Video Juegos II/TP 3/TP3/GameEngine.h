#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdio.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <climits> 
#include <deque>
#include "SpriteSheetManager.h"
#include "Animation.h"
#include "ParticleSystemManager.h"
#include "Disparos.h"
#include "Nivel.h"
#include "Cronometro.h"
#include "Joystick.h"

using namespace std;
using namespace sf;

class SceneBase;
class ManejadorDisparos;
class Nivel;



class GameEngine
{
private:
	View m_currentView;
	std::deque<SceneBase *> m_sceneQueue;
	SceneBase *m_currentScene;
	SceneBase *m_sceneToDelete;	
	bool exitEngine;
	bool isPause;	
	float fps_dt;
	
	sf::Clock clk;
	sf::Clock clkPerf;

	void DrawGame();
	void UpdatePoolEvents(const Event &evt); 
	void UpdateEvents(const float &dt);
	void DoEvents();

	/*void CheckCollitions();
	void InitPhysics();	
	void UpdatePhysics();		
	void UpdateState();*/

	void JoystickUpdate(const Event &evt);
	void Init();

public:
	Joystick j;
	float fpsScale;
	RenderWindow *wnd;
	ManejadorDisparos *disparos;
	Nivel *nivel;
	Cronometro *cronometro;
	ParticleSystemManager *mg;

	bool HayColision(sf::FloatRect &r, sf::FloatRect &areaColision,int &tipo,bool isNPC);
	FloatRect GetLevelViewRect();
	GameEngine(int ancho,int alto,std::string titulo,int fps);
	~GameEngine(void);
	void Loop();	
	void PushScene(SceneBase *scene);			
};

