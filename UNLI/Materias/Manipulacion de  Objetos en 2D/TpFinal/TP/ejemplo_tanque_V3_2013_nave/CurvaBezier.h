#pragma once

#include <vector>
#include <string>
#include <cmath>

#include <GL/glut.h>
extern const double PI;
//Clase que represeta un color mediante el espacio de colores rgb
class Color
{
public:
	Color(float val_r, float val_g, float val_b): r(val_r), g(val_g), b(val_b)
	{}

	float r,g,b;
};

//Clase que representa un vector o punto en 2D
class Vector
{
public:
	Vector(): x(0.0f), y(0.0f)
	{}

	Vector(float val_x, float val_y): x(val_x), y(val_y)
	{}

	float x, y;
};

//Funcion auxiliar para dibujar texto
void print_text(std::string cadena, int x, int y, int espacio=10);

//Funcion auxiliar para dibujar un circulo
void _DibujarCirculo(Color color, Vector posicion, float radio, int LOD);




//Clase que representa una curva de Bezier en 2D
//Pudiendo esta curva ser de cualquier grado N, teniendo en ese caso N+1 puntos(orden N+1)
//Permite evaluar la curva mediante el algoritmo estable de De Casteljau
//y mediante calculo directo de los polinomios de Bernstein(el cual no es numericamente estable)
class CurvaBezier
{
public:
	//Tipo de metodo de evaluacion a usar para la curva
	//- UsarDeCasteljau    -> evalua la curva usando el algoritmo de este nombre
	//- UsarCalculoDirecto -> evalua la curva calculando los polinomios de Bernstein de forma directa
	enum TipoDeEvaluacion{UsarDeCasteljau,UsarCalculoDirecto};

private:
	//Puntos de control de la curva
	//				Nota: vector es una clase de C++ que permite trabajar con un arreglo de forma "facil",
	//				es decir podemos insertar objetos en el arreglo y este se redimensiona solo, podemos borrar
	//				y este se ordena solo
	std::vector<Vector> m_PuntosControl;

	//Tipo de evaluacion usandose actualmente en la curva
	TipoDeEvaluacion          m_TipoEvaluacion;

	//Funcion auxiliar
	//Calcula el factorial del entero k que se le pasa(lo hace de la forma mas ineficiente posible.. o casi)
	int Factorial(int k);

	//Evalua los polinomios de Bernstein de forma directa
	//Depende de Factorial(int k)
	float EvaluarBernstein(float t, int i, int N);

	//Evalua el punto de la curva en el tiempo t usando el metodo directo
	Vector EvaluarCurvaDirectamente(float t);

	//Evalua el punto de la curva en el tiempo t usando DeCasteljau
	Vector EvaluarCurvaDeCasteljau(float t);

public:
	CurvaBezier();

	~CurvaBezier();

	void SetTipoEvaluacion(TipoDeEvaluacion tipo);

	TipoDeEvaluacion GetTipoEvaluacion();

	//Obtiene un puntero al punto de control de la curva que esta mas cercano al punto pasado,
	//y que a su vez esta a menor distancia que minDistancia
	//Si no existe un punto tan cercano luego devuelve NULL
	Vector* GetPuntoControlCercano(Vector punto, float minDistancia);

	//Agrega un punto de control a la curva
	void AgregarPuntoControl(Vector PC);

	//Borra el ultimo punto de control de la curva
	void EliminarUltimoPuntoControl();

	//Evalua el punto de la curva en el tiempo t
	//El metodo que se utilize puede verse y cambiarse usando SetTipoEvaluacion y GetTipoEvaluacion
	Vector Evaluar(float t);

	//Dibuja la curva de Bezier
	//LOD es el nivel de detalle con el que se dibujara la curva, es decir
	//la cantidad de lineas que poseera la poligonal que aproxima la curva
	void Dibujar(int LOD);

	//Dibuja los polinomios base de Bernstein
	//LOD es el nivel de detalle con el que se dibujaran las funciones base, es decir
	//la cantidad de lineas que poseera la poligonal que aproxima la funcion
	void DibujarFuncionBase(float AnchoVentana, float AltoVentana, int LOD);

	//Dibuja el proceso grafico del algoritmo de DeCasteljau
	//t es el parametro en el cual se evalua la curva con el algoritmo
	void DibujarMetodoDeCasteljau(float t);
};
