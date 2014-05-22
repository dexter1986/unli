#include "MiGame.h"
#include "Matematica.h"
#include <Box2D/Box2D.h>

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

MiGame::MiGame(): Game(sf::VideoMode(800,600,32), "TP2: Snack!", sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings(24, 8, 0), 60)
{}

MiGame::~MiGame()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

MiGame* MiGame::Singleton()
{
	static MiGame instancia;
	return &instancia;
}

void MiGame::CrearEscena()
{	
	sf::Texture* imgObstaculoCircular = &m_ManagerDeImagenes[IDImagen::ObstaculoCircularImg];
	
	CrearParedes();
	CrearObstaculos();
	CrearJugador();
	CrearEnemigos();
}

void MiGame::CrearEnemigos()
{
	sf::Texture* img = &m_ManagerDeImagenes[IDImagen::EnemigoImg];

	b2BodyDef cuerpo;
	b2FixtureDef adorno;

	int cantEnemigos = rand() % 3 + 5;

	for (int i = 0; i < cantEnemigos; i++)
	{
		cuerpo.type = b2BodyType::b2_dynamicBody;
		adorno.restitution = 0.0;
		adorno.isSensor = false;
		adorno.friction = 0.3f;
		adorno.density = 0.01f;
		b2PolygonShape* pRectangulo = new b2PolygonShape();
		pRectangulo->SetAsBox(img->getSize().x / 2 * escala, img->getSize().y / 2 * escala, b2Vec2(0, 0), 0);
		adorno.shape = pRectangulo;

		cuerpo.position = b2Vec2((rand() / (float)RAND_MAX) * 400 + 200, (rand() / (float)RAND_MAX) * 400 + 100);
		cuerpo.angle = 0;

		Enemigo* enemigo = new Enemigo(m_pJugador,cuerpo, adorno, escala, img);

		enemigo->m_FuerzaSteeringMax = 800;
		enemigo->m_VelocidadMax = rand() % 40 + 50.0f;

		enemigo->GetSteeringBehaviors().EvadirParedesOn();		
		enemigo->GetSteeringBehaviors().m_PesoEvadirParedes = 1.0f;
		enemigo->GetSteeringBehaviors().EvadirObstaculosOn();		
		enemigo->GetSteeringBehaviors().m_PesoEvadirObstaculos = 1.0f;
		enemigo->GetSteeringBehaviors().DeambularOn();			
		enemigo->GetSteeringBehaviors().m_PesoDeambular = 2.0f;

		enemigo->GetSteeringBehaviors().m_PesoInterceptar = 4.0f;

		enemigo->GetSteeringBehaviors().m_pParedes = &Paredes;
		enemigo->GetSteeringBehaviors().m_pObstaculos = &Obstaculos;

		Enemigos.push_back(enemigo);
	}
}

void MiGame::CrearJugador()
{
	sf::Texture* img = &m_ManagerDeImagenes[IDImagen::JugadorImg];

	b2FixtureDef adorno;
	b2BodyDef cuerpo;

	cuerpo.type = b2BodyType::b2_dynamicBody;
	adorno.restitution = 0.0;
	adorno.isSensor = false;
	adorno.friction = 0.3f;
	adorno.density = 0.01f;
	b2PolygonShape* pRectangulo = new b2PolygonShape();
	pRectangulo->SetAsBox(img->getSize().x / 2 * escala, img->getSize().y / 2 * escala, b2Vec2(0, 0), 0);
	adorno.shape = pRectangulo;

	cuerpo.position = b2Vec2(100, 100);
	cuerpo.angle = 0;

	m_pJugador = new Player(cuerpo, adorno, escala, img);

	m_pJugador->m_FuerzaSteeringMax = 600;
	m_pJugador->m_VelocidadMax = 400;	
}

void MiGame::CrearObstaculos()
{
	sf::Texture* imgObstaculoCircular = &m_ManagerDeImagenes[IDImagen::ObstaculoCircularImg];

	b2BodyDef cuerpo;
	b2FixtureDef adorno;
		
	for (int i = 0; i < 5; ++i)
	{
		cuerpo.type = b2BodyType::b2_staticBody;
		adorno.restitution = 0.2;
		adorno.isSensor = false;
		adorno.friction = 0.3f;
		adorno.density = 0.01f;
		b2CircleShape* pCirculo = new b2CircleShape();
		pCirculo->m_radius = imgObstaculoCircular->getSize().x / 2 * escala;
		adorno.shape = pCirculo;

		cuerpo.position = b2Vec2((rand() / (float)RAND_MAX) * 400 + 200, (rand() / (float)RAND_MAX) * 400 + 100);
		cuerpo.angle = 0;
				
		Obstaculos.push_back(new EntidadEscena(cuerpo, adorno, escala, imgObstaculoCircular));
	}
}

void MiGame::CrearParedes()
{
	sf::Texture* imgObstaculoPared = &m_ManagerDeImagenes[IDImagen::ObstaculoParedImg];

	b2BodyDef cuerpo;
	b2FixtureDef adorno;
	b2PolygonShape* pRectangulo = new b2PolygonShape();

	//Pared de arriba
	cuerpo.type = b2BodyType::b2_staticBody;
	adorno.restitution = 0.2f;
	adorno.isSensor = false;
	adorno.friction = 0.3f;
	adorno.density = 0.01f;
	pRectangulo->SetAsBox(400, 10, b2Vec2(0.0f, 0.0f), 0);
	adorno.shape = pRectangulo;

	cuerpo.position = b2Vec2(400, 0);
	cuerpo.angle = 0;

	Paredes.push_back(new SteeringBehaviors::Pared(sf::Vector2f(0.0f, 1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)));
	ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));

	//Pared de abajo
	cuerpo.position = b2Vec2(400, 600);

	Paredes.push_back(new SteeringBehaviors::Pared(sf::Vector2f(0.0f, -1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)));
	ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));

	//Pared de izquierda
	cuerpo.position = b2Vec2(0, 300);
	cuerpo.angle = 3.1415f / 2.0f;

	Paredes.push_back(new SteeringBehaviors::Pared(sf::Vector2f(1.0f, 0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)));
	ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));

	//Pared de derecha
	cuerpo.position = b2Vec2(800, 300);
	cuerpo.angle = 3.1415f / 2.0f;

	Paredes.push_back(new SteeringBehaviors::Pared(sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)));
	ParedesEscena.push_back(new EntidadEscena(cuerpo, adorno, 800.0f, 20.0f, imgObstaculoPared));
}

void MiGame::Actualizar(sf::Time frameTime)
{
	float dt = frameTime.asSeconds();

	m_pJugador->Actualizar(dt);

	for (int i = 0; i < Enemigos.size(); ++i)			
		Enemigos[i]->Actualizar(dt);

	for (int i = 0; i < Obstaculos.size(); ++i)
		Obstaculos[i]->Actualizar(dt);

	for (int i = 0; i < ParedesEscena.size(); ++i)
		ParedesEscena[i]->Actualizar(dt);

	m_World.Step(m_dt, 10, 10);

	m_World.ClearForces();
}

void MiGame::Dibujar(sf::Time frameTime)
{
	float dt = frameTime.asSeconds();

	m_Window.clear();	

	m_pJugador->Dibujar(m_Window);
	
	for (int i = 0; i < Enemigos.size(); ++i)
		Enemigos[i]->Dibujar(m_Window);

	for (int i = 0; i < Obstaculos.size(); ++i)
		Obstaculos[i]->Dibujar(m_Window);

	for (int i = 0; i < ParedesEscena.size(); ++i)
		ParedesEscena[i]->Dibujar(m_Window);

	m_Window.display();
}

void MiGame::LoadRecursos()
{	
	if (!m_ManagerDeImagenes[IDImagen::ObstaculoParedImg].loadFromFile("Recursos\\ObstaculoPared.png"))
		exit(0);	
	if (!m_ManagerDeImagenes[IDImagen::JugadorImg].loadFromFile("Recursos\\player.png"))
		exit(0);
	if (!m_ManagerDeImagenes[IDImagen::EnemigoImg].loadFromFile("Recursos\\enemigo.png"))
		exit(0);
	if (!m_ManagerDeImagenes[IDImagen::ObstaculoCircularImg].loadFromFile("Recursos\\Obstaculo.png"))
		exit(0);
}