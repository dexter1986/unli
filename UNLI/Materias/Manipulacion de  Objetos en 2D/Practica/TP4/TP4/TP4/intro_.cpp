#include "GL/glut.h"

int main(int argc,char** argv) {
  // Inicializa la librer�a GLUT
  glutInit(&argc,argv);
  // Selecciona modo de display: RGB y simple buffer
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  // Fija tama�o y posici�n inicial de las ventanas
  glutInitWindowSize(480,360);
  glutInitWindowPosition(50,50);
  return 0;
}
