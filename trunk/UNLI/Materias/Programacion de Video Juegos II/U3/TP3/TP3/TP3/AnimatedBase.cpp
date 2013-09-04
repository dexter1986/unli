#include "AnimatedBase.h"

AnimatedBase::~AnimatedBase(void)
{
}

AnimatedBase::AnimatedBase(bool loop){
	this->loop=loop;	
	Reset();
}

// agrega un nuevo cuadro con su respectiva duracion
void AnimatedBase::AddFrame(IntRect &rect, float frameLenght){
	frames.push_back(rect);
	frameTimes.push_back(frameLenght);
	nFrames++;
}

// avanza la animacion en base al tiempo transcurrido
// tiene en cuenta si debe hacer un loop o finalizar
// ademas devuelve un puntero a la imagen actual de
// la animacion para un uso mas comodo
IntRect &AnimatedBase::Animate(float dt){
	currentFrameElapsed+=dt;
	if(currentFrameElapsed>frameTimes[iframe]){
		currentFrameElapsed-=frameTimes[iframe];
		iframe++;
		if(iframe>=frames.size()){
			if(loop)
				// volvemos al principio
				iframe=0;
			else{
				// la animacion finalizo
				iframe--;
				end=true;
			}
		}
	}
	return frames[iframe];
}

void AnimatedBase::SetLoop(bool loop){
	this->loop=loop;
}

bool AnimatedBase::GetLoop(){
	return loop;
}

bool AnimatedBase::Ended(){
	return end;
}

void AnimatedBase::Reset(){
	iframe=0; currentFrameElapsed=0; end=false;
}

void AnimatedBase::SetCurrentFrameNum(int i){
	iframe=i;	
}

int AnimatedBase::GetCurrentFrameNum(){
	return iframe;
}

IntRect &AnimatedBase::GetCurrentFrameRect()
{
	return frames[iframe];
}

float AnimatedBase::GetCurrentFrameElapsedTime(){
	return currentFrameElapsed;
}


