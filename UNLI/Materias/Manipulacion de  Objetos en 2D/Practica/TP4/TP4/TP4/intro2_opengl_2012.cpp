#include <GL/glut.h>

using namespace std;

void myInit(void){
  // Selecciona el color de fondo 
  glClearColor(0.85f,0.9f,0.95f,1.f);
  // El color a dibujar
  glColor3f(1.0f, 0.0f, 0.0f);
  // Tamaño de los puntos
  glPointSize(5.0);
  glMatrixMode (GL_PROJECTION); 
  glLoadIdentity();
  glOrtho(0.0, 480.0, 0.0, 360.0,-1,1);
}

void Display_cb() {
  // Limpia la pantalla
  glClear(GL_COLOR_BUFFER_BIT);
  // Dibuja los dos puntos
  glBegin(GL_POINTS); 
    glVertex2i(100, 50); 
    glVertex2i(100, 130); 
  glEnd();
  // Envia toda la salida al monitor
  glFlush();  
}

int main(int argc,char** argv) {
  glutInit(&argc,argv); 
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  glutInitWindowSize(480,360);
  glutInitWindowPosition(50,50);
  glutCreateWindow ("Ejemplo 2");
  // Declara el callback de display
  glutDisplayFunc(Display_cb);
  myInit();
  glutMainLoop();
  return 0;
}
