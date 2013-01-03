#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <ctime>

#include "Background.h"
#include "NubesParallax.h"
#include "Cannon.h"
#include "Bala.h"
#include "EnergyLevel.h"
#include "WindBlow.h"
#include "Pato.h"

using namespace sf;
using namespace std;

#ifndef GAME_H
#define GAME_H

#define MAX_BALAS 20
#define MAX_FORCE 40
#define MIN_FORCE 0
#define MAX_VIDAS 3
#define MAX_PATOS 20

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
	EnergyLevel *energyLevel;
	WindBlow *wind;

	int cant_balas;
	Bala *balas[20];

	int cant_patos;
	float patosNextTime;
	float patosTime;
	Pato *patos[20];

	int force;
	
	float windNextTime;
	float windTime;
	
	SoundBuffer sonido_bff;		
	Sound sonido;	
	void CrearPatos(Pato *pato);
	void CrearPato(float angulo,float force);
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