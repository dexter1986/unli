#include <cstdio>
#include <tchar.h>
#include "TP5.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{	
	GameBase *Juego;	
	Juego = new TP5(800,600,"TP5");	
	Juego->Loop();	
	delete Juego;

	return 0;
}

