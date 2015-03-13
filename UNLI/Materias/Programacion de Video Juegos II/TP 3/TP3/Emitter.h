#ifndef EMITTER_H
#define EMITTER_H
#include <SFML/Graphics.hpp>
#include "Affector.h"
#include <vector>
#include <cmath>
using namespace std;

#ifndef M_PI
	#define M_PI 3.1416
#endif


class Emitter//: public sf::Sprite
{
	private:
	// medias de velocidad y angulo de emision y vida
	float emitVel, emitAngle, emitLife;
	// desvios de velocidad y angulo de emision y vida
	float deltaVel, deltaAngle, deltaLife;
	// tasa de creacion de particulas
	float spawnRate;
	// si debe crear nuevas particulas o destruirse
	bool spawn, kill;
	
	// los afectadores del sistema de particulas
	vector<Affector *> affectors;
	
	// constructor, es utilizado por
	// la clase ParticleSystemManager
	Emitter(float emitVel=5, float emitAngle=M_PI,
			float emitLife=3, float deltaVel=0,
			float deltaAngle=M_PI, float deltaLife=1,
			float spawnRate=10,bool oneTime=false);

	sf::Blend::Mode _blendedMode;
	sf::Color _color;
	sf::Vector2f _position;
	const sf::Image* _image;

	public:
	~Emitter();	

	//Solo emite una vez. simula una explosion
	bool isOneTime;

	// agrega un affector al emisor
	void AddAffector(Affector &e);
	// permite controlar parametros de la emision
	void SetEmmitVel(float vel, float deltaVel=0);
	void SetEmmitAngle(float angle, float deltaAngle=0);
	void SetEmmitLife(float life, float deltaLife=0);
	void SetSpawnRate(float newSpawnRate);
	
	sf::Blend::Mode GetBlendMode()
	{
		return _blendedMode;
	};

	void SetBlendMode(sf::Blend::Mode Mode)
	{
		_blendedMode = Mode;
	};

	sf::Color GetColor()
	{
		return _color;
	};

	sf::Color SetColor(sf::Color& const  color)
	{
		return _color;
	};

	 const sf::Vector2f& GetPosition() const
	 {
		 return _position;
	 };

	 void SetPosition(float X, float Y)
	 {
		 _position.x = X;
		 _position.y = Y;
	 };

	 const sf::Image* GetImage() const
	 {
		 return _image;
	 };

	 void SetImage(const sf::Image* Img)
	 {
		 _image = Img;
	 };

	float GetSpawnRate(){return spawnRate;};
	
	// indica si el emisor debe o no crear
	// nuevas particulas
	void Spawn(bool spawn);
	
	// senala que el emisor no seguira
	// emitiendo particulas y puede
	// liberarse
	void Kill();
	
	friend class ParticleSystem;
	friend class ParticleSystemManager;
};

#endif

