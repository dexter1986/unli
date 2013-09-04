#include "TiledSprite.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;

TiledSprite::TiledSprite(const string &filename, unsigned nCols, unsigned nRows){
	// pide al TextureManager una referencia a la textura especificada
	const sf::Image &tex = TextureManager::GetInstance().GetTexture(filename);
	// asigna la textura al sprite
	SetImage(tex);
	// guarda la cantidad de filas y columnas (se van a necesitar más tarde para calcular el subrectángulo)
	this->nCols=nCols;
	this->nRows=nRows;
	// calcula el ancho y alto del tile
	tileW=tex.GetWidth()/nCols;
	tileH=tex.GetHeight()/nRows;
	// se pone mCurrentTileIndex en -1 para que al llamar a SetTileIndex() en la linea siguiente,
	// este valor se altere (debe inicializarse en otro valor != 0)
	mCurrentTileIndex=-1; 
	// asigna al sprite el primer tile del spritesheet
	SetTileIndex(0);
}


void TiledSprite::SetTileIndex(unsigned i){
	// solo modifica si el nuevo número o índice de tile es != del actual
	if(i!=mCurrentTileIndex){
		mCurrentTileIndex=i;
		// calcula las coordenadas del subrectangulo donde se encuentra el tile deseado
		int left, top, bottom, right;
		left=((mCurrentTileIndex%nCols)*tileW);
		top=((mCurrentTileIndex/nCols)*tileH);
		right=left+tileW;
		bottom=top+tileH;
		// indica que no debe utilizarse la textura entera para el dibujado, sino la region con el tile seleccionado
		SetSubRect(sf::IntRect(left, top, right, bottom));
	}
}

unsigned TiledSprite::GetTileIndex() const {
	return mCurrentTileIndex;
}
