// TP Final
// 
#include <iostream> // cout
#include <cstdlib> // exit
#include <cmath> // atan sqrt fabs
#include <fstream> // file io
#include <list>
#include <vector>
#include <GL/glut.h>
#include <iostream> // cout
#include <sstream>
#include <time.h>

#include "Teclado.h"
#include "uglyfont.h"
#include "Helper.h"
#include "Avion.h"
#include "Tanque.h"
#include "ManagerTexture.h"


using namespace std;

float Escala;

//------------------------------------------------------------
// variables globales
int
  w=800,h=600; // tamanio inicial de la ventana
   //tamanio del mapa

short modifiers=0;  // ctrl, alt, shift (de GLUT)
inline short get_modifiers() {return modifiers=(short)glutGetModifiers();}
int cant_tanques;

int
  boton=-1, // boton del mouse clickeado
  xclick,yclick; // x e y cuando clickeo un boton

const double   
  zPARED=0.0;

float lpos[]={2,1,5,1};
bool cl_info=true; // informa por la linea de comandos

bool isModoZoom = false;
bool isGameOver = false;
bool isGameWin = false;
bool isGameStart = false;

float Timer = 181;

Teclado teclado('f', 'w', 's', ' ', ' ', 'a', 'd'); // para manejar la entrada por teclado

float escala1=0.67,
	  escala0=0.08, // escala de los objetos window/modelo pixeles/unidad. Inicialmente es 1
	  eye[]={0,0,1}, target[]={0,0,0}, up[]={0,1,0}, // camara
	  znear=.001, zfar=10; //clipping planes cercano y alejado de la camara

	ManagerTexture managertext;	
	
	Avion avion(w,h,managertext);

	list<Tanque> tanques;
		

void InicializaObjetos()
{	
	tanques.push_back(*(new Tanque(2000,-2000,managertext,avion)));
	tanques.push_back(*(new Tanque(3000,3000,managertext,avion)));
	tanques.push_back(*(new Tanque(-4000,500,managertext,avion)));	
	tanques.push_back(*(new Tanque(-4000,4000,managertext,avion)));

	tanques.push_back(*(new Tanque(-4000,1000,managertext,avion)));
	tanques.push_back(*(new Tanque(4000,-4000,managertext,avion)));
	tanques.push_back(*(new Tanque(-1000,2000,managertext,avion)));
	tanques.push_back(*(new Tanque(-4000,-4000,managertext,avion)));

	tanques.push_back(*(new Tanque(-1000,-1000,managertext,avion)));
	tanques.push_back(*(new Tanque(-2000,-2000,managertext,avion)));
	tanques.push_back(*(new Tanque(-3000,-3000,managertext,avion)));
	tanques.push_back(*(new Tanque(-3000,-1500,managertext,avion)));
	
	cant_tanques = 12;
	
	//tanques.push_back(*(new Tanque(1000,1000,managertext)));

	//Inicializa el Random
	srand(time(NULL));	
}

void DetectarColisiones()
{
	list<Tanque>::iterator t = tanques.begin();
	while( t != tanques.end())
	{
		if(!t->isDead)
		{
			if( fabs(avion.MetrallaX-t->TanqueX)+fabs(avion.MetrallaY-t->TanqueY) < 50 ) {
				  t->RecibirImpacto(100);	
				  avion.MetrallaOff();
				  cant_tanques--;
				}
		}
		t++;
	}
}

void ActualizaObjetos(int dt)
{
	//Actualizamos el estado de los tanques
    list<Tanque>::iterator t = tanques.begin();
    while( t != tanques.end() ) {
		t->Update(dt,avion.AvionX,avion.AvionY);		
        t++;
    }
	//Detectar colisiones
	DetectarColisiones();

	if(avion.isDead || Timer <= 0)
	{
		isGameOver = true;
	}

	if(cant_tanques == 0)
	{
		isGameWin = true;
	}
}

void DibujarPared() {
  glColor3f(0.9f,0.9f,0.9f);
  glPushMatrix();
  glTranslated(0,0,zPARED);

  int paredw = 400;
  int paredh = 475;

  glPushMatrix();
  glTranslated(100,-60,0);

  glEnable(GL_TEXTURE_2D);
  
  glBindTexture(GL_TEXTURE_2D,managertext.texid[Manager::CUBO]);
  
  glBegin(GL_QUADS);
	glTexCoord2f(0.00, 0.66); glVertex2f(paredw/2,paredh/2);
    glTexCoord2f(0.00, 0.34); glVertex2f(paredw,paredh/2);
    glTexCoord2f(0.51, 0.34); glVertex2f(paredw,paredh);
    glTexCoord2f(0.51, 0.66); glVertex2f(paredw/2,paredh);
  glEnd();

  glDisable(GL_TEXTURE_2D);

  glPopMatrix();  

  glLineWidth(5.0*Escala);
  glBegin(GL_LINES);
  glVertex2i(325,400); glVertex2i(325,200);
  glVertex2i(325,200); glVertex2i(475,200);
  glVertex2i(475,200); glVertex2i(475,400);
  glEnd();

  glPopMatrix();
}

void DibujarPiso() {
  //const int w_2=1024/2, h_2=1024/2;//para que no se deforme la textura
  const int w_2=w/2, h_2=h/2;

  glEnable(GL_TEXTURE_2D);
  
  glBindTexture(GL_TEXTURE_2D,managertext.texid[Manager::PASTO]);

  glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2i(-wm/2,-hm/2); 
	glTexCoord2f(15, 0); glVertex2i(wm/2,-hm/2);
	glTexCoord2f(15, 15); glVertex2i(wm/2,hm/2);
	glTexCoord2f(0, 15); glVertex2i(-wm/2,hm/2);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  
}

void DibujarObjetos()
{	
  DibujarPiso();
   
  DibujarPared();

  if(!isGameOver && !isGameWin)
  {
	  list<Tanque>::iterator t=tanques.begin();
	  while( t != tanques.end() ) {
		t->Dibujar();
		t++;
	  }
	  avion.Dibujar();
   }
}

void DibujarHUD()
{	 
	if(!isModoZoom)
	{
		int x = -w/2;
		int y = h/2;
		glPushMatrix();
		glColor3f(0.9f,0.9f,0.9f);
		glTranslated(target[0],target[1],0.5);
	
		glScalef(1.35,1.3,0);
		stringstream ss;
		string s;
		if(isGameOver)
		{	
			x = -w/4;
			y = h/3;
			s = "GAME OVER\n\n";
			Helper::print_text(s,x,y, 20,true);

			y -= 50;
			s = "Presiona Escape para salir...";
			Helper::print_text(s,x,y, 20,true);			
		}
		else if(isGameWin)
		{	
			x = -w/4;
			y = h/3;
			s = "EL JUGADOR GANA EL JUEGO\n\n";					
			Helper::print_text(s,x,y, 20,true);
			y -= 50;
			s = "Presiona Escape para salir...";
			Helper::print_text(s,x,y, 20,true);
		}
		else if(!isGameStart)
		{	
			x = -w/4;
			y = h/3;
			s = "Presiona W para comenzar";					
			Helper::print_text(s,x,y, 20,true);
		}
		else
		{	
			s = "CANTIDAD DE TANQUES: ";					
			ss << cant_tanques;
			s+= ss.str();
			Helper::print_text(s,x,y, 20,true);
						
			ss.str(std::string());
			ss.clear();
			ss << (int) Timer;
			s = "TIEMPO: ";
			s += ss.str();
			x = w/3;
			Helper::print_text(s,x,y, 20,true);
		}
		glPopMatrix();
	}
}

//============================================================
// callbacks

//------------------------------------------------------------

// arma un un nuevo buffer (back) y reemplaza el framebuffer
void Display_cb() {

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 
  // arma el back-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  // rellena con color de fondo
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glPushMatrix();
   

	DibujarObjetos();
  

  glPopMatrix();

  DibujarHUD();

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

//------------------------------------------------------------
// Regenera la matriz de proyeccion
// cuando cambia algun parametro de la vista
void regen() {
  //  if (cl_info) cout << "regen" << endl;
  
  //POSICIONA LA CAMARA
  //eye=posicion desde donde miran los ojos.[Se mira desde arriba]
  //up=direccion a la que apunta la parte superior de la camara.
  //target=punto hacia donde se mira.[Se debe mirar hacia donde gira el Tanque]
  /*	
  gluLookAt(   eye[0],   eye[1],   eye[2],
  target[0],target[1],target[2],
  up[0],    up[1],    up[2]);// ubica la camara
  */	  
 // if (!dibuja) return;

  // matriz de proyeccion
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();

  // aplica la escala que se setea con el mouse
  double w0=(double)w/2/Escala,h0=(double)h/2/Escala; // semiancho y semialto en el target

  // proyeccion ortogonal
  glOrtho(-w0,w0,-h0,h0,znear,zfar);

  glMatrixMode(GL_MODELVIEW); glLoadIdentity(); // matriz del modelo->view

  gluLookAt(   eye[0],   eye[1],   eye[2],
            target[0],target[1],target[2],
                up[0],    up[1],    up[2]);// ubica la camara

   glutPostRedisplay();
}

void Idle_cb() 
{ 
  static unsigned int lt=0;  	
  
  int dt = glutGet(GLUT_ELAPSED_TIME) - lt;
  
  

  if(dt > 30) 
  {
	  if(teclado.Salir()) 
	  {
		  exit(EXIT_SUCCESS);
	  }

	  if(!isGameOver && !isGameWin)
	  {
		  if(teclado.IsKeyPressed('z') ||teclado.IsKeyPressed('Z'))
		  {
			  Escala = escala1;
			  isModoZoom = false;
		  }

		  if(teclado.IsKeyPressed('x') ||teclado.IsKeyPressed('X'))
		  {
			  Escala = escala0;

			  eye[0]=0;
			  eye[1]=0;
			  eye[2]=1;
			  target[0]=0;
			  target[1]=0;		  
			  target[2]=0;

			  isModoZoom = true;
		  }

		  avion.Mover(dt,teclado);	 

		  if(!isGameStart && avion.isReady)
		  {
			  isGameStart = true;
		  }

		  if(isGameStart)
		  {
			Timer = Timer - (dt/1000.0f);
			ActualizaObjetos(dt);
			DetectarColisiones();	 
		  }
	}
	else
	{
		isModoZoom = false;
	}

	lt = glutGet(GLUT_ELAPSED_TIME);	

	if(!isModoZoom)
	{
	  eye[0]=avion.AvionX;
	  eye[1]=avion.AvionY;
      eye[2]=1;
      target[0]=avion.AvionX;
      target[1]=avion.AvionY;
      target[2]=0;
	}
    regen();
  }
}


//------------------------------------------------------------
// Maneja cambios de ancho y alto de la ventana
void Reshape_cb(int width, int height){
  // cout << "reshape " << width << "x" << height << endl;
  if (!width||!height) return; // minimizado ==> nada
  w=width; h=height;

  glViewport(0,0,w,h); // región donde se dibuja (toda la ventana)
  
  regen();
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
  glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);// pide color RGB y double buffering
  glutInitWindowSize(w,h); 
  glutInitWindowPosition(10,10);
  glutCreateWindow("TP Final"); // crea el main window

  // declara los callbacks, los que (aun) no se usan (aun) no se declaran
  glutDisplayFunc(Display_cb);
  glutReshapeFunc(Reshape_cb); 
  glutSpecialFunc(Special_cb);   
  glutIdleFunc(Idle_cb);  //Idle

  teclado.Iniciar();

  // OpenGL

  //Z-Buffer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc( GL_LEQUAL );
  glDepthRange(0.0, 1.0);
  glClearDepth(1.0);

  glEnable(GL_NORMALIZE); // para que el scaling no moleste
  glDisable(GL_AUTO_NORMAL); // para nurbs??
  glEnable(GL_POLYGON_OFFSET_FILL); 
  glPolygonOffset (1,1); // coplanaridad
  glEnable(GL_POINT_SMOOTH); glEnable(GL_LINE_SMOOTH); glEnable(GL_POLYGON_SMOOTH);

  glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

  glShadeModel(GL_SMOOTH);

  // transparencias
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);  
  glDisable(GL_BLEND);

  //glClearColor(0.23f,0.20f,0.01f,1.f); // color de fondo
  glClearColor(0.01f,0.01f,0.01f,1.f);
  
   // direccion de los poligonos
  glFrontFace(GL_CCW); 
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);  
  glCullFace(GL_BACK); // se habilita por objeto (cerrado o abierto)
  
  managertext.LoadTexture();

  Escala = escala1;

  // las operaciones subsiguientes se aplican a la matriz de modelado GL_MODELVIEW
  regen();

  InicializaObjetos();

}

//------------------------------------------------------------
// main
int main(int argc,char** argv) {
  // teclas a utilizar
  cout << "Teclas a utilizar:" << endl;
  cout << "w: avanza" << endl;
  cout << "s: modo turbo" << endl;
  cout << "d: gira en sentido horario" << endl;
  cout << "a: gira en sentido antihorario" << endl;
  cout << "f: Disparar" << endl;
  cout << "z: Zoom in" << endl;
  cout << "x: Zoom out" << endl;
  
  
  glutInit(&argc,argv); // inicialización interna de GLUT
  inicializa(); // define el estado inicial de GLUT y OpenGL
  glutMainLoop(); // entra en loop de reconocimiento de eventos
  return 0; // nunca se llega acá, es sólo para evitar un warning
}
