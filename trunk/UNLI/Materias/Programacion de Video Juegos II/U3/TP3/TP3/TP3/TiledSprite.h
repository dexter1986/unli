#ifndef TILEDSPRITE_H
#define TILEDSPRITE_H
#include <SFML/Graphics.hpp>

/**
 * Representa un sprite cuya imagen asociada corresponde a un spritesheet/tileset.
 * Para crear el sprite es necesario especificar la cantidad de filas/columnas de tiles
 * que existen en la imagen dada.
 * El sprite se dibujará utilizando uno de los tiles de la imagen, el cual se especificará
 * mediante un valor entero.
 */
class TiledSprite: public sf::Sprite {
	public:
		
	/**
	 * \brief	constructor: crea un TiledSprite a partir de la imagen, especificando
	 *			la cantidad de filas y columnas de tiles en los que está dividida la imagen
	 * \param	filename nombre del archivo de imagen del spritesheet
	 * \param	nCols cantidad de columnas del spritesheet
	 * \param	nRows cantidad de filas del spritesheet
	 */
	TiledSprite(const std::string &filename, unsigned nCols, unsigned nRows=1);
		
		
	/**
	 * \brief	cambia el tile actual con el que se dibuja el Sprite
	 * \param	i índice del tile actual (va desde 0 a (nCols*nRows)-1
	 * \see		GetTileIndex
	 */
	void SetTileIndex(unsigned i);
	
	/**
	 * \brief	devuelve el índice del tile actual
	 * \return	índice correspondiente al tile actual
	 */
	unsigned GetTileIndex() const;
	
	private:
	unsigned tileW, tileH;			///< ancho y alto de cada tile
	unsigned nRows, nCols;			///< cantidad de filas/columnas del spritesheet
	unsigned mCurrentTileIndex;		///< indice del tile actual
};
#endif

