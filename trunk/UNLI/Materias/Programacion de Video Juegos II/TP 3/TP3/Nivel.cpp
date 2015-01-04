#include "Nivel.h"
#include <fstream>
#include <iomanip>

Nivel::Nivel()
{	
	occlusion_tiles = NULL;
	isDebug = false;
	irKeys[0]  = 0;
	irKeys[1]  = 0;
	irKeys[2]  = 0;
	irKeys[3]  = 0;
	irKeys[4]  = 0;	
	iKeys = 5;	
}

/*
// Constructor: inicializa el Nivel
// tileset_filename: el nombre del archivo que contiene el tileset
// tileset_nw: numero de tiles de ancho del tileset
// tileset_nh: numero de tiles de alto del tileset
// levelSize_w: ancho del nivel en tiles
// levelSize_h: alto del nivel en tiles
Nivel::Nivel(string tileset_filename, int tileset_nw, int tileset_nh, unsigned levelSize_w, unsigned levelSize_h)
{
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
	
	tileSize.x=(int)size.x;
	tileSize.y= (int)size.y;

	occlusion_tiles = NULL;
	irKeys[0]  = 0;
	irKeys[1]  = 0;
	irKeys[2]  = 0;
	irKeys[3]  = 0;
	irKeys[4]  = 0;	
	iKeys = 5;
	isDebug = false;
	// inicializamos la matriz de tiles
	Init();
}
*/
/*
// Constructor: cargar el nivel desde el archivo level_file
Nivel::Nivel(string level_file)
{	
	Load(level_file);
}
*/
void Nivel::GetOcclusionTiles()
{
	if(occlusion_tiles != NULL)
	{
		for(unsigned i=0; i<occlusion_tiles->size(); i++)
		{
			delete (*occlusion_tiles)[i];
		}
		occlusion_tiles->clear();
		delete occlusion_tiles;
	}
	occlusion_tiles = new  vector<sf::Vector2i *>();	

	GetOverlappingTiles(levelView.GetRect(), *occlusion_tiles);
}

void Nivel::PrepareNivel()
{
	GetOcclusionTiles();
}

// inicializa la matriz de tiles
void Nivel::Init(){
	isGameWon = false;
	isNeedNextLoadLevel = false;

	fileNextLevel = "";
	iPortales = 0;
	iEnemigos = 0;	
	// vaciamos la matriz de tiles (por las dudas si se llama
	// a Load() mas de una vez)
	tiles.clear();
	tiles.resize(0);

	for(int i=0;i<nextLevels.size();i++)
	{	
		delete nextLevels[i];
	}

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
	for(unsigned y=0; y<levelSize.y; y++){
		// vaciamos la fila y le insertamos todos los tiles
		filaTemp.clear();
		for(unsigned x=0; x<levelSize.x; x++){
			// calculamos la posision del tile
			posx=x*tileSize.x;
			posy=y*tileSize.y;
			tileTemp.SetPosition((float)posx,(float) posy);
			// calculamos el rectangulo que va a ocupar el tile
			tileTemp.rect.Left=(float)posx;
			tileTemp.rect.Right=(float)posx+tileSize.x;
			tileTemp.rect.Top=(float)posy;
			tileTemp.rect.Bottom=(float)posy+tileSize.y;
			
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
			tileTemp.isDead = false;
			tileTemp.isKey = false;
			tileTemp.iKey = -1;
			tileTemp.isDynamic = false;
			tileTemp.isKeyBomb = false;
			// insertamos al tile en la fila
			filaTemp.push_back(tileTemp);
		}
		// insertamos la fila en la matriz
		tiles.push_back(filaTemp);		
	}	
	
	sf::Image *l=new sf::Image;
	
	const int len = 2;
	
	// los offsets y velocidades de las capas
	float offsetYCapas[]={0,20,110};
	float offsetXCapas[]={0,0,0};	
	float velCapas[]={0.0010f, 0.0015f, 0.0015f};
	
	// inicializamos las capas del parallax
	const sf::Image *img;

	//ParallaxLayer *capas[len];
	for(unsigned i=0; i<len; i++)
	{	 
		 img = &TextureManager::GetInstance().GetTexture(capasparalaxFiles[i]);		
		 capasParallax.push_back(new ParallaxLayer(*img, velCapas[i], true, offsetXCapas[i],
												    0, false, offsetYCapas[i]));
	}
}

// carga un nivel desde un archivo de nivel
void Nivel::Load(string filename,bool reload){
	
	// abrimos el archivo
	ifstream entrada(filename.c_str());

	getline(entrada,name);

	// leemos el nombre del archivo de tilesets
	getline(entrada,tileset_filename);
	//Cargamos el paralax
	entrada>>capasparalaxFiles[0];
	entrada>>capasparalaxFiles[1];
	
	// cargamos el tamano del tileset y del nivel
	entrada>>tileSetSize.x>>tileSetSize.y;
	entrada>>levelSize.x>>levelSize.y;
	
	// cargamos el tileset
	sm.Load(tileset_filename, tileSetSize.x, tileSetSize.y,levelSize.x,levelSize.y);
	//tileSize.x=sm[0].GetWidth();
	//tileSize.y=sm[0].GetHeight();

	sm.GetImage(0,FloatRect());
	Vector2f size = sm.GetSize();
	tileSize.x=(int) size.x;
	tileSize.y= (int)size.y;
	
	// inicializamos la matriz de tiles
	Init();

	if(reload)
	{
		isNeedNextLoadLevel = true;
	}

	int aux = 0;

	//leemos la matriz de numeros de imagenes
	for(unsigned y=0; y<levelSize.y; y++){
		for(unsigned x=0; x<levelSize.x; x++){
			entrada>>aux;
			tiles[y][x].iImage = aux-1;			
		}
	}
	
	//01 solid
	//03 bomb		
	//10-19 portal
	//20-29 recolectable -> 20,21,22,23,24 -> son las claves
	//60-69 Enemigo
	//88 Key Bomb
	//99 Enter Point - es donde aparece el player
	//100 solid - floor
	//101 solid - wall
	//102 solid - ceiling
	// leemos la matriz que nos indica cuales
	// tiles son solidos
	aux = 0;
	for(unsigned y=0; y<levelSize.y; y++){
		for(unsigned x=0; x<levelSize.x; x++){
			entrada>>aux;
			if(aux == 1)
			{
				tiles[y][x].solid = true;
			}			
			else if(aux == 3)
			{
				tiles[y][x].isBomb = true;				
			}
			else if(aux >= 10 && aux <= 19)
			{
				iPortales++;
				tiles[y][x].iPortal = aux;
			}
			else if(aux >= 20 && aux <= 29)
			{					
				tiles[y][x].isKey = true;
				tiles[y][x].iKey = aux - 20;
				tiles[y][x].isDynamic = true;
				if(irKeys[tiles[y][x].iKey] != 0)
				{
					tiles[y][x].isDead = true;
				}
			}
			else if(aux >= 60 && aux <= 69)
			{
				iEnemigos++;
				tiles[y][x].iEnemigo = aux - 60;
				//if(!isDebug)
					//ptrAgregarEnemigo(tileSize.x * j,tileSize.y * i,tiles[i][j].iEnemigo);
			}
			else if(aux == 88)
			{				
				tiles[y][x].isDynamic = true;
				tiles[y][x].isKeyBomb = true;
			}
			else if(aux == 99)
			{
				tiles[y][x].isEntryPoint = true;
				vEntryPoint.x = tileSize.x * x;
				vEntryPoint.y = tileSize.y * y;
			}
			else if(aux == 100)
			{
				tiles[y][x].solid = true;
				tiles[y][x].floor = true;
			}
			else if(aux == 101)
			{
				tiles[y][x].solid = true;
				tiles[y][x].wall = true;
			}
			else if(aux == 102)
			{
				tiles[y][x].solid = true;
				tiles[y][x].ceiling = true;
			}
		}
	}
	// leemos la matriz que nos indica cuales
	// tiles son overlay
	aux = 0;
	for(unsigned y=0; y<levelSize.y; y++)
	{
		for(unsigned x=0; x<levelSize.x; x++){
			entrada>>aux;			
			tiles[y][x].iOverLayer = aux-1;
		}
	}

	aux = 0;
	string file;
	Level *templevel = NULL;

	//Cargamos los link a los niveles
	for(unsigned i=0; i<iPortales; i++){		
		entrada>>aux;
		entrada>>file;
		templevel = new	Level();
		templevel->index = aux;
		templevel->file = file;
		nextLevels.push_back(templevel);
	}

	// cerramos el archivo
	entrada.close();
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
void Nivel::Draw(sf::RenderWindow &w)
{
	
	for(unsigned i=0; i<capasParallax.size(); i++){
		capasParallax[i]->Draw(w);
	}	
	for(unsigned i=0; i<occlusion_tiles->size(); i++)
	{		
		Tile &temp=tiles[(*occlusion_tiles)[i]->y][(*occlusion_tiles)[i]->x];		
	
		if(temp.iImage != -1 )//&& !temp.isDead)
		{
			sm.GetImage(temp.iImage,temp.rect);
			w.Draw(sm);			
		}

	}
}

void Nivel::DrawOverLayer(sf::RenderWindow &w)
{	
	for(unsigned i=0; i<occlusion_tiles->size(); i++){
		Tile &temp=tiles[(*occlusion_tiles)[i]->y][(*occlusion_tiles)[i]->x];		
		if(temp.iOverLayer != -1 && !temp.isDead)
		{	
			sm.GetImage(temp.iOverLayer,temp.rect);
			w.Draw(sm);
		}
	}	
	
}

// llena el vector ovTiles con las coordenadas de los tiles que se superponen
// con el rectangulo r, nos es util para detectar colisiones y para saber que
// tiles debemos renderizar en caso de que no estemos viendo todo el nivel
void Nivel::GetOverlappingTiles(sf::FloatRect r, vector<sf::Vector2i *> &ovTiles){
	// tanto i como j comienzan con las coordenadas (en tiles) del rectangulo r
	
	float xo = r.Left/tileSize.x;
	float xf = r.Right/tileSize.x;

	float yo = r.Top/tileSize.y;
	float yf = r.Bottom/tileSize.y;

	for(int x=xo; x<xf; x++)
	{
		for(int y=yo; y<yf; y++)
		{
			if( x >= 0 && y >= 0)
			{
				ovTiles.push_back(new sf::Vector2i(x, y));
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
	
	sf::FloatRect tempResp; 
	float maxResponse=0;
	float sresponse = 0;
	int x = 0;
	int y = 0;
	bool ret = false;
	for(unsigned i=0; i<_tiles->size(); i++)
	{		
		if(ret)
		{
			break;
		}
		x = (*_tiles)[i]->x;
		y = (*_tiles)[i]->y;
		if(y > -1 && y < levelSize.y && x < levelSize.x  && x > -1)
		{	
			Tile *tile = &tiles[y][x];			
			if(tile->isDead)
			{
				continue;
			}

			if(tile->solid || tile->isBomb || tile->isKeyBomb)
			{
				if(r.Intersects(tile->rect, &tempResp))
				{
					sresponse = tempResp.GetWidth() * tempResp.GetHeight();
					if( sresponse > maxResponse )
					{
						maxResponse=sresponse;
						areaColision=tempResp;
					}
				}
			}

			if(!isNPC)
			{
				if(tile->isBomb)
				{
					tipo = 3;
					tile->isDead = true;
					ret = true;
				}
				else if(tile->isDynamic)
				{
					if(tile->isKey)
					{
						tipo = 1;
						tile->isDead = true;
						iKeys--;
						irKeys[tile->iKey] = 1;
						ret = true;
					}
					else if(tile->isKeyBomb)
					{
						tipo = 2;
						if(iKeys == 0)
						{
							tipo = 4;
							isGameWon = true;
							tile->isDead = true;
						}						
					}
				}
				else if(tile->iPortal != -1)
				{
					tipo = tile->iPortal;
					/*if(!isNeedNextLoadLevel)
					{
						isNeedNextLoadLevel = true;
						for(int i=0;i<iPortales;i++)
						{
							if(nextLevels[i]->index == tipo)
							{
								fileNextLevel = nextLevels[i]->file;
							}
						}
					}*/					
					ret = true;
				}				
			}
		}
		else
		{
			cout<<"Out of Level limits";
		}

	}


	for(unsigned i=0; i<_tiles->size(); i++)
	{
		delete (*_tiles)[i];
	}

	_tiles->clear();
	
	delete _tiles;

	if(ret)
	{
		return true;
	}
	else
	{
		return maxResponse > 0;
	}
}

bool Nivel::HayColision2(FloatRect &r,FloatRect &cr,FloatRect &areaColision)
{
	vector<sf::Vector2i *> *_tiles = new vector<sf::Vector2i *>();	
	
	float xo = cr.Left/tileSize.x;
	float xf = cr.Right/tileSize.x;

	float yo = cr.Top/tileSize.y;
	float yf = cr.Bottom/tileSize.y;

	for(int x=xo; x<xf; x++)
	{
		for(int y=yo; y<yf; y++)
		{
			if( x >= 0 && y >= 0)
			{
				_tiles->push_back(new sf::Vector2i(x, y));
			}
		}
	}

	sf::FloatRect tempResp; 
	float maxResponse=0;
	float sresponse = 0;
	int x = 0;
	int y = 0;
	bool ret = false;

	for(unsigned i=0; i<_tiles->size(); i++)
	{	
		x = (*_tiles)[i]->x;
		y = (*_tiles)[i]->y;
		if(y > -1 && y < levelSize.y && x < levelSize.x  && x > -1)
		{	
			Tile *tile = &tiles[y][x];			
			if(tile->isDead)
			{
				continue;
			}

			if(tile->solid)
			{
				if(r.Intersects(tile->rect, &tempResp))
				{
					sresponse = tempResp.GetWidth() * tempResp.GetHeight();
					if( sresponse > maxResponse )
					{
						maxResponse=sresponse;
						areaColision=tempResp;
					}
				}
			}			
		}
		else
		{
			cout<<"Out of Level limits";
		}
	}

	for(unsigned i=0; i<_tiles->size(); i++)
	{
		delete (*_tiles)[i];
	}

	_tiles->clear();
	
	delete _tiles;

	return ret;
}

void Nivel::SetGameWonDelegate(void (*gamewon)(void))
{
	gamewon_delegate = gamewon;
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
sf::Vector2f Nivel::GetTileSize(){
	return tileSize;
}

// devuelve el tamano del nivel (en cantidad de tiles)
sf::Vector2f Nivel::GetLevelSize(){
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
	levelView.SetHalfSize(sf::Vector2f(realtiles_x*tileSize.x*0.5f, realtiles_y*tileSize.y*0.5f));
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
				sm.GetImage(tiles[i][j].iImage,tiles[i][j].rect);			
				imagen.Copy(sm.InternalImage(), j*tileSize.x, i*tileSize.y);
			}
		}
	}
	// guarda la imagen
	imagen.SaveToFile(filename);
}

Nivel::~Nivel()
{
	for(int i=0;i<nextLevels.size();i++)
	{	
		delete nextLevels[i];
	}

	nextLevels.clear();

	//vaciamos las capas parallax
	for(int i=0;i<capasParallax.size();i++)
	{
		delete capasParallax[i];
	}

	capasParallax.clear();
	capasParallax.resize(0);
}
