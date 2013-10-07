#ifndef NIVEL_H
#define NIVEL_H

#include <iostream>
#include <vector>
#include "SpriteSheetManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ParallaxLayer.h"
using namespace std;
using namespace sf;

class Nivel{
private:
	// la estructura para representar un tile
	class Tile: public sf::Sprite{
	public:
		int iImage;			// el numero de imagen
		bool solid;			// si se puede chocar con el tile
		sf::FloatRect rect; // para facilitar la deteccion de colisiones
	};
	
	// nombre del archivo tileset
	string tileset_filename;
	// manejador de las imagenes del tileset
	SpriteSheetManager sm;
	// la matriz (o vector de vectores) de tiles
	vector< vector<Tile> > tiles;
	// tamano del nivel en tiles (ancho x alto)
	sf::Vector2i levelSize;
	// tamano del tileset en tiles (ancho x alto)
	sf::Vector2i tileSetSize;
	// tamano de los tiles (ancho x alto)
	sf::Vector2i tileSize;
	
	// la vista del nivel
	sf::View levelView;
	
	vector<ParallaxLayer *> capasParallax;
	
	
	// inicializa la matriz de tiles
	void Init();
	
	// nos da los tiles que se solapan con el rectangulo r
	// (para detectar colisiones e evitar dibujar todo el escenario)
	void GetOverlappingTiles(sf::FloatRect r, vector<sf::Vector2i> &_tiles);
	
public:
	// constructores
	Nivel(string tileset_file, int ntilesx, int ntilesy, unsigned levelSize_w, unsigned levelSize_h);
	Nivel(string level_file);
	
	// salvar y guardar un nivel
	void Load(string file);
	void Save(string file);
	
	// tamano de tiles y del nivel
	sf::Vector2i GetTileSize();
	sf::Vector2i GetLevelSize();
	
	// dibujar el nivel en pantalla
	void Draw(sf::RenderWindow &w);
	
	// probar si hay colision del nivel con el rectangulo r
	bool HayColision(sf::FloatRect &r, sf::FloatRect &areaColision);
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

