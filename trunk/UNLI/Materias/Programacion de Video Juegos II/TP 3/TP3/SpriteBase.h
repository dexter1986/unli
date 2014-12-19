#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "AnimatedBase.h"
#include "Joystick.h"
#include "GameEngine.h"


using namespace std;
using namespace sf;

class GameEngine;

class SpriteBase :	public Sprite
{
protected:	
	enum Direccion
	{
		UP,
		LEFT,
		RIGHT,
		DOWN
	};

	static const int MAX_VEL_Y = 1000;
	static const int MAX_VEL_X = 80;

	float v0;		// velocidad inicial al comenzar el salto 
	float gravity;	// gravedad
	float delay;
	float ajustaColision_y,ajustaColision_x; // ajuste de colision
	int currentState;
	Vector2f velocidad;
	Vector2f posicion;
	Vector2f posicion_inicial;
	Vector2f scale;
	float dt;
	
	Joystick joystick;
	GameEngine *engine;
	Direccion direccion;// si apunta a la der o izq (flip horizontal de la textura)

	bool isNPC;
	bool isHitWall;
	bool isVisible;
	
	AnimatedBase *animaciones;
	FloatRect aabb;	
	Nivel *nivel;	
	ManejadorDisparos *disparos;
	float shootTime;

	// inicializa las animaciones, es llamado en el constructor
	bool IsAnimationEnded();
	void AnimationStop();
	int AnimationCurrentFrame();
	virtual void InicializarAnimaciones()=0;
	virtual void Internal_Mover_y_Animar()=0;
	// cambia el estado y hace algunas operaciones necesarias
	void CambiarEstado(int nuevoEstado, bool continueFromCurrent=false);	
	void AnimationReverse(bool reverse);
	bool DelayTransition(bool reset=false);
	void CalculateAABB();
	void SetOffsetAABB(Vector2f &offset);
	bool ColisionaPared();
	bool ColisionaTecho();
	bool ColisionaSuelo();
	void AjustaColisionX();
	void AjustaColisionY();	
	bool SecuenciaDisparoFinalizada();
	void Disparar(float x, float y,float shoot_time,float velmisiles);
	void Disparar(float shootTime,float vel_misiles);
	virtual void AiNpc();
	bool CheckVisibility();
	void ResolverColision(int tipo,FloatRect aabb_tmp);
public:

	bool pause;
	bool isDead;
	int vidas;
	bool RecibirImpacto(float x,float y);
	void Draw(sf::RenderWindow &w);
	int GetDireccionX();
	FloatRect &GetAABB();
	virtual void Inicializar(ManejadorDisparos *d,Nivel *n);
	SpriteBase(GameEngine *e,int cant_estados,const string &filename,float scale_x=0,float scale_y=0,bool NPC=false);
	void Mover_y_Animar(Joystick &j, float dt);	
	void Mover_y_Animar_NPC(float dt);	
	virtual ~SpriteBase(void);
};
