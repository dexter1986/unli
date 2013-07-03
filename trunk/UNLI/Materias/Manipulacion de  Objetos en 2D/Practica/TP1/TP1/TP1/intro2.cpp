#include <GL/glut.h>

void Display_cb() {
  glFlush();  
}

int main(int argc,char** argv) {
  // Identificadores para ventanas 
  int idVentana1, idVentana2; 
  // Inicializa la libreria GLUT
  glutInit(&argc,argv);
  // Selecciona modo de display: RGB y simple buffer
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  // Fija tamaño y posición inicial de las ventanas
  glutInitWindowSize(480,360);
  glutInitWindowPosition(0,0);
  // Crea las ventanas
  glutCreateWindow ("Ventana 1");
  idVentana1=glutGetWindow();
  // Declara el callback de display
  glutDisplayFunc(Display_cb);
  
  glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
  glutInitWindowSize(200,500); glutInitWindowPosition(500,100); 
  glutCreateWindow("Ventana 2"); // crea el main window
  idVentana2=glutGetWindow();
  // Declara el callback de display
  glutDisplayFunc(Display_cb);
  
  // Setea la ventana 1 como actual
  glutSetWindow (idVentana1);  
  glutSetCursor(GLUT_CURSOR_NONE);  

  // Destruye la ventana 1
  // glutDestroyWindow (idVentana1);

  glutMainLoop(); // entra en loop de reconocimiento de eventos
  return 0;
}
