#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System/Clock.hpp>
#include<Box2D\Box2D.h>

#include<cstdio>
#include <tchar.h>
#include "SFMLRenderer.h"
#include "TP2.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{	
	GameBase *Juego;	
	Juego = new TP2(800,600,"U3 EJ 3");	
	Juego->Loop();	
	delete Juego;

	return 0;
}

