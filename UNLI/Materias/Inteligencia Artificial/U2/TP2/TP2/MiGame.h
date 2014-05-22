#pragma once

#include "Game.h"
#include "Enemigo.h"
#include "Player.h"

//Identificadores para las imagenes(sf::Image) almacenadas
//en el mapa m_ManagerDeImagenes
enum IDImagen{ JugadorImg,EnemigoImg, ObstaculoParedImg, ObstaculoCircularImg };

//Clase principal del juego, contiene toda la estructura de juego
//Este objeto sera el responsable de:
//	-Crear la escena
//	-Dibujar la pantalla
//	-Actualizar el juego
class MiGame: public Game
{
private:

	MiGame();

	MiGame(const MiGame& cpy);

	MiGame& operator=(const MiGame& cpy);

	std::vector<Enemigo*> Enemigos;
	std::vector<EntidadEscena*>				Obstaculos;//Necesitamos estos para decirle cuales son los obstaculos
	std::vector<SteeringBehaviors::Pared*>	Paredes;   //Necesitamos estos para definir como son las paredes obstaculos
	std::vector<EntidadEscena*>				ParedesEscena;//Necesitamos estos para tener las paredes como objetos de Box2D y que se grafiquen

	float escala = 0.2f;
	float minInterceptar = 100.0f;
	Player* m_pJugador;
	
	void CrearParedes();
	void CrearJugador();
	void CrearEnemigos();
	void CrearObstaculos();

public:
	//Nos devuelve la unica instancia de la clase
	static MiGame* Singleton();

	~MiGame();

	//================================================
	/////////	Game Propiedades publicas	 /////////
	//================================================

	std::map<IDImagen,sf::Texture> m_ManagerDeImagenes;

	//================================================
	/////////////	 Game Metodos		 /////////////
	//================================================

	//Crea la escena
	virtual void CrearEscena();

	//Actualiza la escena
	virtual void Actualizar(sf::Time frameTime);

	//Dibuja la escena
	virtual void Dibujar(sf::Time frameTime);

	//Carga los recursos a usar
	virtual void LoadRecursos();
};