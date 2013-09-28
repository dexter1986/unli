#ifndef SPRITESHEETMANAGER_H
#define SPRITESHEETMANAGER_H
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

class SpriteSheetManager{
private:
	vector<sf::Image> images;
	
public:
	// carga un sprite sheet
	void Load(string filename, unsigned nCols, unsigned nRows=1);
	// devuelve la imagen en la posicion i
	sf::Image &GetImage(unsigned i);
	sf::Image &operator[](unsigned i);
	// devuelve la cantidad de imagenes almacenadas
	unsigned Size();
};

#endif


