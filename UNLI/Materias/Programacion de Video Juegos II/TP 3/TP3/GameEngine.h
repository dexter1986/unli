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
#include "SceneBase.h"

using namespace std;
using namespace sf;

class SceneBase;

// una estructura simple para pasarle los controles a megaman
struct Joystick{
	bool up, down, left, right, a, b;
};


class GameEngine
{
private:
	RenderWindow *wnd;
	View m_currentView;
	std::deque<SceneBase *> m_sceneQueue;
	SceneBase *m_currentScene;
	SceneBase *m_sceneToDelete;	
	bool exitEngine;
	bool isPause;
	float fpsScale;
	Joystick j;
	sf::Clock clk;
	
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
	
	GameEngine(int ancho,int alto,std::string titulo,int fps);
	~GameEngine(void);
	void Loop();	
	void PushScene(SceneBase *scene);			
};

