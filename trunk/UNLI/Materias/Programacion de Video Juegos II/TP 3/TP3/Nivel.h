#ifndef NIVEL_H
#define NIVEL_H

#include <iostream>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "SpriteSheetManager.h"
#include "ParallaxLayer.h"
#include "AnimatedBase.h"

using namespace std;
using namespace sf;

namespace Tiletype
{
	enum Tiletype
	{
		NOTHING = 0,
		SOLID = 1
	};
};

class Nivel{
private:
	
	class Tile : public Sprite
	{	
		public:			
		int iImage;			// el numero de imagen
		bool solid;			// si se puede chocar con el tile
		int  iPortal;	//indice si es una puerta a otro nivel
		bool isBomb; // indica si es una bomba
		int iOverLayer; //indica si debe pintarse sobre
		bool isAnim; //indica si esta animado
		int iEnemigo; //indica si es un enemigo
		bool isEntryPoint; //punto en el cual aparece el personaje cuando empieza el nivel
		int iType; //
		sf::FloatRect rect; // para facilitar la deteccion de colisiones
		bool isDead;
	};

	class Level
	{
		public:
		int index;
		string file;
	};
	
	int iPortales;
	int iEnemigos;
	
	string capasparalaxFiles[2];

	// nombre del archivo tileset
	string tileset_filename;
	// manejador de las imagenes del tileset
	SpriteSheetManager sm;
	// la matriz (o vector de vectores) de tiles
	vector<vector<Tile>>tiles;
	
	// la matriz (o vector de vectores) de tiles
	vector<vector<Tile>>tiles_overlayer;

	//Matriz con los jump a los 
	//otro niveles
	vector<Level> nextLevels;

	// tamano del nivel en tiles (ancho x alto)
	sf::Vector2i levelSize;
	// tamano del tileset en tiles (ancho x alto)
	sf::Vector2i tileSetSize;
	// tamano de los tiles (ancho x alto)
	sf::Vector2i tileSize;
	
	

	vector<ParallaxLayer *> capasParallax;

	vector<sf::Vector2i *> *occlusion_tiles;
	
	// inicializa la matriz de tiles
	void Init();
	
	// nos da los tiles que se solapan con el rectangulo r
	// (para detectar colisiones e evitar dibujar todo el escenario)
	void GetOverlappingTiles(sf::FloatRect r, vector<sf::Vector2i *> &_tiles);
	
	//
	void GetOcclusionTiles();
	//
	void (*agregarEnemigo_entities)(float x, float y,int tipo);
public:
	// la vista del nivel
	sf::View levelView;

	bool isNeedNextLoadLevel;
	string fileNextLevel;

	Vector2f vEntryPoint;
	
	// constructores
	Nivel(string tileset_file, int ntilesx, int ntilesy, unsigned levelSize_w, unsigned levelSize_h);
	Nivel(string level_file);
	Nivel();
	// salvar y guardar un nivel
	void Load(string file);
	void Save(string file);
	
	// tamano de tiles y del nivel
	sf::Vector2i GetTileSize();
	sf::Vector2i GetLevelSize();
	
	// dibujar el nivel en pantalla
	void Draw(sf::RenderWindow &w);
	void DrawOverLayer(sf::RenderWindow &w);
	
	void PrepareNivel();

	void SetEnemigoManagerDelegate(void (*agregarEnemigo)(float x, float y,int tipo));

	// probar si hay colision del nivel con el rectangulo r
	bool HayColision(sf::FloatRect &r, sf::FloatRect &areaColision,int &tipo,bool isNPC);
	bool HayColision(float x, float y,int &tipo);
	bool HayColision2(FloatRect &r,FloatRect &collisionRec,FloatRect &areaColision);
	
	// funciones para inicializar la vista
	sf::View &InitLevelView(int res_x, int res_y, int tiles_x=-1, int tiles_y=-1);
	sf::View &InitLevelView();
	
	// funciones para realizar scrolling
	void ScrollView(sf::Vector2f newCenter);
	void ScrollViewSmooth(sf::Vector2f newCenter, float factor, float dt);
	
	// algunas funciones utiles
	void DrawGrid(sf::RenderWindow &w);
	void SaveToImage(string filename);
	
	// devuelve la vista del nivel
	sf::View &GetView();
	// mueve la vista (realiza scrolling)
	void SetViewCenter(sf::Vector2f newCenter);
	// mueve la vista de forma suave
	void SetViewCenterSmooth(sf::Vector2f newCenter, float factor, float dt);
};

#endif


