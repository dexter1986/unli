#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <ctime>
#include <iostream>

#include "Background.h"

#include "Cannon.h"
#include "Bala.h"
#include "IntroGame.h"
#include "Menu.h"
#include "Edificio.h"
#include "Hud.h"

using namespace sf;
using namespace std;

#ifndef GAME_H
#define GAME_H

#define MAX_FORCE 40
#define MIN_FORCE 0

class Game
{
private:
	int wnd_ancho,wnd_alto;
	RenderWindow* pWnd;
	Music musica;	
	const Input* in;
	
	Background *background;
	Hud *hud;
	Menu *menu;
	Cannon *cannon_p1;
	Cannon *cannon_p2;
	
	Bala *balas;
	Edificio *edificio;
	
	Event evt;
	bool isTurnoP1;
	int isTurnoSec;
	bool isNextTurnSec;
	string aux;
	bool isPause; 
	bool isShowIntro;
	bool isQuit;
	bool isMenuGeneral;
	bool isPlayer1Lost;
	bool isOnePlayer;
	SoundBuffer snd_disparo_bff;		
	Sound snd_disparo;			

	SoundBuffer snd_loadbff;		
	Sound snd_load;	
	float delay_oneplayermode;
	void ProcessInput();
	bool isGame;	
	bool isMusicEnable;
	void ProcessEvent(Event &evt);
	void DrawGame();
	void UpdateGame();
	void ProcessCollisions();	
	void MusicGame();
	void MusicMenu();
	void MusicGameOver();
	void GameOver();
	void StopMusic();
	void Intro();
	void Creditos();
	void LoadSound();
	void ShowMenu();	
	void Quit();
	void Init();
	void InitLevel();
	void Instance();
	void PrincipalLoop();
	void RefreshLevel();
public:
	Game(int alto, int ancho, string titulo);
	~Game(void);
	void Go();
};

#endif