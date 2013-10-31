#include "Nivel.h"
#include <fstream>
#include <iomanip>

Nivel::Nivel()
{
}

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
	sm.Load(tileset_filename, tileSetSize.x, tileSetSize.y,levelSize.x,levelSize.y);
	sm.GetImage(0,FloatRect());
	Vector2f size = sm.GetSize();
	tileSize.x= size.x;
	tileSize.y= size.y;
	
	// inicializamos la matriz de tiles
	Init();
}

// Constructor: cargar el nivel desde el archivo level_file
Nivel::Nivel(string level_file){
	Load(level_file);
}

// inicializa la matriz de tiles
void Nivel::Init(){
	isNeedNextLoadLevel = false;
	fileNextLevel = "";
	iPortales = 0;
	iEnemigos = 0;
	
	// vaciamos la matriz de tiles (por las dudas si se llama
	// a Load() mas de una vez)
	tiles.clear();
	tiles.resize(0);

	tiles_overlayer.clear();
	tiles_overlayer.resize(0);
	
	nextLevels.clear();
	nextLevels.resize(0);

	// variables temporales para ir llenando la matriz
	// una fila y un tile
	vector<Tile> filaTemp;
	Tile tileTemp;
	

	//vaciamos las capas parallax
	for(int i=0;i<capasParallax.size();i++)
	{
		delete capasParallax[i];
	}

	capasParallax.clear();
	capasParallax.resize(0);

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
			tileTemp.iOverLayer=-1;
			tileTemp.isAnim=false;
			tileTemp.isBomb=false;
			tileTemp.iPortal=-1;
			tileTemp.iEnemigo = -1;
			tileTemp.isEntryPoint = false;			
			tileTemp.solid = false;
			tileTemp.iType = -1;
						
			// insertamos al tile en la fila
			filaTemp.push_back(tileTemp);
		}
		// insertamos la fila en la matriz
		tiles.push_back(filaTemp);
		tiles_overlayer.push_back(filaTemp);
	}
	
	/*sf::Image *i=new sf::Image;
	sf::Image *j=new sf::Image;
	sf::Image *k=new sf::Image;*/
	sf::Image *l=new sf::Image;
	/*i->LoadFromFile("../data/parallax1.png");*/
	/*i->LoadFromFile("../data/parallax5.png");*/
	/*j->LoadFromFile("../data/parallax2.png");*/
	/*k->LoadFromFile("../data/parallax3.png");*/
	/*l->LoadFromFile("../data/parallax4.png");*/
	/*i->LoadFromFile("../data/parallax6.png");
	j->LoadFromFile("../data/parallax7.png");*/
	//l->LoadFromFile("../data/parallax8.png");
	//l->LoadFromFile("../data/parallax-1-800x200.png");
	

	/*capasParallax.push_back(new ParallaxLayer(*l, 0.0005, true, 0, 0, false, -5));*/
	
	//capasParallax.push_back(new ParallaxLayer(*i, 0.001, true, 0, 0, false, 0));
	//capasParallax.push_back(new ParallaxLayer(*j, 0.001, true, 0, 0, false, 30));
	/*capasParallax.push_back(new ParallaxLayer(*l, 0.000, false, 0, 0, true, 40));*/
	//capasParallax.push_back(new ParallaxLayer(*l, 0.001, true, 0, 0.0001, false, 0));
	
	/*capasParallax.push_back(new ParallaxLayer(*k, 0.0015, true, 0, 0, false, 15));
	capasParallax.push_back(new ParallaxLayer(*j, 0.002, true, 0, 0, false, 40));
	capasParallax.push_back(new ParallaxLayer(*i, 0.0035, true, 0, 0, false, 110));*/

	/*capasParallax.push_back(new ParallaxLayer(*l, 0.0035, true, 0, 0, false, 0));*/

	const int len = 2;
	char *archivosCapas[]={ "../data/parallax-1-800x200.png",
							"../data/parallax-2-800x120.png"};
	
	// cargamos las imagenes de las capas
	/*sf::Image imgCapas[len];
	for(unsigned i=0; i<len; i++)
	{
		imgCapas[i].LoadFromFile(archivosCapas[i]);
	}*/
	
	//l->LoadFromFile("../data/parallax-1-800x200.png");

	// los offsets y velocidades de las capas
	float offsetYCapas[]={0,20,110};
	float offsetXCapas[]={0,0,0};
	/*float offsetYCapas[]={0,10,20,30,40};*/
	float velCapas[]={0.0010, 0.0015, 0.0015};
	
	// inicializamos las capas del parallax
	const sf::Image *img;
	//ParallaxLayer *capas[len];
	for(unsigned i=0; i<len; i++)
	{	 
		 img = &TextureManager::GetInstance().GetTexture(archivosCapas[i]);		
		 capasParallax.push_back(new ParallaxLayer(*img, velCapas[i], true, offsetXCapas[i],
												    0, false, offsetYCapas[i]));
	}

	
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
	sm.Load(tileset_filename, tileSetSize.x, tileSetSize.y,levelSize.x,levelSize.y);
	//tileSize.x=sm[0].GetWidth();
	//tileSize.y=sm[0].GetHeight();

	sm.GetImage(0,FloatRect());
	Vector2f size = sm.GetSize();
	tileSize.x= size.x;
	tileSize.y= size.y;
	
	// inicializamos la matriz de tiles
	Init();
	
	int aux = 0;

	// leemos la matriz de numeros de imagenes
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			entrada>>aux;
			tiles[i][j].iImage = aux-1;			
		}
	}
	
	//01 solid
	//03 bomb
	//70 Enemigo
	//10-20 portal
	//99 Enter Point
	// leemos la matriz que nos indica cuales
	// tiles son solidos
	aux = 0;
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			entrada>>aux;
			if(aux == 1)
			{
				tiles[i][j].solid = true;
			}
			else if(aux == 3)
			{
				tiles[i][j].isBomb = true;				
			}
			else if(aux >= 10 && aux <= 20)
			{
				iPortales++;
				tiles[i][j].iPortal = aux;
			}
			else if(aux == 70)
			{
				iEnemigos++;
				tiles[i][j].iEnemigo = aux;
			}
			else if(aux == 99)
			{
				tiles[i][j].isEntryPoint = true;
				vEntryPoint.x = tileSize.x * j;
				vEntryPoint.y = tileSize.y * i;

			}
		}
	}


	// leemos la matriz que nos indica cuales
	// tiles son overlay
	aux = 0;
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			entrada>>aux;
			tiles_overlayer[i][j].iOverLayer = aux-1;
		}
	}
	aux = 0;
	string file;
	Level templevel;
	//Cargamos los link a los niveles
	for(unsigned i=0; i<iPortales; i++){		
		entrada>>aux;
		entrada>>file;
		templevel.index = aux;
		templevel.file = file;
		nextLevels.push_back(templevel);
	}

	// cerramos el archivo
	entrada.close();
	
	//// finalmente asignamos las imagenes a los tiles
	//// (si su numero de imagen es distinto de -1)
	//int iImg;
	//for(unsigned i=0; i<levelSize.y; i++){
	//	for(unsigned j=0; j<levelSize.x; j++){
	//		iImg=tiles[i][j].iImage;
	//		if(iImg!=-1){
	//			tiles[i][j].SetImage(sm[iImg]);
	//		}
	//		iImg=tiles_overlayer[i][j].iOverLayer;
	//		if(iImg!=-1){
	//			tiles_overlayer[i][j].SetImage(sm[iImg]);
	//		}
	//	}
	//}
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
	
	vector<sf::Vector2i *> *_tiles = new  vector<sf::Vector2i *>();
	GetOverlappingTiles(levelView.GetRect(), *_tiles);
	
	for(unsigned i=0; i<_tiles->size(); i++){		
		Tile &temp=tiles[(*_tiles)[i]->x][(*_tiles)[i]->y];		
		if(temp.iImage != -1)
		{
			sm.GetImage(temp.iImage,temp.rect);
			w.Draw(sm);			
		}
	}

	/*int i = 15;
	temp=tiles[_tiles[i].x][_tiles[i].y];
	if(temp.iImage!=-1){
			w.Draw(temp);
	}*/

	for(unsigned i=0; i<_tiles->size(); i++)
	{
		delete (*_tiles)[i];
	}
	_tiles->clear();
	delete _tiles;
	
}

void Nivel::DrawOverLayer(sf::RenderWindow &w)
{
	vector<sf::Vector2i *> *_tiles = new vector<sf::Vector2i *>();
	GetOverlappingTiles(levelView.GetRect(), *_tiles);
	
	for(unsigned i=0; i<_tiles->size(); i++){
		Tile &temp=tiles_overlayer[(*_tiles)[i]->x][(*_tiles)[i]->y];		
		if(temp.iOverLayer != -1)
		{
			sm.GetImage(temp.iOverLayer,temp.rect);
			w.Draw(sm);
		}
	}

	for(unsigned i=0; i<_tiles->size(); i++)
	{
		delete (*_tiles)[i];
	}
	_tiles->clear();
	delete _tiles;
}

// llena el vector ovTiles con las coordenadas de los tiles que se superponen
// con el rectangulo r, nos es util para detectar colisiones y para saber que
// tiles debemos renderizar en caso de que no estemos viendo todo el nivel
void Nivel::GetOverlappingTiles(sf::FloatRect r, vector<sf::Vector2i *> &ovTiles){
	// tanto i como j comienzan con las coordenadas (en tiles) del rectangulo r
	float xo = r.Top/tileSize.y;
	float xf = r.Bottom/tileSize.y;
	float yo = r.Left/tileSize.x;
	float yf = r.Right/tileSize.x;

	for(int i=xo; i<xf; i++){
		for(int j=yo; j<yf; j++){
			if( i >= 0 && j >= 0)
			{
				ovTiles.push_back(new sf::Vector2i(i, j));
			}
		}
	}
}

// revisa si hay o no colision del rectangulo r con algun tile solido
// devuelve verdadero o falso segun haya colision o no
// devuelve en areaColision el area de interpenetracion con el tile
// en caso de haber colision con mas de un tile, devuelve
// el area de colision con el tile que tenga mayor area de colision
bool Nivel::HayColision(sf::FloatRect &r, sf::FloatRect &areaColision,int &tipo,bool isNPC){
	vector<sf::Vector2i *> *_tiles = new vector<sf::Vector2i *>();
	GetOverlappingTiles(r, *_tiles);
	sf::FloatRect tempResp; float maxResponse=0, sresponse;
	int x,y;
	for(unsigned i=0; i<_tiles->size(); i++){		
		x = (*_tiles)[i]->x;
		y = (*_tiles)[i]->y;
		if(x > -1 && x < levelSize.y && y < levelSize.x  && y > -1)
		{
			//Tile &tile = tiles[_tiles[i].x][_tiles[i].y];
			Tile &tile = tiles[x][y];
			if(!isNPC)
			{
				if(tile.isBomb)
				{
					tipo = 3;
					return true;
				}
				else if(tile.iPortal != -1)
				{
					tipo = tile.iPortal;
					if(!isNeedNextLoadLevel)
					{
						isNeedNextLoadLevel = true;
						for(int i=0;i<iPortales;i++)
						{
							if(nextLevels[i].index == tipo)
							{
								fileNextLevel = nextLevels[i].file;
							}
						}
					}					
					return true;
				}
			}
			
			if(tiles[x][y].solid)
			{
				if(r.Intersects(tiles[x][y].rect, &tempResp))
				{
					sresponse=tempResp.GetWidth()*tempResp.GetHeight();
					if(sresponse>maxResponse)
					{
						maxResponse=sresponse;
						areaColision=tempResp;
					}
				}
			}
		}
	}


	for(unsigned i=0; i<_tiles->size(); i++)
	{
		delete (*_tiles)[i];
	}
	_tiles->clear();
	delete _tiles;

	return maxResponse > 0;
}

bool Nivel::HayColision(float x, float y,int &tipo)
{
	int xo = x / tileSize.y;
	int yo = y / tileSize.x;
	if(xo >= 0 && yo >= 0 && xo < levelSize.x && yo < levelSize.y)
	{
		Tile &tile = tiles[yo][xo];
		if(tile.solid)
		{			
			return true;
		}
	}
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
	if(newCenter.x-halfSize.x<0) 
		newCenter.x=halfSize.x;
	if(newCenter.x+halfSize.x>levelSizeCoords.x) 
		newCenter.x=levelSizeCoords.x-halfSize.x; 
	if(newCenter.y-halfSize.y<0) 
		newCenter.y=halfSize.y;
	if(newCenter.y+halfSize.y > levelSizeCoords.y) 
		newCenter.y=levelSizeCoords.y-halfSize.y;
	
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
		// si la ventana es mas alta que ancha
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
				//imagen.Copy(sm[tiles[i][j].iImage], j*tileSize.x, i*tileSize.y);
			}
		}
	}
	// guarda la imagen
	imagen.SaveToFile(filename);
}

