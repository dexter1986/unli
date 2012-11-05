#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[]) {
	
	char z[5][18]={"Santa Fe","Entre R¡os","C¢rdoba","Salta","Chaco"};
	//Observen que z es una matríz de char, en este caso está definida con 18
	//columnas que nos dice que la mayor cadena que puede contener es de 17
	//caracteres (hay que reservar uno para el \0
	//z tiene 5 lineas, cada linea representa una cadena a la cual accedemos,
	//por ejemplo para la primera z[0], si lo que queremos es acceder al primer
	//caracter de la segunda cadena haríamos z[1][0]
	//Así si solo contemplamos el primer indice estaríamos ante un vector de
	//Cstring, si contemplamos los dos indices estariamos ante una matriz de char
	
	for (int i=0; i<5; i++)
		puts( z[i] ); //muestra un cstring por l?nea
	puts (z[2]); //obtiene "C?rdoba" en la salida
	cout<<z[3]<<endl;//también funciona con cout
	cout<<z[1][0]<<endl; //accedemos al primer caracter de la segunda cadena
	
	
	return 0;
}
