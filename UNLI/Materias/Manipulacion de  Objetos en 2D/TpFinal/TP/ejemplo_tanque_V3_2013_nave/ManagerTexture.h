#ifndef MANAGERTEXT_H
#define MANAGERTEXT_H

#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>

#include <GL\glut.h>
#include "uglyfont.h"
#include "Teclado.h"
#include "Helper.h"

using namespace std;

#define stripeImageWidth 32

namespace Manager
{
const int TANQUE1d = 0,
		   AVION = 1,
		   CUBO = 2,
		   PASTO = 3;
}
class ManagerTexture
{

private:
	//Textura 1D
	GLubyte stripeImage[stripeImageWidth][4];
	

	void makeStripeImage(void);
	

public:
	

	void LoadTexture(void);
	GLuint texid[10];
	ManagerTexture();
	~ManagerTexture();
};

#endif