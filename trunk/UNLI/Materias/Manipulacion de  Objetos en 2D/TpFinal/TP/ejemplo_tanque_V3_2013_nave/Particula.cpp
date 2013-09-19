#include <cstdlib>
#include <cmath>
#include "Particula.h"

void Particula::Inicializar(float pX, float pY, float Velocidad, float r, float g, float b, int amplitud, int direccion, int vida)
{
	x = pX; y = pY; 
	
	float ang, seno, coseno;
	int ang_bottom, ang_top;
	ang_top = direccion + (amplitud/2.0); ang_bottom = direccion - (amplitud/2.0);
	ang = rand() % (ang_top+1-ang_bottom) + ang_bottom;
	ang = ang * 3.14 / 180.0;
	seno = sin(ang);
	coseno = cos(ang);
	vX = seno * Velocidad;
	vY = coseno * Velocidad;		
	
	blue = r; red = g; green = b;
	life_initial = rand() % vida; life = life_initial; 
}
