#ifndef AVION_H
#define AVION_H

#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>

#include <GL\glut.h>
#include "uglyfont.h"
#include "Teclado.h"
#include "Helper.h"
#include "ManagerTexture.h"
#include "EfectoParticulas.h"

using namespace std;

class Avion{
private:
	double   
		zAla,
		zAVION,
		zAVION_CUERPO,
		zCABINA,  
		zMETRALLA,
		zPARED;

	double 	 
	  ArmaAng,
	  ArmaTamanio;

	bool isTurbo;

	double lightY,
		AngMetralla,
		MetrallaX,
		MetrallaY,
		incyMetralla,
		incxMetralla,
		isFired;
		// Creamos el unico efecto de particulas que tendremos en este demo
		/*
		Importante: las variables son:
		posicion x
		posicion y
		aceleracion en el eje y
		tamanio de particula (glPointSize(size_particle))
		cantidad de particulas
		tiempo de vida de particulas
		velocidad de particulas
		amplitud del sistema (cutoff)
		direccion (angle)
		*/
		EfectoParticulas* fx;

	double lpos[4];
	int width,
		height;
	
	bool isReady;//true, el avion vuela de forma automatica
	
	ManagerTexture* managerText;

	void DibujarCabina();
	void DibujarMetralla();
	void DibujarAla();
	void DibujarCuerpo();
	void DibujarAvion();
	void DibujaTexto();
public:
	double 
	  AvionX,
	  AvionY,
	  AvionAng;
		
	Avion(int width,int height,ManagerTexture& manager);
	~Avion();
	void Dibujar();
	void Mover(int dt,Teclado& teclado);	
};

#endif