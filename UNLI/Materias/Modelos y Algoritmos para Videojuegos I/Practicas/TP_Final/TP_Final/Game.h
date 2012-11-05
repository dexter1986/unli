#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <ctime>
#include"Circulo.h"
#include"Hud.h"
#include"Zone.h"
#include"Letra.h"
	
using namespace sf;
using namespace std;

#ifndef GAME_H
#define GAME_H

class Game
{
private:
	int wnd_ancho,wnd_alto;
	RenderWindow* pWnd;
	Music musica;	
	const Input* in;
	Circulo* circulo;
	Zone* zone;
	Hud* hud;
	
	Letra* letra;

	SoundBuffer  vida_up_bff;	
	SoundBuffer  letra_ok_bff;
	SoundBuffer  letra_fail_bff;
	SoundBuffer level_fail_bff;
	SoundBuffer extra_puntos_bff;

	Sound vida_up;	
	Sound letra_ok;
	Sound letra_fail;
	Sound level_fail;
	Sound extra_puntos;
	
	bool isGame;
	int puntos;
	int extra_pnt;
	int count_letras;
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
	void ShowPuntaje();
	void Init();
public:
	Game(int alto, int ancho, string titulo);
	~Game(void);
	void Go();
};

#endif
