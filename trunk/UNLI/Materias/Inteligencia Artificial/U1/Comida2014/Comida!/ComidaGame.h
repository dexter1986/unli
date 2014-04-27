#pragma once
#include "stdafx.h"
#include "Tablero.h"


using namespace sf;

class ComidaGame
{

	int width;
	int height;
	RenderWindow *wnd;
	Tablero * tablero;

public:
	ComidaGame(void);
	void Loop();
	bool ProcessEvents();
	~ComidaGame(void);
};

