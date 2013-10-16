#include "SpriteSheetManager.h"
#include "TextureManager.h"

void SpriteSheetManager::Load(string filename, unsigned nCols, unsigned nRows){
	
	// cargamos 
	const sf::Image &sheet = TextureManager::GetInstance().GetTexture(filename);
	
	// segun la cantidad de filas/columnas calculamos el tamanio
	// de las subimagenes
	unsigned subimgw, subimgh;
	subimgw=sheet.GetWidth()/nCols;
	subimgh=sheet.GetHeight()/nRows;
	
	unsigned i, j;
	// r contendra la region de la imagen que nos interesa
	sf::IntRect r;
	// en temp copiaremos la parte de la imagen que buscamos
	sf::Image temp(subimgw, subimgh);
	
	// descomentar la linea siguiente si no quieren interpolacion
	temp.SetSmooth(false);
	
	for(i=0; i<nRows; i++){
		for(j=0; j<nCols; j++){
			// cargamos r con los datos del rectangulo
			r.Left=subimgw*j;
			r.Top=subimgh*i;
			r.Right=r.Left+subimgw;
			r.Bottom=r.Top+subimgh;
			// copiamos una porcion de la imagen a temp
			temp.Copy(sheet, 0, 0, r);
			// e insertamos una copia de temp en el vector
			images.push_back(temp);
		}
	}
}

sf::Image &SpriteSheetManager::GetImage(unsigned i){
	return images[i];
}

sf::Image &SpriteSheetManager::operator[](unsigned i){
	return images[i];
}

unsigned SpriteSheetManager::Size(){
	return images.size();
}
