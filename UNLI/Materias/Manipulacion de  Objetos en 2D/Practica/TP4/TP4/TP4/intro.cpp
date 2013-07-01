// Ejemplo 4
// triángulo con tres puntos editables

#include <iostream> // cout
#include <cstdlib> // exit
#include <cmath> // fabs
#include "GL/glut.h"

using namespace std;

//------------------------------------------------------------
// variables globales
int
  w=480,h=360, // tamaño inicial de la ventana
  npuntos=0, // cantidad de puntos
  pt[6], // los puntos (hasta 3: x0,y0,x1,y1,x2,y2)
  ep=-1; // índice del punto a editar

//============================================================
// callbacks

//------------------------------------------------------------

// arma un un nuevo buffer (back) y reemplaza el framebuffer
void Display_cb() {
  //static int counter=0; cout << "display: " << counter++ << endl;

  // arma el back-buffer
  glClear(GL_COLOR_BUFFER_BIT);// rellena con color de fondo

  if (!npuntos){ // no hay nada
    glutSwapBuffers(); // manda al monitor la pantalla vacía
    return;
  }

  // dibuja
  int i;
  // triángulo (sólo si ya están los tres puntos)
  if (npuntos==3) {
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); glLineWidth(2);
    glColor3f(.4f,.6f,.8f);
    glBegin(GL_TRIANGLES);
      for(i=0;i<npuntos;i++) glVertex2i(pt[2*i],pt[2*i+1]);
    glEnd();
  }
  // puntos (después del triángulo, para que se vean encima)
  glColor3f(.1f,.2f,.3f);
  glPointSize(5.0); // punto grueso
  glBegin(GL_POINTS);
    for(i=0;i<npuntos;i++) glVertex2i(pt[2*i],pt[2*i+1]);
  glEnd();

  glutSwapBuffers(); // lo manda al monitor
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
  glutPostRedisplay(); // avisa que se debe redibujar
}

//------------------------------------------------------------
// Mouse

// Seguimiento del cursor
void PassiveMotion_cb(int x, int y){
  y=h-y; // el 0 está arriba
  cout << x << "," << y << "                    \r" << flush;
}

// Drag (movimiento con algun boton apretado)
void Motion_cb(int x, int y){
  y=h-y; // el 0 está arriba
  //cout << x << "," << y << endl;
  pt[2*ep]=x;pt[2*ep+1]=y; // fija el punto editado en x,y
  glutPostRedisplay(); // avisa que se debe redibujar
}

// Botones picados o soltados
void Mouse_cb(int button, int state, int x, int y){
  
  cout << x << "," << y << "," << button << endl;
  if (button==GLUT_LEFT_BUTTON){ // boton izquierdo
    if (state==GLUT_DOWN) { // clickeado
      y=h-y; // el 0 está arriba
      //cout << x << "," << y << endl;
      ep=-1;
      // verifica si picó a menos de 5 pixeles de algún punto previo
      for (int i=0;i<npuntos;i++){
        int d=sqrt(pow(float(x-pt[2*i]),2)+pow(float(y-pt[2*i+1]),2)); // distancia euclidea
        if (d>5) continue; // lejos
        ep=i; // edita el punto i
        glutMotionFunc(Motion_cb); // define el callback para los drags
        return;
      }
      // no pico cerca de otro
      if (npuntos==3) return; // ya hay 3 ==> no hace nada
      // agrega un punto
      pt[2*npuntos]=x; pt[2*npuntos+1]=y; npuntos++;
      Display_cb(); // Redibuja
      // y queda listo para editarlo hasta que suelte el botón izquierdo
      ep=npuntos-1; // edita el ultimo punto
      glutMotionFunc(Motion_cb); // define el callback para los drags
    } // fin clickeado
    else if (state==GLUT_UP) // soltado
      glutMotionFunc(0); // anula el callback para los drags
  } // fin botón izquierdo
}

//------------------------------------------------------------
// Teclado

// Maneja pulsaciones del teclado (ASCII keys)
// x,y posicion del mouse cuando se teclea (aqui no importan)
void Keyboard_cb(unsigned char key,int x,int y) {
  if (key==127||key==8){ // DEL o Backspace ==> borra el punto ep (el editable)
    if (ep==-1||ep==npuntos) return;
    // corre los siguientes hacia atras
    for(int i=ep;i<npuntos-1;i++) {pt[2*i]=pt[2*i+2];pt[2*i+1]=pt[2*i+3];}
    npuntos--;
    glutPostRedisplay(); // avisa que se debe redibujar
    // Backspace borra para atras, DEL borra para adelante
    if (key==8) ep--; // ep pasa a ser el anterior
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
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);// pide color RGB y double buffering
  glutInitWindowSize(w,h); glutInitWindowPosition(50,50);
  glutCreateWindow("Ejemplo 4"); // crea el main window

  //declara los callbacks, los que (aun) no se usan (aun) no se declaran
  glutDisplayFunc(Display_cb);
  glutReshapeFunc(Reshape_cb);
  glutKeyboardFunc(Keyboard_cb);
  glutSpecialFunc(Special_cb);
  glutMouseFunc(Mouse_cb);
   glutPassiveMotionFunc(PassiveMotion_cb);

  // OpenGL
  glClearColor(0.85f,0.9f,0.95f,1.f); // color de fondo
  glMatrixMode(GL_MODELVIEW); glLoadIdentity(); // constante
}

//------------------------------------------------------------
// main
int main(int argc,char** argv) {
  glutInit(&argc,argv); // inicialización interna de GLUT
  inicializa(); // define el estado inicial de GLUT y OpenGL
  glutMainLoop(); // entra en loop de reconocimiento de eventos
  return 0; // nunca se llega acá, es sólo para evitar un warning
}
