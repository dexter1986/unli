#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
using namespace std;
using namespace sf;


class Animation{
private:
	// punteros a las imagenes
	vector<Image *> frames;
	// duracion de cada frame
	vector<float> frameTimes;
	// tiempo que ha sido mostrado el frame actual
	float currentFrameElapsed;
	// nro de frame actual y nro total de frames
	int iframe, nFrames;
	// banderas para saber si la animacion debe
	// ciclar o de lo contrario si ya finalizo
	bool loop, end;
	
public:
	Animation(bool loop=true);
	// permite agregar un nuevo frame con su duracion
	void AddFrame(Image &, float lenght);
	
	// permite avanzar la animacion un tiempo dt
	// y devolver la imagen actual
	Image &Animate(float dt);
	Image &GetCurrentFrame();
	
	// algunas funciones para controlar la animacion
	void SetLoop(bool loop);
	bool GetLoop();
	void Reset();
	bool Ended();
	
	// otras funciones para tener mayor control
	float GetCurrentFrameElapsedTime();
	void SetCurrentFrameNum(int i);
	int GetCurrentFrameNum();
};

#endif

