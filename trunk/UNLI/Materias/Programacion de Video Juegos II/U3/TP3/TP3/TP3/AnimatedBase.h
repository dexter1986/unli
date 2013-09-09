#ifndef ANIMATESPRITE_H
#define ANIMATESPRITE_H
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include "TextureManager.h"
using namespace std;
using namespace sf;

class AnimatedBase
{
private:
	vector<sf::IntRect> frames;
	vector<float> frameTimes;
	
	float currentFrameElapsed;	
	int iframe, nFrames;	
	bool loop, end;	

	int estado;

public:		
	void AddFrame(IntRect &rect, float lenght);		
	void AddFrame(int x, int y, int w, int h, float frameLenght);
	IntRect &AnimatedBase::Animate(float dt);
	void SetLoop(bool loop);
	bool GetLoop();
	void Reset();
	bool Ended();
		
	int GetEstado();
	float GetCurrentFrameElapsedTime();
	void SetCurrentFrameNum(int i);
	int GetCurrentFrameNum();
	IntRect &GetCurrentFrameRect();
	void Stop();

public:
	AnimatedBase(bool loop=true);
	~AnimatedBase(void);
};

#endif

