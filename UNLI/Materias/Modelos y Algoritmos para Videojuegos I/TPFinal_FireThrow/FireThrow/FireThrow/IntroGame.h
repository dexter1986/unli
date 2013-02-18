#include "GameObject.h"


#ifndef INTRO_GAME_H
#define INTRO_GAME_H

class IntroGame : public GameObject
{
private:
	int alpha;
public:
	void NextFrame();
	bool isNextFrame();
	void Draw(RenderWindow *app);
	IntroGame();
};

#endif