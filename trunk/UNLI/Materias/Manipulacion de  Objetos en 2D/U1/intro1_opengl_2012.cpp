#include <GL/glut.h>

void Display_cb() {
  glFlush();  
}

int main(int argc,char** argv) {
  // Inicializa la librería GLUT
  glutInit(&argc,argv); 
  // Selecciona modo de display: RGB y simple buffer
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  // Fija tamaño y posición inicial de las ventanas
  glutInitWindowSize(480,360);
  glutInitWindowPosition(50,50);
  // Crea la ventana 
  glutCreateWindow ("Ejemplo 1");

  // Declara el callback de display
  glutDisplayFunc(Display_cb);

  glutMainLoop(); // entra en loop de reconocimiento de eventos
  return 0;
}
