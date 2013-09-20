#ifndef TANQUE_H
#define TANQUE_H

#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>

#include <GL\glut.h>
#include "uglyfont.h"
#include "Teclado.h"
#include "Helper.h"
#include "ManagerTexture.h"
#include "EfectoParticulas.h"


using namespace std;

namespace TanqueFSM
{
	enum Estados
	{
		Mover,
		Disparar,
		Parar,
		Apuntar,
		Girar
	};
};

class Tanque
{
private:

	class Bala {
		private:
		  double x;
		  double y;
		  double incrementox;
		  double incrementoy;
		public:
		  Bala(double posX, double posY, double incX, double incY) : x(posX), y(posY), incrementox(incX), incrementoy(incY) {}
		  bool Update() {
			x+=incrementox;
			y+=incrementoy;
			////Me fijo si hay colision de la bala con una torre enemiga
			//if( fabs(x-EnemigoX)+fabs(y-EnemigoY) < 50 ) {
			//  Energia-=10;
			//  cout << endl << "Energia del enemigo: " << Energia << endl;
			//  return true;
			//}
			//Si esta fuera de la pantalla, elimino la bala
			return ( x > (wm)/2 || x < (-wm)/2 || y > (hm)/2 || y < (-hm)/2 );
		  }

		  void Draw() {
			glVertex2d(x,y);
		  }
	};

	TanqueFSM::Estados estadoActual;

	double TanqueX, 
	  TanqueY, 
	  Oruga1,
	  Oruga2,
	  TanqueAng, 
	  ArmaAng,
	  ArmaTamanio;

	float Tanque_Escala;
	int Energia;

	float radioAtaque;

	int direccionAngulo,
		direccionPaso,
		direccionApuntar,
		contadorPasosFSM,
		contadorAnguloFSM,
		contadorDisparosFSM,
		contadorIntervaloDisparo,
		contadorAnguloApuntarFSM,
		velocidadTanque;

	EfectoParticulas* fx;

	list<Bala> proyectil;
	ManagerTexture* managerText;

	unsigned int* orugatext;

	void makeStripeImage(void);
	void DibujarTanque(void);
	void DibujarCuerpo(void);
	void DibujarOruga(float pos);
	void DibujarTorre(void);
	void DibujarArma(void);
	void DibujarFaro(void);
	void Disparar(void);
	void CambiarEstado(void);
	bool CalcularAlcance(float target_x,float target_y);
public:
	void Dibujar();
	void Mover(int dt);
	void Update(int dt,float target_x,float target_y);
	Tanque(double x,double y,ManagerTexture& manager);
	~Tanque(void);
};

#endif