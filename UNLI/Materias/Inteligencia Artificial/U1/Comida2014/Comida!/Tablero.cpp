#include "Tablero.h"
#include "utils.h"


Tablero::Tablero(int nhormigas, int nmatadores, int ncomida, int _width, int _height)
{

	width=_width;
	height=_height;

	m_fuente.loadFromFile("arial.ttf");
	
	m_imBackground.loadFromFile("back.png");
	m_sprBackground.setTexture(m_imBackground);

	for( int i=0;i<nhormigas;++i){
		Hormiga* h= new Hormiga(this);
		//agregamos la hormiga a la lista
		//de las cosas que se dibujan
		//y a la lista de las cosas que se
		//actualizan
		m_pGraphics.push_back(h);
		m_pLogics.push_back(h);
		m_pHormigas.push_back(h);
	}

	for( int i=0;i<nmatadores;++i){
		Matador* m= new Matador(this);
		//agregamos al matador a la lista
		//de las cosas que se dibujan
		//y a la lista de las cosas que se
		//actualizan
		m_pGraphics.push_back(m);
		m_pLogics.push_back(m);
		m_pMatadores.push_back(m);
	}


	for( int i=0;i<ncomida;++i){
		Comida* m= new Comida();
		//agregamos al matador a la lista
		//de las cosas que se dibujan solamente
		m_pGraphics.push_back(m);
		m_pComida.push_back(m);
		
	}


}

void Tablero::Draw(RenderWindow* wnd){

	//draw background
	wnd->draw(m_sprBackground);

	for(unsigned int i=0;i<m_pGraphics.size();++i)
		m_pGraphics[i]->Draw(wnd);


}

void Tablero::Update(){


	for(unsigned int i=0;i<m_pLogics.size();++i)
		m_pLogics[i]->Update();

	CheckRules();
}

void Tablero::CheckRules(){

	//miramos sino se salio alguno de los participantes
	Vector2f pos;
	for(unsigned int i=0;i<m_pMatadores.size();++i){
		pos=m_pMatadores[i]->GetPosition();
		if(pos.x>width)
			pos.x=(float)width;
		if(pos.x<0)
			pos.x=0.0f;
		if(pos.y>height)
			pos.y=(float)height;
		if(pos.y<0)
			pos.y=0.0f;

		m_pMatadores[i]->SetPosition(pos);
	}

	for(unsigned int i=0;i<m_pHormigas.size();++i){
		pos=m_pHormigas[i]->GetPosition();
		if(pos.x>width)
			pos.x=(float)width;
		if(pos.x<0)
			pos.x=0.0f;
		if(pos.y>height)
			pos.y=(float)height;
		if(pos.y<0)
			pos.y=0.0f;

		m_pHormigas[i]->SetPosition(pos);
	}

}

Tablero::~Tablero(void)
{

}


Matador* Tablero::GetClosestMatador(Hormiga* h){

	float minDist=(float)INT_MAX;
	float dist;
	Matador* closest=NULL;

	for(unsigned int i=0;i<m_pMatadores.size();++i){
		dist = Utils::GetVecDistance(h->GetPosition(), m_pMatadores[i]->GetPosition());
		if(dist<minDist){
			minDist=dist;
			closest=m_pMatadores[i];
		}

	}

	return closest;

}

void Tablero::KillHormiga(Hormiga* h){

	 
	m_pHormigas.erase(std::find(m_pHormigas.begin(),m_pHormigas.end(),h));
	m_pLogics.erase(std::find(m_pLogics.begin(),m_pLogics.end(),(UpdateBase*)h));
	m_pGraphics.erase(std::find(m_pGraphics.begin(),m_pGraphics.end(),(DrawBase*)h));

	delete h;

	h = NULL;
	
}
void Tablero::KillMatador(Matador* m){

	m_pMatadores.erase(std::find(m_pMatadores.begin(),m_pMatadores.end(),m));
	m_pLogics.erase(std::find(m_pLogics.begin(),m_pLogics.end(),(UpdateBase*)m));
	m_pGraphics.erase(std::find(m_pGraphics.begin(),m_pGraphics.end(),(DrawBase*)m));

	delete m;

	m = NULL;
}
void Tablero::EatComida(Comida *c)
{
	m_pComida.erase(std::find(m_pComida.begin(), m_pComida.end(), c));	
	m_pGraphics.erase(std::find(m_pGraphics.begin(), m_pGraphics.end(), (DrawBase*)c));

	delete c;

	c = NULL;
}

Hormiga* Tablero::GetClosestHormiga(Matador* m){

	float minDist=(float)INT_MAX;
	float dist;
	Hormiga* closest=NULL;

	for(unsigned int i=0;i<m_pHormigas.size();++i){
		dist = Utils::GetVecDistance(m->GetPosition(), m_pHormigas[i]->GetPosition());
		if(dist<minDist){
			minDist=dist;
			closest=m_pHormigas[i];
		}

	}

	return closest;

}

Comida*  Tablero::GetNearestVisibleFood(Hormiga *h){

	float minDist=(float)INT_MAX;
	float dist;
	Comida* closest=NULL;

	for(unsigned int i=0;i<m_pComida.size();++i){
		dist = Utils::GetVecDistance(h->GetPosition(), m_pComida[i]->GetPosition());
		if(dist<minDist){
			minDist=dist;
			closest=m_pComida[i];
		}

	}

	return closest;


}