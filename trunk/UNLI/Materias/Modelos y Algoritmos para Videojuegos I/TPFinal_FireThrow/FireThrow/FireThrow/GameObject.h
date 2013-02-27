#include <SFML/Graphics.hpp>
#include "GameObjectBase.h"

using namespace sf;
using namespace std;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject: public GameObjectBase
{
protected:		
	Vector2f pos;	
	Vector2f velocidad;
	float width,height;
	bool isEnable;
	bool isCollide;
	Image img;
	Sprite sprite;
	void LoadSprite(const std::string &filename);	
	void LoadSprite(const std::string &filename,int frames);
	int maxframes;
	int currentframe;
	int frameRate;
	int countFrameRate;
	Image *imgAnim;
	int startAnim;
	int stopAnim;
public:
	GameObject();
	GameObject(bool isCollide,const std::string &Filename);	
	GameObject(bool isCollide,const std::string &filename,int frames);	
	void Enable(bool enable);
	void Init(RenderWindow *app);
	void Draw(RenderWindow *app) const;
	bool Hit(int x,int y) const;
	bool Hit(Rect<int> *rect) const;
	Vector2f GetPos() const;
	float GetWidth() const;
	float GetHeight() const;
	bool isAnim() const;
	void Update(RenderWindow *app);
	const sf::Image *ShareImage();
	void Move(float x,float y);
	void Rotate(float rad);
	void SetCenter(float x,float y);
	void Anim();
	void UpdateFrame();
	void SetAnim(int start,int stop);
	void RotateAbs(float ang);
	~GameObject(void);
};

#endif