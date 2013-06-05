#include <cstdio>
#include <tchar.h>
#include "TP3.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{	
	GameBase *Juego;	
	Juego = new TP3(800,600,"TP3");	
	Juego->Loop();	
	delete Juego;

	return 0;
}

