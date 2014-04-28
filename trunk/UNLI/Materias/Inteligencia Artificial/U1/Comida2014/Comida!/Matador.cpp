#include "Matador.h"
#include "MatadorStates.h"
#include "Tablero.h"
#include "utils.h"

Matador::Matador(Tablero *tab): tablero(tab)
{

	//cargamos los recursos de SFML
	m_img.loadFromFile("osos.png");
	m_spr.setTexture(m_img);
	m_spr.setScale(0.2f,0.2f);
	
	m_text.setFont(tablero->m_fuente);
	m_text.setCharacterSize(15);

	SetPosition(Utils::GetRandomVec(0.0f, 600.0f, 0.0f, 600.0f));
	
	//creamos la maquina de estados
	m_pStateMachine= new StateMachine<Matador>(this);
	//configuramos el estado inicial
	m_pStateMachine->SetCurrentState(State_Matador_Deambular::Instance());


}

void Matador::SetTarget(Hormiga* h){
	p_target=h;
}

Hormiga* Matador::GetTarget(){
	return p_target;
}

StateMachine<Matador>* Matador::GetFSM() const{
	return m_pStateMachine;
}

Vector2f Matador::GetPosition(){
	return m_spr.getPosition();
}

Tablero* Matador::GetTablero(){
	return tablero;
}

Matador::~Matador(void)
{
}

void Matador::Draw(RenderWindow *wnd){
	wnd->draw(m_spr);
	wnd->draw(m_text);

}

void Matador::Update(){

	m_pStateMachine->Update();
	
	m_text.setString(m_pStateMachine->CurrentState()->GetStateName());
	m_text.setOrigin(m_img.getSize().x / 2.0f, m_img.getSize().y / 2.0f);

}

void Matador::SetPosition(Vector2f pos){

	m_spr.setPosition(pos);
	Vector2f post= pos;
	post.y-=20;
	
	m_text.setPosition(post);

}

void Matador::ChangeDirection(){

	dir = Utils::GetRandomVec(-1.0f, 1.0f, -1.0f, 1.0f);
	float norm= sqrt(dir.x*dir.x+dir.y*dir.y);
	dir.x /=norm;
	dir.y /=norm;	
}

void Matador::Move(){
	Vector2f posActual= m_spr.getPosition();
	posActual.x+= dir.x * MATADORVEL;
	posActual.y+= dir.y * MATADORVEL;
	SetPosition(posActual);
}

void Matador::Chase(){

	Vector2f posActual= m_spr.getPosition();
	Vector2f posTarget= p_target->GetPosition();
	dir= posTarget-posActual;
	float norm= sqrt(dir.x*dir.x+dir.y*dir.y);
	dir.x /=norm;
	dir.y /=norm;
}