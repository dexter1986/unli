#include <GL/glut.h>

void Display_cb() {
  // envia al monitor la pantalla vac�a
  glutSwapBuffers();
}

int main(int argc,char** argv) {
  // Inicializa la librer�a GLUT
  glutInit(&argc,argv);
  // Selecciona modo de display: RGB y double buffering
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
  // Fija tama�o y posici�n inicial de las ventanas
  glutInitWindowSize(480,360);
  glutInitWindowPosition(50,50);
  glutCreateWindow("Ejemplo 4");
  //declara los callbacks
  glutDisplayFunc(Display_cb);
  glutMainLoop(); // entra en loop de reconocimiento de eventos
  return 0;
}
