#ifndef DISPAROS_H
#define DISPAROS_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <list>
#include <vector>
#include "Nivel.h"
#include "ParticleSystemManager.h"
#include "TextureManager.h"
#include "SceneBase.h"

using namespace std;

class Nivel;
class SceneBase;

class Disparo: public sf::Sprite{
	private:
	
	static bool init; 				// para saber si ya cargamos o no la imagen
	float velx;						// la velocidad del disparo
	bool isNPC;

	public:
	Disparo(float x0, float y0, float vel,bool isNPC);	// constructor
	~Disparo(void);
	friend class ManejadorDisparos;	// para que ManejadorDisparos pueda acceder al miembro velx
};

// la clase se encarga de manejar todos los disparos
class ManejadorDisparos{
private:
	vector<Disparo *> disparos;								// guardamos una lista de disparos
	Nivel *nivel;
	SceneBase *scene;
public:

	ManejadorDisparos();
	void SetScene(SceneBase *scene);
	void SetLevelManager(Nivel *n);
	~ManejadorDisparos();
	void Init();
	void MoverDisparos(float dt, sf::View &v);			// mueve los disparos y revisa que esten dentro de la pantalla
	void AgregarDisparo(float x, float y, float vel,bool isNPC);	// agrega un nuevo disparo
	void DibujarDisparos(sf::RenderWindow &w);				// Dibuja todos los disparos en la ventana w
};


#endif

