#include "CurvaBezier.h"
#include <limits>

void print_text(std::string cadena, int x, int y, int espacio){
	for(unsigned int i=0; i < cadena.size(); i++) {
		glRasterPos2i( x + i*espacio, y );
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,(int)cadena[i]);//GLUT_BITMAP_9_BY_15//GLUT_BITMAP_TIMES_ROMAN_10
	}
}

void _DibujarCirculo(Color color, Vector posicion, float radio, int LOD)
{
	glColor3f(color.r,color.g,color.b);
	glPushMatrix();
	
	glTranslated(posicion.x,posicion.y,0);
	glScaled(radio,radio,1);

	double dx = (2*PI)/(LOD-1);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2d(0,0);
		for(double x=0; x<(2*PI); x+=dx) 
			glVertex2d(cos(x),sin(x));
	glEnd();

	glPopMatrix();
}

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

CurvaBezier::CurvaBezier(): m_TipoEvaluacion(UsarDeCasteljau)
{}

CurvaBezier::~CurvaBezier()
{
	m_PuntosControl.clear();//limpiamos el vector de los PC
}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

void CurvaBezier::SetTipoEvaluacion(TipoDeEvaluacion tipo)
{
	m_TipoEvaluacion = tipo;
}

CurvaBezier::TipoDeEvaluacion CurvaBezier::GetTipoEvaluacion()
{
	return m_TipoEvaluacion;
}

Vector* CurvaBezier::GetPuntoControlCercano(Vector punto, float minDistancia)
{
	float minDst = std::numeric_limits<float>::max();
	int minIndx = -1;
	for(unsigned int i=0; i < m_PuntosControl.size() ; ++i)
	{
		float aux1 = m_PuntosControl[i].x-punto.x;
		float aux2 = m_PuntosControl[i].y-punto.y;
		float dst = sqrt(aux1*aux1 + aux2*aux2);//Distancia Euclidea
		if( dst < minDst )
		{
			minDst = dst;
			minIndx = i;
		}
	}
	if( minDst < minDistancia )
		return &m_PuntosControl[minIndx];
	else
		return NULL;
}

int CurvaBezier::Factorial(int k)
{
	//Implmentacion extremadamente ineficiente para calcular
	//un factorial pero tambien la mas directa
	int res=1;
	for(int i=2;i <= k;++i)
		res *= i;
	return res;
}

float CurvaBezier::EvaluarBernstein(float t, int i, int N)
{
	int aux1 = Factorial(N);
	int aux2 = Factorial(i);
	int aux3 = Factorial(N-i);

	return (aux1*pow(t,i)*pow(1-t,N-i))/(float)(aux2*aux3);
}

Vector CurvaBezier::EvaluarCurvaDirectamente(float t)
{
	Vector aux(0.0f,0.0f);
	int N = m_PuntosControl.size()-1;
	for(unsigned int i=0; i < m_PuntosControl.size() ; ++i)//por cada punto de control se pesa y se suma
	{
		aux.x += EvaluarBernstein(t,i,N)*m_PuntosControl[i].x;
		aux.y += EvaluarBernstein(t,i,N)*m_PuntosControl[i].y;
	}
	return aux;
}

Vector CurvaBezier::EvaluarCurvaDeCasteljau(float t)
{
	Vector* Q = new Vector[m_PuntosControl.size()];
	int N = m_PuntosControl.size()-1;

	for(int i=0; i <= N ; ++i)
		Q[i] = m_PuntosControl[i]; // primera columna de la cuña
	for(int k=1; k <= N ; ++k)//por cada columna siguiente de la cuña
		for(int i=0; i <= (N-k); ++i)
		{
			Q[i].x = (1 - t)*Q[i].x + t*Q[i+1].x;//calculo del punto C en el ratio (1-t):t
			Q[i].y = (1 - t)*Q[i].y + t*Q[i+1].y;
		}

	Vector res = Q[0];//punto de la curva a tiempo t
	delete[] Q;
	return res;
}

void CurvaBezier::AgregarPuntoControl(Vector PC)
{
	m_PuntosControl.push_back(PC);//la funcion agrega PC al final del vector
}

void CurvaBezier::EliminarUltimoPuntoControl()
{
	if( m_PuntosControl.size() > 0 )//si hay puntos
		m_PuntosControl.erase(m_PuntosControl.begin()+m_PuntosControl.size()-1);//la funcion borra el ultimo PC del vector
}

Vector CurvaBezier::Evaluar(float t)
{
	switch(m_TipoEvaluacion)
	{
	case UsarDeCasteljau:
		return EvaluarCurvaDeCasteljau(t);
		break;
	case UsarCalculoDirecto:
		return EvaluarCurvaDirectamente(t);
		break;
	}
	return Vector(-1,-1);//si devuelve esto es porque m_TipoEvaluacion tiene un valor no permitido
}

void CurvaBezier::Dibujar(int LOD)
{
	//Graficamos los puntos de control(PC)
	for(unsigned int k=0; k < m_PuntosControl.size() ; ++k)
		_DibujarCirculo(Color(1.0f,0.0f,0.0f), m_PuntosControl[k], 5.0f, 2*PI/(0.25f));

	if( m_PuntosControl.size() < 2)
		return;
	std::vector<Vector> puntos;

	//Calculamos los puntos a graficar en la curva
	float dt = 1.0f/(LOD-1);
	for(int k=0; k < LOD ; ++k)
	{
		float t = dt*k;
		if( t>=1 )
			t -= 0.00001;
		puntos.push_back( Evaluar(t) );
	}

	//Graficamos la curva propiamente dicha(en realidad una aproximacion con lineas claro)
	glColor3f(1.0f,1.0f,0.0f);
	glBegin(GL_LINES);
	for(int k=1; k < LOD ; ++k)
	{
		glVertex3f(puntos[k].x  ,puntos[k].y  ,0.f);
		glVertex3f(puntos[k-1].x,puntos[k-1].y,0.f);
	}
	glEnd();

	return;
}

void CurvaBezier::DibujarFuncionBase(float AnchoVentana, float AltoVentana, int LOD)
{
	//Un vector de colores para elegir para cada funcion base
	Color Colores[]={Color(0.0f,0.0f,1.0f)/*Azul*/,Color(1.0f,1.0f,0.0f)/*Amarillo*/,Color(1.0f,0.0f,0.0f)/*Rojo*/,Color(0.0f,1.0f,0.0f)/*Verde*/,
		Color(1.0f,0.0f,1.0f)/*Magenta*/,Color(0.0f,1.0f,1.0f)/*Cian*/, Color(1.0f,1.0f,1.0f)/*Blaco*/};

	float& h = AltoVentana;//Nota: el nombre de la variable es muy largo por eso usamos otras que se llaman h y w
	float& w = AnchoVentana;

	//Por cada punto de control tenemos una funcion base -> Por cada funcion base
	for(unsigned int b=0; b < m_PuntosControl.size() ; ++b)
	{
		//Calculamos valores de la funcion base
		float dt = 1.0f/(LOD-1);
		std::vector<float> puntos;//seran valores de una funcion base
		for(int k=0; k < LOD ; ++k)
		{
			float t = dt*k;
			puntos.push_back(EvaluarBernstein(t, b, m_PuntosControl.size()-1));
		}
		//Graficamos la funcion base
		glBegin(GL_LINES);
		for(int k=1; k < LOD ; ++k)
		{
			float t = dt*k;

			glColor3f(Colores[b%7].r,Colores[b%7].g,Colores[b%7].b);
			
			Vector aux = Vector((t-dt)*w,puntos[k-1]*h);
			glVertex3f(aux.x  ,aux.y  ,0.f);
			aux = Vector(t*w,puntos[k]*h);
			glVertex3f(aux.x,aux.y,0.f);
		}
		glEnd();
	}
}

void CurvaBezier::DibujarMetodoDeCasteljau(float t)
{
	Vector* Q = new Vector[m_PuntosControl.size()];
	int N = m_PuntosControl.size()-1;

	//Dibujamos la leyenda de los Puntos de Control
	glColor3f(1.0f,1.0f,1.0f);
	for(int i=0; i <= N ; ++i)
	{
		Q[i] = m_PuntosControl[i]; // primera columna de la cuña
		std::string texto="A";
		texto[0]+=i;
		print_text(texto, Q[i].x+10, Q[i].y);
	}

	//Dibujamos los poligonos de control y los puntos intermedios
	for(int k=1; k <= N ; ++k)//por cada columna siguiente de la cuña
		for(int i=0; i <= (N-k); ++i)
		{
			//Nota: Tener tantos glBegin y glEnd no es eficiente, pero
			//como se ahorraba un par de lineas se lo realizo asi
			glColor3f(1.0f,1.0f,1.0f);
			glBegin(GL_LINES);
			glVertex3f(Q[i].x   ,Q[i].y    ,0.f);
			glVertex3f(Q[i+1].x ,Q[i+1].y  ,0.f);
			glEnd();

			Q[i].x = (1 - t)*Q[i].x + t*Q[i+1].x;//calculo del punto C en el ratio (1-t):t
			Q[i].y = (1 - t)*Q[i].y + t*Q[i+1].y;

			_DibujarCirculo(Color(255,0,255), Q[i], 4.0f, 2*PI/(0.25f));
		}

	delete[] Q;
}
