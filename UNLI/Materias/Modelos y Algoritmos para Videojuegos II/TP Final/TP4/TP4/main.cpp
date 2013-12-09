#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System/Clock.hpp>
#include<Box2D\Box2D.h>

#include<cstdio>
#include <tchar.h>
#include "SFMLRenderer.h"
#include "TP4.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{	
	GameBase *Juego;	
	Juego = new TP4(800,600,"TP Final");	
	Juego->Loop();	
	delete Juego;

	return 0;
}

