#include "Nivel.h"
#include <fstream>
#include <iomanip>


// Constructor: inicializa el Nivel
// tileset_filename: el nombre del archivo que contiene el tileset
// tileset_nw: numero de tiles de ancho del tileset
// tileset_nh: numero de tiles de alto del tileset
// levelSize_w: ancho del nivel en tiles
// levelSize_h: alto del nivel en tiles
Nivel::Nivel(string tileset_filename, int tileset_nw, int tileset_nh, unsigned levelSize_w, unsigned levelSize_h){
	// asignamos algunas variables
	levelSize.x=levelSize_w;
	levelSize.y=levelSize_h;
	this->tileset_filename=tileset_filename;
	tileSetSize.x=tileset_nw;
	tileSetSize.y=tileset_nh;
	// cargamos el tileset
	sm.Load(tileset_filename, tileSetSize.x, tileSetSize.y);
	tileSize.x=sm[0].GetWidth();
	tileSize.y=sm[0].GetHeight();
	// inicializamos la matriz de tiles
	Init();
}


// Constructor: cargar el nivel desde el archivo level_file
Nivel::Nivel(string level_file){
	Load(level_file);
}


// inicializa la matriz de tiles
void Nivel::Init(){
	// vaciamos la matriz de tiles (por las dudas si se llama
	// a Load() mas de una vez)
	tiles.clear();
	tiles.resize(0);
	
	// variables temporales para ir llenando la matriz
	// una fila y un tile
	vector<Tile> filaTemp;
	Tile tileTemp;
	
	// para calcular la posicion en pantalla de cada tile
	int posx, posy;
	
	// inicializamos la matriz
	for(unsigned i=0; i<levelSize.y; i++){
		// vaciamos la fila y le insertamos todos los tiles
		filaTemp.clear();
		for(unsigned j=0; j<levelSize.x; j++){
			// calculamos la posision del tile
			posx=j*tileSize.x;
			posy=i*tileSize.y;
			tileTemp.SetPosition(posx, posy);
			// calculamos el rectangulo que va a ocupar el tile
			tileTemp.rect.Left=posx;
			tileTemp.rect.Right=posx+tileSize.x;
			tileTemp.rect.Top=posy;
			tileTemp.rect.Bottom=posy+tileSize.y;
			
			// inicializamos el numero de imagen
			tileTemp.iImage=-1;
			
			// insertamos al tile en la fila
			filaTemp.push_back(tileTemp);
		}
		// insertamos la fila en la matriz
		tiles.push_back(filaTemp);
	}
	
	sf::Image *i=new sf::Image;
	sf::Image *j=new sf::Image;
	sf::Image *k=new sf::Image;
	sf::Image *l=new sf::Image;
	i->LoadFromFile("../data/parallax1.png");
	j->LoadFromFile("../data/parallax2.png");
	k->LoadFromFile("../data/parallax3.png");
	l->LoadFromFile("../data/parallax4.png");

	capasParallax.push_back(new ParallaxLayer(*l, 0.0005, true, 0, 0, false, -5));
	capasParallax.push_back(new ParallaxLayer(*k, 0.0015, true, 0, 0, false, 15));
	capasParallax.push_back(new ParallaxLayer(*j, 0.002, true, 0, 0, false, 40));
	capasParallax.push_back(new ParallaxLayer(*i, 0.0035, true, 0, 0, false, 110));
}


// carga un nivel desde un archivo de nivel
void Nivel::Load(string filename){
	// abrimos el archivo
	ifstream entrada(filename.c_str());
	// leemos el nombre del archivo de tilesets
	getline(entrada,tileset_filename);
	// cargamos el tamano del tileset y del nivel
	entrada>>tileSetSize.x>>tileSetSize.y;
	entrada>>levelSize.x>>levelSize.y;
	
	// cargamos el tileset
	sm.Load(tileset_filename, tileSetSize.x, tileSetSize.y);
	tileSize.x=sm[0].GetWidth();
	tileSize.y=sm[0].GetHeight();
	
	// inicializamos la matriz de tiles
	Init();
	
	// leemos la matriz de numeros de imagenes
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			entrada>>tiles[i][j].iImage;
		}
	}
	
	// leemos la matriz que nos indica cuales
	// tiles son solidos
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			entrada>>tiles[i][j].solid;
		}
	}
	// cerramos el archivo
	entrada.close();
	
	// finalmente asignamos las imagenes a los tiles
	// (si su numero de imagen es distinto de -1)
	int iImg;
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			iImg=tiles[i][j].iImage;
			if(iImg!=-1){
				tiles[i][j].SetImage(sm[iImg]);
			}
		}
	}
}


// guardamos el nivel en un archivo
void Nivel::Save(string filename){
	// abrimos el archivo de salida
	ofstream salida(filename.c_str());
	// guardamos el nombre del archivo con el tileset
	salida<<tileset_filename<<endl;
	// guardamos los tamanos del tileset y del nivel
	salida<<tileSetSize.x<<" "<<tileSetSize.y<<endl;
	salida<<levelSize.x<<" "<<levelSize.y<<endl;
	salida<<endl;
	
	// guardamos los numeros de imagen de cada tile
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			salida<<setw(3)<<tiles[i][j].iImage<<" ";
		}
		salida<<endl;
	}
	salida<<endl;
	
	// para cada tile guardamos si es o no solido
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			salida<<setw(3)<<tiles[i][j].solid<<" ";
		}
		salida<<endl;
	}
	// cerramos el archivo
	salida.close();
}

// dibuja el tilemap del nivel en la ventana w, para ello utiliza
// la funcion GetOverlappingTiles() para saber que tiles aparecen
// en la vista actual del nivel
void Nivel::Draw(sf::RenderWindow &w){
	
	for(unsigned i=0; i<capasParallax.size(); i++){
		capasParallax[i]->Draw(w);
	}
	
	vector<sf::Vector2i> _tiles;
	GetOverlappingTiles(levelView.GetRect(), _tiles);
	Tile temp;
	for(unsigned i=0; i<_tiles.size(); i++){
		temp=tiles[_tiles[i].x][_tiles[i].y];
		if(temp.iImage!=-1){
			w.Draw(temp);
		}
	}

	/*int i = 15;
	temp=tiles[_tiles[i].x][_tiles[i].y];
	if(temp.iImage!=-1){
			w.Draw(temp);
	}*/
	
}

// llena el vector ovTiles con las coordenadas de los tiles que se superponen
// con el rectangulo r, nos es util para detectar colisiones y para saber que
// tiles debemos renderizar en caso de que no estemos viendo todo el nivel
void Nivel::GetOverlappingTiles(sf::FloatRect r, vector<sf::Vector2i> &ovTiles){
	// tanto i como j comienzan con las coordenadas (en tiles) del rectangulo r
	for(int i=r.Top/tileSize.y; i<r.Bottom/tileSize.y; i++){
		for(int j=r.Left/tileSize.x; j<r.Right/tileSize.x; j++){
			ovTiles.push_back(sf::Vector2i(i, j));
		}
	}
}

// revisa si hay o no colision del rectangulo r con algun tile solido
// devuelve verdadero o falso segun haya colision o no
// devuelve en areaColision el area de interpenetracion con el tile
// en caso de haber colision con mas de un tile, devuelve
// el area de colision con el tile que tenga mayor area de colision
bool Nivel::HayColision(sf::FloatRect &r, sf::FloatRect &areaColision){
	vector<sf::Vector2i> _tiles;
	GetOverlappingTiles(r, _tiles);
	sf::FloatRect tempResp; float maxResponse=0, sresponse;
	for(unsigned i=0; i<_tiles.size(); i++){
		if(tiles[_tiles[i].x][_tiles[i].y].solid){
			if(r.Intersects(tiles[_tiles[i].x][_tiles[i].y].rect, &tempResp)){
				sresponse=tempResp.GetWidth()*tempResp.GetHeight();
				if(sresponse>maxResponse){
					maxResponse=sresponse;
					areaColision=tempResp;
				}
			}
		}
	}
	return maxResponse > 0;
}

// revisa si hay o no colision del rectangulo r con algun tile solido
// devuelve verdadero o falso segun haya colision o no
// devuelve en areaColision el area de interpenetracion con el tile
// en caso de haber colision con mas de un tile, devuelve
// el area de colision con el tile que tenga mayor area de colision
bool Nivel::HayColision2(FloatRect &r,FloatRect &collisionRec,FloatRect &areaColision)
{
	areaColision.Top = 0;
	areaColision.Bottom = 0;
	areaColision.Left = 0;
	areaColision.Right = 0;

	//Calcular los tiles de las coordenadas	
	IntRect collTiles,normalTiles;

	collTiles.Top = floor(collisionRec.Top / tileSize.y);
	collTiles.Left = floor(collisionRec.Left / tileSize.x);
	collTiles.Right = floor(collisionRec.Right / tileSize.x);
	collTiles.Bottom = floor(collisionRec.Bottom / tileSize.y);

	normalTiles.Top = floor(r.Top / tileSize.y);
	normalTiles.Left = floor(r.Left / tileSize.x);
	normalTiles.Right = floor(r.Right / tileSize.x);
	normalTiles.Bottom = floor(r.Bottom / tileSize.y);

	//Obtiene los todos los tiles incluyendo los intermedios
	vector<Vector2i> vectTiles;
	
	for(int y=collTiles.Top;y<=collTiles.Bottom;y++)
	{
		for(int x=collTiles.Left;x<=collTiles.Right;x++)
		{
			vectTiles.push_back(Vector2i(x,y));
		}
	}
	
	//Verifica si alguno de los tiles es solido
	vector<Vector2i> vectTilesCol;

	int lenght = vectTiles.size();
	for(int i=0;i<lenght;i++)
	{
		if(tiles[vectTiles[i].y][vectTiles[i].x].solid)
		{
			vectTilesCol.push_back(vectTiles[i]);
		}
	}

	//Calcula el rectangulo exterior
	lenght = vectTilesCol.size();
	
	IntRect externAABB(-1,-1,-1,-1);
	int aux_x,aux_y;
	for(int i=0;i<lenght;i++)
	{
		aux_x =  vectTilesCol[i].x;
		aux_y = vectTilesCol[i].y;

		if(aux_y < normalTiles.Top)
		{	
			externAABB.Top = aux_y - 1;			
		}
		if(aux_y > normalTiles.Bottom)
		{
			externAABB.Bottom = aux_y - 1;
		}
		if(aux_x < normalTiles.Left)
		{
			externAABB.Left = aux_x - 1;
		}
		if(aux_x > normalTiles.Right)
		{
			externAABB.Right = aux_x - 1;
		}
	}

	//Calcular los limites
	areaColision.Top =  (externAABB.Top + 1) * tileSize.y;
	areaColision.Bottom = (externAABB.Bottom + 1) * tileSize.y;
	areaColision.Left =  (externAABB.Left + 1) * tileSize.x;
	areaColision.Right =  (externAABB.Right + 1) * tileSize.y;

	if(lenght > 0)
		return true;

	return false;
	
}

// devuelve el tamano del tile
sf::Vector2i Nivel::GetTileSize(){
	return tileSize;
}

// devuelve el tamano del nivel (en cantidad de tiles)
sf::Vector2i Nivel::GetLevelSize(){
	return levelSize;
}

// devuelve la vista actual del nivel
sf::View &Nivel::GetView(){
	return levelView;
}

// Mueve el centro de la vista a las coordenadas
// (newCenter.x, newCenter.y). Si la nueva vista se
// sale del nivel, se la corrige
void Nivel::SetViewCenter(sf::Vector2f newCenter){
	// el tamano de la mitad de la vista
	sf::Vector2f halfSize=levelView.GetHalfSize();
	static sf::Vector2f oldCenter;
	
	// el tamano del nivel pero en coordenadas
	sf::Vector2f levelSizeCoords;
	levelSizeCoords.x=levelSize.x*tileSize.x;
	levelSizeCoords.y=levelSize.y*tileSize.y;
	
	// si el nuevo centro se sale fuera del nivel, lo corregimos
	if(newCenter.x-halfSize.x<0) newCenter.x=halfSize.x;
	if(newCenter.x+halfSize.x>levelSizeCoords.x) newCenter.x=levelSizeCoords.x-halfSize.x; 
	if(newCenter.y-halfSize.y<0) newCenter.y=halfSize.y;
	if(newCenter.y+halfSize.y>levelSizeCoords.y) newCenter.y=levelSizeCoords.y-halfSize.y;
	
	// actualiza las capas de parallax scrolling
	for(unsigned i=0; i<capasParallax.size(); i++){
		capasParallax[i]->SetPosition(levelView);
		capasParallax[i]->Move(-(oldCenter.x-newCenter.x), oldCenter.y-newCenter.y);
	}
	oldCenter=newCenter;
	
	// seteamos el nuevo centro de la vista
	levelView.SetCenter(newCenter);
}

// Cumple la misma funcion que ScrollView() pero suavizando el scroll
// con un factor, tambien necesitamos el tiempo transcurrido
void Nivel::SetViewCenterSmooth(sf::Vector2f newCenter, float factor, float dt){
	// conseguimos el centro actual de la vista
	sf::Vector2f oldCenter=levelView.GetCenter();
	
	// calculamos el desplazamiento como un proporcional a la diferencia
	// entre el viejo centro y el nuevo (y factor y el paso de tiempo)
	float scrollDeltax, scrollDeltay;
	scrollDeltax=(newCenter.x-oldCenter.x)*(factor*dt);
	scrollDeltay=(newCenter.y-oldCenter.y)*(factor*dt);
	
	// aplicamos el desplazamiento
	newCenter.x=oldCenter.x+scrollDeltax;
	newCenter.y=oldCenter.y+scrollDeltay;
	
	// seteamos el nuevo centro corrigiendolo si se sale fuera del nivel
	SetViewCenter(newCenter);
}

// inicializa la vista del nivel para que abarque todo el escenario
sf::View &Nivel::InitLevelView(){
	levelView=sf::View(sf::FloatRect(0,0,levelSize.x*tileSize.x, levelSize.y*tileSize.y));
	return levelView;
}

// inicializa la vista basandose en la resolucion de pantalla que utilzaremos
// y la cantidad de tiles de ancho y alto de la vista, crea la vista manteniendo
// la relacion de aspecto
sf::View &Nivel::InitLevelView(int res_x, int res_y, int tiles_x, int tiles_y){
	// si no nos especifican el tamano en tiles de la vista
	// buscamos una vista que abarque todo el nivel
	if(tiles_x<0) tiles_x=levelSize.x;
	if(tiles_y<0) tiles_y=levelSize.y;
	
	// aca vamos a guardar el tamano final de la vista (en tiles)
	float realtiles_x, realtiles_y;
	
	// la logica consiste en hacer coincidir la menor magnitud del Nivel
	// (ancho o alto) con la menor magnitud de la ventana
	
	// si la ventana es mas ancha que alta
	if(res_x>res_y){
		// buscamos la menor magnitud del nivel y ese tamano se
		// correspondera con el alto (menor tamano)
		// la magnitud restante la calculamos con regla de 3
		if(tiles_x>tiles_y){
			// el alto del nivel abarcara el alto de la ventana
			realtiles_y=tiles_y;
			realtiles_x=(res_x*tiles_y)/float(res_y);
		}else{
			// el ancho del nivel abarca el ancho de la ventana
			realtiles_x=tiles_x;
			realtiles_y=(res_y*tiles_x)/float(res_x);
		}
	}else{
		// si la ventana es mas alta que anca
		// hacemos lo mismo que antes, el menor lado de la ventana
		// le asignamos el menor lado del nivel
		if(tiles_x>tiles_y){
			// el alto del nivel abarcara el alto de la ventana 
			realtiles_y=tiles_y;
			realtiles_x=(res_y*tiles_x)/float(res_x);
		}else{
			// el ancho del nivel abarca el ancho de la ventana
			realtiles_x=tiles_x;
			realtiles_y=(res_y*tiles_x)/float(res_x);
		}
	}
	// seteamos la vista del nivel y hacemos un scroll para inicializarla/acomodarla
	levelView.SetHalfSize(sf::Vector2f(realtiles_x*tileSize.x/2.0, realtiles_y*tileSize.y/2.0));
	SetViewCenter(sf::Vector2f(0,0));
	return levelView;
}

// dibuja una grilla sobre los tiles
void Nivel::DrawGrid(sf::RenderWindow &w){
	// coordenadas de la vista actual en tiles
	int x1, y1, x2, y2;
	sf::FloatRect r=levelView.GetRect();
	x1=r.Left/tileSize.x;
	x2=(r.Right/tileSize.x)+1;
	y1=r.Top/tileSize.y;
	y2=(r.Bottom/tileSize.y)+1;
	
	// dibuja las lineas verticales
	for(unsigned i=x1; i<=x2; i++){
		sf::Shape Line = sf::Shape::Line(i*tileSize.x, y1*tileSize.y, i*tileSize.x, y2*tileSize.y, 1, sf::Color(255,255,255));
		w.Draw(Line);
	}

	// dibuja las lineas horizontales
	for(unsigned i=y1; i<=y2; i++){
		sf::Shape Line = sf::Shape::Line(x1*tileSize.x, i*tileSize.y, x2*tileSize.x, i*tileSize.y, 1, sf::Color(255,255,255));
		w.Draw(Line);
	}
}

// genera y guarda una imagen con el tilemap
void Nivel::SaveToImage(string filename){
	// crea una imagen
	sf::Image imagen(levelSize.x*tileSize.x, levelSize.y*tileSize.y, sf::Color(0, 0, 0, 0));
	// dibuja los tiles en la imagen
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			if(tiles[i][j].iImage!=-1){
				imagen.Copy(sm[tiles[i][j].iImage], j*tileSize.x, i*tileSize.y);
			}
		}
	}
	// guarda la imagen
	imagen.SaveToFile(filename);
}

