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
#include "Avion.h"


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
		  Avion* enemigo;
		public:
		  Bala(double posX, double posY, double incX, double incY, Avion* avion) : 
								x(posX), y(posY), incrementox(incX), incrementoy(incY)
		  {
			  enemigo =  avion;
		  }

		  bool Update() {
			x+=incrementox;
			y+=incrementoy;
			//Me fijo si hay colision de la bala con el avion
			if( fabs(x-enemigo->AvionX)+fabs(y-enemigo->AvionY) < 50 ) {
			  enemigo->RecibirImpacto(25);
			  cout << endl << "Energia del Avion: " << enemigo->energia << endl;
			  return true;
			}
			//Si esta fuera de la pantalla, elimino la bala
			return ( x > (wm)/2 || x < (-wm)/2 || y > (hm)/2 || y < (-hm)/2 );
		  }

		  void Draw() {
			glVertex2d(x,y);
		  }
	};

	TanqueFSM::Estados estadoActual;

	
	double Oruga1,
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
	EfectoParticulas* fx2;

	list<Bala> proyectil;
	ManagerTexture* managerText;
	Avion* enemigo;

	bool isDead;

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
	double TanqueX, 
		   TanqueY;
	void Dibujar();
	void Mover(int dt);
	void RecibirImpacto(int energia);
	void Update(int dt,float target_x,float target_y);
	Tanque(double x,double y,ManagerTexture& manager, Avion& avion);
	~Tanque(void);
};

#endif