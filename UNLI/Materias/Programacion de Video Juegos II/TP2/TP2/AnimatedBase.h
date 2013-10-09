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
	vector<sf::Vector2f> frameOffsets;
	vector<sf::Vector2f> frameFlipOffsets;
	
	float currentFrameElapsed;	
	int iframe, nFrames;	
	bool loop, end;	
	FloatRect aabb;
	int estado;
	
public:		
	void AddFrame(IntRect &rect, float lenght,float offset_x,float offset_y,float flipoffset_x ,float flipoffset_y);		
	void AddFrame(int x, int y, int w, int h, float frameLenght,float offset_x=0,float offset_y=0,float flipoffset_x=0 ,float flipoffset_y=0);
	IntRect &AnimatedBase::Animate(float dt);
	void SetLoop(bool loop);
	bool GetLoop();
	void Reset();
	bool Ended();
	
	bool  reverse;

	int GetEstado();
	float GetCurrentFrameElapsedTime();
	void SetCurrentFrameNum(int i);
	void SetAABB(FloatRect &rect);
	FloatRect &GetAABB();
	int GetCurrentFrameNum();
	IntRect &GetCurrentFrameRect();
	Vector2f &GetCurrentFrameOffset();
	Vector2f &GetCurrentFrameFlipOffset();
	void Stop();

public:
	AnimatedBase(bool loop=true);
	~AnimatedBase(void);
};

#endif

