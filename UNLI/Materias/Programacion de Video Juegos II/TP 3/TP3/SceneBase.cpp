#include "SceneBase.h"


SceneBase::SceneBase(void)
{
	isDebug = false;
	isFinished = false;
	isExit = false;
}

SceneBase::~SceneBase(void)
{
}

void SceneBase::IsDebug(bool debug)
{
	isDebug =  debug;
}

bool SceneBase::IsFinished()
{
	return isFinished;
}

bool SceneBase::HayColision(float x, float y,sf::Color &color,bool isNPC)
{
	return false;
}

void SceneBase::AgregarEnemigo(float x, float y,int tipo)
{
}

bool SceneBase::IsExit()
{
	return isExit;
}