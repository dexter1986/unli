// TP 2 - MO2D
// 

#include <iostream> // cout
#include <cstdlib> // exit
#include <cmath> // fabs
#include <sstream>
#include <GL/glut.h>
#include "teclado.h"
#include "uglyfont.h"

using namespace std;

//------------------------------------------------------------
// variables globales
int
  w=800,h=600; // tamanio inicial de la ventana

double 
  AvionX=400, 
  AvionY=300, 
  AvionAng=0, 
  ArmaAng=0,
  ArmaTamanio=0;

const double   
  zAla=0.2,
  zAVION=0.1,
  zAVION_CUERPO=0.3,
  zCABINA=0.4,
  zFARO=0.4,
  zTORRE=0.5,  
  zCANON=0.7,
  zPARED=0.0;

const double PI=4*atan(1.0);
bool cl_info=true; // informa por la linea de comandos

//============================================================

void print_text(string cadena, int x, int y, int espacio=10) {
	for(unsigned int i=0; i < cadena.size(); i++) {
		glRasterPos2i( x + i*espacio, y );
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,(int)cadena[i]);//GLUT_BITMAP_9_BY_15//GLUT_BITMAP_TIMES_ROMAN_10
	}
}

void DibujarCabina() {
  glColor3d(0.6,0.7,0.9);
  glBegin( GL_TRIANGLE_FAN );
  glVertex2d(0,	0);
  for(double r=0; r<PI*2; r+=0.1)
    glVertex2d(cos(r), sin(r));
  glVertex2d(1.0,0.0);
  glEnd();
}

void DibujarCuerpo() {
  glColor3d(0.4,0.4,0.4);
  glBegin( GL_TRIANGLE_FAN );
  glVertex2d(0.0,	0.0);
  glVertex2d(0.0,	70.0);
  glVertex2d(-8, 35.0);
  glVertex2d(-10,	-30.0);
  glVertex2d(0.0,	-15.0);
  glVertex2d(10, -30.0);
  glVertex2d(8,	35.0);
  glVertex2d(0.0,	70.0);
  glEnd();
}

void DibujarAla() {
  glColor3d(0.7,0.7,0.7);
  glBegin( GL_TRIANGLE_FAN );
  glVertex2d(35,10);
  glVertex2d(0.0,20.0); 
  glVertex2d(0.0,0.0); 
  glVertex2d(35,4);
  glVertex2d(50.0,0.0);
  glEnd();
}

void DibujarAvion() {
  glPushMatrix();// inicio push1

  // Posiciona y rota el Avion en el modelo
  glTranslated(AvionX,AvionY,zAVION);
  glRotated(AvionAng,0,0,1);  
  
  //Dibujamos las distintas partes de la nave, aplicando las transformaciones necesarias
  //Ala derecha
  glPushMatrix();
  glTranslated(0,0,zAla);
  DibujarAla();
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
  // dibuja un punto en la posici�n 0,0 (es solo para ayuda)
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

void DibujarPared() {
  glColor3f(0.9f,0.9f,0.9f);
  glPushMatrix();
  glTranslated(0,0,zPARED);

  glLineWidth(5.0);
  glBegin(GL_LINES);
  glVertex2i(325,400); glVertex2i(325,200);
  glVertex2i(325,200); glVertex2i(475,200);
  glVertex2i(475,200); glVertex2i(475,400);
  glEnd();

  glPopMatrix();
}

void DibujaTexto()
{
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

	print_text(s, i, j, 10);	
	
}

//============================================================
// callbacks

//------------------------------------------------------------

// arma un un nuevo buffer (back) y reemplaza el framebuffer
void Display_cb() {
  // arma el back-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// rellena con color de fondo
  glPushMatrix();
  /*
  // dibuja un punto en la posici�n x,y que querramos visualizar (es solo para probar)
  glColor3f(1.0f,0.0f,0.0f);
  glPointSize(5.0);
  glBegin(GL_POINTS);
  glVertex2d(50,50);
  glEnd();
  */
  
  DibujarPared();

  DibujarAvion();

  DibujaTexto();

  glPopMatrix();

  glutSwapBuffers(); // lo manda al monitor
  
  // chequea errores
  int errornum=glGetError();
  while(errornum!=GL_NO_ERROR){
    if (cl_info){
      if(errornum==GL_INVALID_ENUM)
        cout << "GL_INVALID_ENUM" << endl;
      else if(errornum==GL_INVALID_VALUE)
        cout << "GL_INVALID_VALUE" << endl;
      else if (errornum==GL_INVALID_OPERATION)
        cout << "GL_INVALID_OPERATION" << endl;
      else if (errornum==GL_STACK_OVERFLOW)
        cout << "GL_STACK_OVERFLOW" << endl;
      else if (errornum==GL_STACK_UNDERFLOW)
        cout << "GL_STACK_UNDERFLOW" << endl;
      else if (errornum==GL_OUT_OF_MEMORY)
        cout << "GL_OUT_OF_MEMORY" << endl;
    }
    errornum=glGetError();
  }
}

void Idle_cb() {
  static unsigned int lt=0;  	
  int dt = glutGet(GLUT_ELAPSED_TIME) - lt;
  if(dt > 60) {
	lt = glutGet(GLUT_ELAPSED_TIME);	
	glutPostRedisplay();
  }
}

//------------------------------------------------------------
// Maneja cambios de ancho y alto de la ventana
void Reshape_cb(int width, int height){
  // cout << "reshape " << width << "x" << height << endl;
  if (!width||!height) return; // minimizado ==> nada
  w=width; h=height;
  glViewport(0,0,w,h); // regi�n donde se dibuja (toda la ventana)
  // rehace la matriz de proyecci�n (la porcion de espacio visible)
  glMatrixMode(GL_PROJECTION);  glLoadIdentity();
  glOrtho(0,w,0,h,-1,1); // unidades = pixeles
  // las operaciones subsiguientes se aplican a la matriz de modelado GL_MODELVIEW
  glMatrixMode(GL_MODELVIEW);  
  glutPostRedisplay(); // avisa que se debe redibujar
}

//------------------------------------------------------------
// Teclado

// Maneja pulsaciones del teclado (ASCII keys)
// x,y posicion del mouse cuando se teclea (aqui no importan)
void Keyboard_cb(unsigned char key,int x,int y) {
  // Convierte AvionAng de grados a radianes
  double ang=AvionAng*PI/180.0;
  switch(key){
  case 'w':
  case 'W':
    // double sin(double ang); // Calcula el seno de ang medido en radianes
    AvionX-=5*sin(ang);
    AvionY+=5*cos(ang);
    glutPostRedisplay();
    break;
  case 's':
  case 'S':
    AvionX+=5*sin(ang);
    AvionY-=5*cos(ang);
    glutPostRedisplay();
    break;
  case 'a':
  case 'A':
    AvionAng+=2;
    glutPostRedisplay();
    break;
  case 'd':
  case 'D':
    AvionAng-=2;
    glutPostRedisplay();
    break;
  case 27:
    exit(EXIT_SUCCESS);
    break;
  }
}

// Special keys (non-ASCII)
// teclas de funcion, flechas, page up/dn, home/end, insert
void Special_cb(int key,int xm=0,int ym=0) {
  if (key==GLUT_KEY_F4 && glutGetModifiers()==GLUT_ACTIVE_ALT) // alt+f4 => exit
    exit(EXIT_SUCCESS);
}

//------------------------------------------------------------
void inicializa() {
  // GLUT
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);// pide color RGB y double buffering
  glutInitWindowSize(w,h); glutInitWindowPosition(10,10);
  glutCreateWindow("Ejemplo Avion"); // crea el main window

  // declara los callbacks, los que (aun) no se usan (aun) no se declaran
  glutDisplayFunc(Display_cb);
  glutReshapeFunc(Reshape_cb);
  glutKeyboardFunc(Keyboard_cb);
  glutSpecialFunc(Special_cb);
  glutIdleFunc(Idle_cb);  //Idle

  // OpenGL

  //Z-Buffer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc( GL_LEQUAL );
  glDepthRange(0.0, 1.0);
  glClearDepth(1.0);

  //glClearColor(0.23f,0.20f,0.01f,1.f); // color de fondo
  glClearColor(0.01f,0.01f,0.01f,1.f);
  // las operaciones subsiguientes se aplican a la matriz de modelado GL_MODELVIEW
  glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

//------------------------------------------------------------
// main
int main(int argc,char** argv) {
  // teclas a utilizar
  cout << "Teclas a utilizar:" << endl;
  cout << "w: avanza" << endl;
  cout << "s: retrocede" << endl;
  cout << "d: gira en sentido horario" << endl;
  cout << "a: gira en sentido antihorario" << endl;
  
  
  glutInit(&argc,argv); // inicializaci�n interna de GLUT
  inicializa(); // define el estado inicial de GLUT y OpenGL
  glutMainLoop(); // entra en loop de reconocimiento de eventos
  return 0; // nunca se llega ac�, es s�lo para evitar un warning
}
