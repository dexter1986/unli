#ifndef SPRITESHEETMANAGER_H
#define SPRITESHEETMANAGER_H
#include <vector>
#include <SFML/Graphics/Sprite.hpp>

using namespace std;
using namespace sf;

class SpriteSheetManager : public Sprite {
private:
	unsigned subimgw, subimgh;
	vector<sf::IntRect> tiles;
	//vector<sf::Image> images;
	sf::IntRect r;
	unsigned cols, rows; 
public:
	// carga un sprite sheet
	void Load(string filename, unsigned nCols, unsigned nRows=1,unsigned LevelRows=1,unsigned LevelCols=1);
	// devuelve la imagen en la posicion i
	void GetImage(unsigned i,FloatRect &rect);
	const Image& InternalImage();
	//sf::Image &operator[](unsigned i);
	// devuelve la cantidad de imagenes almacenadas
	//unsigned Size();
};

#endif


