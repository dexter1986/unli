#pragma once
#include "stdafx.h"
#include "Drawable.h"
#include "Hormiga.h"
#include "Comida.h"
#include "Matador.h"
#include <vector>
using namespace sf;
using namespace std;

class Tablero : public DrawBase, public UpdateBase
{

	friend class Hormiga;
	friend class Matador;

	Texture m_imBackground;
	Sprite m_sprBackground;

	int width;
	int height;

	//vectores de clases base
	//para dibujar y actualizar
	vector<DrawBase*> m_pGraphics;
	vector<UpdateBase*> m_pLogics;


	//vectores de tipos hijos
	//para busquedas. Nos evita
	//casts excesivos
	vector<Hormiga*> m_pHormigas;
	vector<Matador*> m_pMatadores;
	vector<Comida*> m_pComida;


	Font m_fuente;

public:
	void Draw(RenderWindow* wnd);
	void Update();	

	Matador* GetClosestMatador(Hormiga* h);
	Hormiga* GetClosestHormiga(Matador* m);
	Comida*  GetNearestVisibleFood(Hormiga *h);
	void	 CheckRules();
	void	 KillHormiga(Hormiga *h);
	void	 KillMatador(Matador *m);
	void	 EatComida(Comida *c);
	Tablero(int nhormigas, int nmatadores, int ncomida, int _width, int _height);
	~Tablero(void);
};

