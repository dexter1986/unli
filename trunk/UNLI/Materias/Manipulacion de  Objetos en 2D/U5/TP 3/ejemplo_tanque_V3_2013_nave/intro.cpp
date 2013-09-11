// TP 3 - MO2D
// 
#include <iostream> // cout
#include <cstdlib> // exit
#include <cmath> // atan sqrt fabs
#include <fstream> // file io
#include <list>
#include <GL/glut.h>
#include <iostream> // cout
#include <sstream>

#include "Teclado.h"
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
  zMETRALLA=0.15,
  zPARED=0.0;

double lightY = 0;
double AngMetralla = -1;
double MetrallaX = 0;
double MetrallaY = 0;
double incyMetralla = 0;
double incxMetralla = 0;
bool isFired = false;
float lpos[]={2,1,5,1};
const double PI=4*atan(1.0);
bool cl_info=true; // informa por la linea de comandos

Teclado teclado('f', 'w', 's', ' ', ' ', 'a', 'd'); // para manejar la entrada por teclado

GLuint texid[3];//GLuint texid;

// Load a PPM Image
bool mipmap_ppm(const char *ifile){
  char dummy; int maxc,wt,ht;
  ifstream fileinput(ifile, ios::binary);
  if (!fileinput.is_open()) {cerr<<"Not found"<<endl; return false;}
  fileinput.get(dummy);
  if (dummy!='P') {cerr<<"Not P6 PPM file"<<endl; return false;}
  fileinput.get(dummy);
  if (dummy!='6') {cerr<<"Not P6 PPM file"<<endl; return false;}
  fileinput.get(dummy);
  dummy=fileinput.peek();
  if (dummy=='#') do {
    fileinput.get(dummy);
  } while (dummy!=10);
  fileinput >> wt >> ht;
  fileinput >> maxc;
  fileinput.get(dummy);
  
  unsigned char *img=new unsigned char[3*wt*ht];
  fileinput.read((char *)img, 3*wt*ht);
  fileinput.close();
  //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, wt, ht,  GL_RGB, GL_UNSIGNED_BYTE, img);
  // conversion a rgba alpha=255-(r+g+b)/3 (blanco=transparente, negro=opaco)
  unsigned char *imga=new unsigned char[4*wt*ht];
  unsigned char r,g,b;
  for (int i=0;i<wt*ht;i++){
    r=imga[4*i+0]=img[3*i+0];
    g=imga[4*i+1]=img[3*i+1];
    b=imga[4*i+2]=img[3*i+2];
    imga[4*i+3]=((r+g+b==765)? 0: 255);
    //imga[4*i+3]=255-(r+g+b)/3;
  }
  delete[] img;
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, wt, ht,  GL_RGBA, GL_UNSIGNED_BYTE, imga);
  delete[] imga;
  return true;
}

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

void DibujarAla() {
	glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texid[2]);
  
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

void DibujarMetralla()
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

void DibujarAvion() {
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

void DibujarPared() {
  glColor3f(0.9f,0.9f,0.9f);
  glPushMatrix();
  glTranslated(0,0,zPARED);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texid[0]);
  glBegin(GL_QUADS);
	glTexCoord2f(0.00, 0.66); glColor3f(1,0,0); glVertex2f(325,400);
    glTexCoord2f(0.00, 0.33); glColor3f(0,1,0); glVertex2f(475,400);
    glTexCoord2f(0.50, 0.33); glColor3f(0,0,1); glVertex2f(475,200);
    glTexCoord2f(0.50, 0.66); glColor3f(1,1,1); glVertex2f(325,200);
  glEnd();
  glDisable(GL_TEXTURE_2D);

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

	print_text(s, i, j, 10);	

	glPopMatrix();	
}

void DibujarPiso() {
  //const int w_2=1024/2, h_2=1024/2;//para que no se deforme la textura
  const int w_2=w/2, h_2=h/2;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texid[1]);
 
 glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glColor3f(1,0,0); glVertex2f(0,h);
    glTexCoord2f(1.0, 1.0); glColor3f(0,1,0); glVertex2f(w,h);
    glTexCoord2f(1.0, 0.0); glColor3f(0,0,1); glVertex2f(w,0);
    glTexCoord2f(0.0, 0.0); glColor3f(1,1,1); glVertex2f(0,0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

//============================================================
// callbacks

//------------------------------------------------------------

// arma un un nuevo buffer (back) y reemplaza el framebuffer
void Display_cb() {
  // arma el back-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// rellena con color de fondo
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glPushMatrix();
  /*
  // dibuja un punto en la posición x,y que querramos visualizar (es solo para probar)
  glColor3f(1.0f,0.0f,0.0f);
  glPointSize(5.0);
  glBegin(GL_POINTS);
  glVertex2d(50,50);
  glEnd();
  */
  
  DibujarPiso();

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

void Idle_cb() 
{
  
  static unsigned int lt=0;  	
  
  int dt = glutGet(GLUT_ELAPSED_TIME) - lt;
  
  if(dt > 60) 
  {

	  if(isFired)
	  {
		incyMetralla+=8;
		if(incyMetralla < 0 || incyMetralla > h)
			isFired = false;
	  }

	  lightY++;
	  if(lightY > 20.0)
		  lightY = 0.0;

	// Convierte AvionAng de grados a radianes
	  double ang=AvionAng*PI/180.0;
	  
	  if(teclado.Salir())
	  {
		  exit(EXIT_SUCCESS);
	  }
	  
	  if(teclado.Adelante())
	  {
		// double sin(double ang); // Calcula el seno de ang medido en radianes
		AvionX-=5*sin(ang);
		AvionY+=5*cos(ang);		
	  }

	  if(teclado.Atras())
	  {
		AvionX+=5*sin(ang);
		AvionY-=5*cos(ang);
	  }

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
  glViewport(0,0,w,h); // región donde se dibuja (toda la ventana)
  // rehace la matriz de proyección (la porcion de espacio visible)
  glMatrixMode(GL_PROJECTION);  glLoadIdentity();
  glOrtho(0,w,0,h,-1,1); // unidades = pixeles
  // las operaciones subsiguientes se aplican a la matriz de modelado GL_MODELVIEW
  glMatrixMode(GL_MODELVIEW);  
  glutPostRedisplay(); // avisa que se debe redibujar
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
  glutInitWindowSize(w,h); glutInitWindowPosition(10,10);
  glutCreateWindow("Ejemplo Avion"); // crea el main window

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
  glEnable(GL_POLYGON_OFFSET_FILL); glPolygonOffset (1,1); // coplanaridad
  glEnable(GL_POINT_SMOOTH); glEnable(GL_LINE_SMOOTH); glEnable(GL_POLYGON_SMOOTH);

  glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

  glShadeModel(GL_SMOOTH);

  // transparencias
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);  

  //glClearColor(0.23f,0.20f,0.01f,1.f); // color de fondo
  glClearColor(0.01f,0.01f,0.01f,1.f);
  
   // direccion de los poligonos
  glFrontFace(GL_CCW); glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);  
  glCullFace(GL_BACK); // se habilita por objeto (cerrado o abierto)


   // textura
  // textura1
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(3,texid);

  glBindTexture(GL_TEXTURE_2D, texid[0]);
  mipmap_ppm("cubo.ppm");
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

 /* glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);*/
  
  //Textura 2
  glBindTexture(GL_TEXTURE_2D, texid[1]);
  mipmap_ppm("grass.ppm");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    

  glBindTexture(GL_TEXTURE_2D, texid[2]);
  mipmap_ppm("pista.ppm");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 


  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
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
  cout << "f: Disparar" << endl;
  
  
  glutInit(&argc,argv); // inicialización interna de GLUT
  inicializa(); // define el estado inicial de GLUT y OpenGL
  glutMainLoop(); // entra en loop de reconocimiento de eventos
  return 0; // nunca se llega acá, es sólo para evitar un warning
}
