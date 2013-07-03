#include <GL/glut.h>

void Display_cb() {
  glFlush();  
}

void RespuestaMenuColor(int value){}
void RespuestaMenuPrincipal(int value){}

int main(int argc,char** argv) {
  // Identificador de la ventana
  int idVentana;
  
  // Inicializa la librer�a GLUT
  glutInit(&argc,argv);
  // Selecciona modo de display: RGB y simple buffer
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  // Fija tama�o y posici�n inicial de las ventanas
  glutInitWindowSize(480,360);
  glutInitWindowPosition(50,50);
  // Crea la ventana 
  idVentana=glutCreateWindow ("Ejemplo 3");
  
  // Identificadores de los men�s
  int menuColor, menuPrincipal; 
  // Crear submen� y asociarle su funci�n de respuesta
  menuColor=glutCreateMenu (RespuestaMenuColor); 
  glutAddMenuEntry("Rojo", 1);
  glutAddMenuEntry("Verde", 2);
  glutAddMenuEntry("Azul", 3);
  // Crear men� principal y asociarle su funci�n de respuesta
  menuPrincipal = glutCreateMenu(RespuestaMenuPrincipal);
  glutAddMenuEntry("Luz", 1);
  glutAddMenuEntry("Material", 2);
  glutAddSubMenu("Color", menuColor);
  // Asociar el men� al bot�n derecho del rat�n 
  glutAttachMenu(GLUT_RIGHT_BUTTON); 
  // C�digo del programa 
  // ...

  // Declara el callback de display
  glutDisplayFunc(Display_cb);

  glutMainLoop(); // entra en loop de reconocimiento de eventos
  return 0;
}
