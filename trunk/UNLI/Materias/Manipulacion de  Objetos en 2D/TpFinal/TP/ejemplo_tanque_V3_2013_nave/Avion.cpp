#include "Avion.h"


Avion::Avion(int width,int height,ManagerTexture& manager)
{	
	this->width = width;
	this->height = height;

	isReady = false;

	zAla=0.03;
	zAVION=0.02;
	zAVION_CUERPO=0.01;
	zCABINA=0.04;
	zMETRALLA=0.015;
	
	AvionX=400;
	AvionY=300; 
	AvionAng=0; 
	ArmaAng=0;
	ArmaTamanio=0;

	lightY = 0;
	AngMetralla = -1;
	MetrallaX = 0;
	MetrallaY = 0;
	incyMetralla = 0;
	incxMetralla = 0;
	isFired = false;
	isTurbo = false;
	
	lpos[0] = 2;
	lpos[1] = 1;
	lpos[2] = 5;
	lpos[3] = 1;	

	managerText = &manager;

	fx = new EfectoParticulas(0,0,0.001,0.0f,0.0f,4, 150, 50, 0.0f, 45, 0);
	fx->SetColor(1,1,1);
}

void Avion::Mover(int dt,Teclado& teclado)
{
	  if(isFired)
	  {
		incyMetralla+=20;
		if(incyMetralla < 0 || incyMetralla > 1000)
			isFired = false;
	  }

	  lightY++;
	  if(lightY > 20.0)
		  lightY = 0.0;

	  //Convierte AvionAng de grados a radianes
	  double ang=AvionAng*PI/180.0;

	  if(teclado.Adelante())
	  {
		 isReady =  true;
	  }

	  if(isReady)	  
	  {
		  // double sin(double ang); // Calcula el seno de ang medido en radianes
		  if(teclado.Atras()) //Turbo
		  {
			  AvionX-=12*sin(ang);
			  AvionY+=12*cos(ang);
			  lightY +=5;
			  isTurbo = true;
		  }
		  else
		  {
			  AvionX-=3*sin(ang);
			  AvionY+=3*cos(ang);
			  isTurbo = false;
		  }
	  }

	  /*if(teclado.Atras())
	  {
		AvionX+=5*sin(ang);
		AvionY-=5*cos(ang);
	  }*/

	  if(teclado.IzquierdaAux())
	  {
		AvionAng+=2;
	  }

	  if(teclado.DerechaAux())
	  {
		AvionAng-=2;		
	  }

	  if(!isFired && teclado.Disparar())
	  {
		  isFired = true;		
		  MetrallaX = AvionX;
		  MetrallaY = AvionY;
		  incxMetralla = -sin(AvionAng);
		  incyMetralla = cos(AvionAng);			  
		  AngMetralla = AvionAng;
	  }

	  if(isTurbo)
	  { 
		if(!fx->GetActivo()) 
		{
			fx->ToggleActivo();
		}		
	  }
	  else
	  {
		if(fx->GetActivo()) 
		{
			fx->ToggleActivo();
		}
	  }

	  fx->Actualizar();	
	  fx->SetPosicion(AvionX,AvionY);	  	  
}

void Avion::DibujaTexto()
{
	glPushMatrix();
	glTranslated(0,0,0.5);

	static int i=10, j=570;
	glColor3f(0.9f,0.9f,0.9f);
	
	stringstream ss;
	
	ss << AvionX;
	
	string s;
	s = "x: ";
	s += ss.str();
	s += " y: ";

	ss.str(string());
	ss << AvionY;

	s+= ss.str();

	ss.str(string());

	s += "\n Ang: ";

	ss << ((int)AvionAng) % 360;

	s += ss.str();

	Helper::print_text(s, i, j, 10);	

	glPopMatrix();	
}

void Avion::Dibujar()
{
	
	fx->Dibujar();
  
	DibujarAvion();
	DibujaTexto();
}

void Avion::DibujarCabina() {
  glColor3d(0.6,0.7,0.9);
  glBegin( GL_TRIANGLE_FAN );
  glVertex2d(0,	0);
  for(double r=0; r<PI*2; r+=0.1)
    glVertex2d(cos(r), sin(r));
  glVertex2d(1.0,0.0);
  glEnd();
}

void Avion::DibujarCuerpo() {
 	
  glColor3d(0.4,0.4,0.4);
  glBegin( GL_TRIANGLE_FAN);

	glVertex2f(0.0,	0.0);
	glVertex2f(0.0,	70.0);
	glVertex2f(-8, 35.0);
	glVertex2f(-10,	-30.0);
	glVertex2f(0.0,	-15.0);
	glVertex2f(10, -30.0);
	glVertex2f(8,	35.0);
	glVertex2f(0.0,	70.0);

  glEnd();

  glColor3f(0.9f,0.9f,0.9f);
  glPointSize(2.0);
  glBegin(GL_POINTS);
	glVertex2d(5.0,20.0 + lightY);
	glVertex2d(0.0,21.0 + lightY);
	glVertex2d(-5.0,20.0 + lightY);
  glEnd();
}

void Avion::DibujarAla() {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, managerText->texid[Manager::AVION]);  
  glColor3d(0.7,0.7,0.7);
  glBegin( GL_TRIANGLE_FAN );
  glTexCoord2f(0.0, 0.0); glVertex2d(35,10);
  glTexCoord2f(0.5, 0.5); glVertex2d(0.0,20.0); 
  glTexCoord2f(0.5, 0.5); glVertex2d(0.0,0.0); 
  glTexCoord2f(0.6, 1.0); glVertex2d(35,4);
  glTexCoord2f(1.0, 1.0); glVertex2d(50.0,0.0);
  glEnd();

   glDisable(GL_TEXTURE_2D);
}

void Avion::DibujarMetralla()
{
	glColor3d(0.4,0.4,0.4);  
	glBegin(GL_QUADS);
	glVertex2d(0.0,0.0);
	glVertex2d(7.0,0.0);
	glVertex2d(7.0,40.0);
	glVertex2d(0.0,40.0);  
	glEnd();

	glColor3f(0.0f,0.0f,0.0f);
	glPointSize(2.5);
	glBegin(GL_POINTS);
		glVertex2d(2.5,36.0);
	glEnd();
	
	glBegin(GL_POINTS);
		glVertex2d(2.5,15.0 + lightY);		
	glEnd();

}

void Avion::DibujarAvion() {
	
  glPushMatrix();// inicio push1

  if(isFired)
  {	  
	  glPushMatrix();
	  
	  glTranslated(MetrallaX,MetrallaY,zAVION);
	  glRotated(AngMetralla,0,0,1); 	  

	 //Metralla
	  glPushMatrix();	  
	  glTranslated(25+incxMetralla,-5+incyMetralla,zMETRALLA);
	  DibujarMetralla();
	  glPopMatrix();

	  glPushMatrix();  	  	   
	  glTranslated(-35+incxMetralla,-5+incyMetralla,zMETRALLA);
	  DibujarMetralla();
	  glPopMatrix();

	  glPopMatrix();
  }
 

  // Posiciona y rota el Avion en el modelo
  glTranslated(AvionX,AvionY,zAVION); 
  
  glRotated(AvionAng,0,0,1);
  
 

  if(!isFired)  
  {
	  //Metralla
	  glPushMatrix();
	  glTranslated(25,-5,zMETRALLA);
	  DibujarMetralla();
	  glPopMatrix();

	  glPushMatrix();  	  
	  glTranslated(-35 ,-5,zMETRALLA);
	  DibujarMetralla();
	  glPopMatrix();
  }

  
  //Dibujamos las distintas partes de la nave, aplicando las transformaciones necesarias
  //Ala derecha
  glPushMatrix();
  glTranslated(0,0,zAla);
  
  DibujarAla();
  
  glPushMatrix();
  glTranslatef(12.0f, 7.0f, 0.5f);
  glRotated(-10,0,0,1);
  glScaled(6,6,6);
  glColor3f(0.0,0.3,0.3);
  glLineWidth(2);
  YsDrawUglyFont("F16",0);
  glPopMatrix();

  glPopMatrix();

  //Ala izquierda
  glPushMatrix();
  glTranslated(0,0,zAla);
  glScaled(-1,1,1); //Con este escalamiento logramos reflejar (x = -AnchoAla * x)  
  DibujarAla();
  glPopMatrix();
  
  
  //Cuerpo
  glPushMatrix();
  glTranslated(0,0,zAVION_CUERPO);
  DibujarCuerpo();
  glPopMatrix();
  
  //Cabina
  glPushMatrix();  
  glTranslated(0,0,zCABINA);
  glScaled(6,12,1);  
  DibujarCabina();
  glPopMatrix();
  
  // Luego de aplicar la traslacion (AvionX,AvionY) y la rotacion (AvionAng) inicial 
  // dibuja un punto en la posición 0,0 (es solo para ayuda)
  glPushMatrix();
  glTranslated(0,0,zCABINA);
  glColor3f(0.0f,0.0f,0.0f);
  glPointSize(5.0);
  glBegin(GL_POINTS);
  glVertex2d(0.0,0.0);
  glEnd();
  glPopMatrix();
  
  glPopMatrix();// fin push1
}

Avion::~Avion()
{
	delete fx;
}