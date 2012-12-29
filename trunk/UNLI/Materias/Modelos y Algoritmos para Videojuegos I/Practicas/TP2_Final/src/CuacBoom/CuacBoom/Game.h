#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <ctime>

#include "Background.h"
#include "NubesParallax.h"
#include "Cannon.h"
#include "Bala.h"

using namespace sf;
using namespace std;

#ifndef GAME_H
#define GAME_H

#define MAX_BALAS 20

class Game
{
private:
	int wnd_ancho,wnd_alto;
	RenderWindow* pWnd;
	Music musica;	
	const Input* in;

	Background *background;
	NubesParallax *nubes;
	Cannon *cannon;
	int cant_balas;
	Bala *balas[20];

	int force;

	SoundBuffer sonido_bff;		
	Sound sonido;	

	void ProcessInput();
	bool isGame;
	int puntos;	
	int vidas;
	bool isMusicEnable;
	void ProcessEvent(Event &evt);
	void DrawGame();
	void UpdateGame();
	void ProcessCollisions();	
	void MusicGame();
	void MusicMenu();
	void StopMusic();
	void Intro();
	void Creditos();
	void LoadSound();
	void ShowMenu();	
	void Quit();
	void Init();
public:
	Game(int alto, int ancho, string titulo);
	~Game(void);
	void Go();
};

#endif