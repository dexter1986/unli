#include <cstdio>
#include <tchar.h>
#include "TP4.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{	
	GameBase *Juego;	
	Juego = new TP4(800,600,"TP4");	
	Juego->Loop();	
	delete Juego;

	return 0;
}

