#include "SpriteSheetManager.h"
#include "TextureManager.h"

void SpriteSheetManager::Load(string filename, unsigned nCols, unsigned nRows,unsigned LevelRows,unsigned LevelCols){
	
	// cargamos 
	const sf::Image &sheet = TextureManager::GetInstance().GetTexture(filename);
	
	cols = nCols;
	rows = nRows;

	tiles.clear();
	tiles.resize(0);

	// segun la cantidad de filas/columnas calculamos el tamanio
	// de las subimagenes
	
	subimgw=sheet.GetWidth()/nCols;
	subimgh=sheet.GetHeight()/nRows;
	
	unsigned i, j;
	
	//// en temp copiaremos la parte de la imagen que buscamos
	//sf::Image temp(subimgw, subimgh);
	//
	//// descomentar la linea siguiente si no quieren interpolacion
	//temp.SetSmooth(false);
	
	for(i=0; i<rows; i++){
		for(j=0; j<cols; j++){
			// cargamos r con los datos del rectangulo
			r.Left=subimgw*j;
			r.Top=subimgh*i;
			r.Right=r.Left+subimgw;
			r.Bottom=r.Top+subimgh;
			// copiamos una porcion de la imagen a temp
			//temp.Copy(sheet, 0, 0, r);
			// e insertamos una copia de temp en el vector
			//images.push_back(temp);
			tiles.push_back(r);
		}
	}
	SetImage(sheet);
}

void SpriteSheetManager::GetImage(unsigned i,FloatRect &rect){
	SetSubRect(tiles[i]);	
	SetX(rect.Left);
	SetY(rect.Top);
}

//sf::Image &SpriteSheetManager::operator[](unsigned i){
//	return images[i];
//}

//unsigned SpriteSheetManager::Size(){
//	return images.size();
//}
