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
	
	Menu *menu;
	Cannon *cannon;
	
	Bala *balas;

	int force;
	
	float windNextTime;
	float windTime;
	Event evt;

	bool isPause; 
	bool isShowIntro;

	SoundBuffer snd_disparo_bff;		
	Sound snd_disparo;	

	SoundBuffer snd_pato_hit_bff;		
	Sound snd_pato_hit;	

	SoundBuffer snd_loadbff;		
	Sound snd_load;	
	
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
	void Instance();
	void PrincipalLoop();
public:
	Game(int alto, int ancho, string titulo);
	~Game(void);
	void Go();
};

#endif