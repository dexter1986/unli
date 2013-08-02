#ifndef TECLADO_H
#define TECLADO_H
#include <GL/glut.h>

/*
	Si utilizamos el callback de teclado como lo veniamos haciendo, no podremos reconocer cuando multiples teclas se presionan.
Por este motivo (y por claridad en el codigo tambien) creamos esta clase para adquirir las pulsaciones de teclas.
El funcionamiento es bastante simple, cuando se presiona una tecla (KeyPressed_cb se llama) la marcamos en un arreglo de booleanos
como presionada. Cuando se libera (KeyReleas_cb se llama), la marcamos como no presionada. Para ver si una tecla se encuentra presionada
simplemente miramos el valor del booleano correspondiente a dicha tecla.
*/

class Teclado {
private:
	// Este arreglo tiene un booleano para cada tecla que indica si esta esta presionada o no
	static bool teclado[256];
	// Indica si se presiono la tecla esc o la combinacion alt+F4
	static bool salir;
	// Mapa de teclas
	// mapa[0] -> tecla utilizada para Disparar, mapa[1] -> tecla para avanzar, etc...
	unsigned char mapa[7];
public:
	Teclado(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char);
	
	void Iniciar();
	
	static void KeyPressed_cb(unsigned char key,int x,int y);
	static void KeyRelease_cb(unsigned char key, int x, int y);
	static void Special_cb(int key,int xm,int ym);
	
	bool Disparar( );
	bool Adelante( );
	bool Atras( );
	bool Izquierda( );
	bool Derecha( );
	bool Salir( );
};

#endif

