#include "AnimatedBase.h"

AnimatedBase::~AnimatedBase(void)
{
}

AnimatedBase::AnimatedBase(bool loop){
	this->loop=loop;		
	reverse = false;
	nFrames = 0;
	Reset();
}

Vector2f &AnimatedBase::GetCurrentFrameOffset()
{
	return frameOffsets[iframe];
}

Vector2f &AnimatedBase::GetCurrentFrameFlipOffset()
{
	return frameFlipOffsets[iframe];
}

// agrega un nuevo cuadro con su respectiva duracion
void AnimatedBase::AddFrame(IntRect &rect, float frameLenght,float offset_x ,float offset_y,float flipoffset_x ,float flipoffset_y){
	frames.push_back(rect);
	frameTimes.push_back(frameLenght);
	frameOffsets.push_back(Vector2f(offset_x,offset_y));
	frameFlipOffsets.push_back(Vector2f(flipoffset_x,flipoffset_y));
	nFrames++;
}

void AnimatedBase::AddFrame(int x, int y, int w, int h, float frameLenght,float offset_x,float offset_y,float flipoffset_x ,float flipoffset_y)
{
	AddFrame(IntRect(x,y,x+w,y+h),frameLenght,offset_x,offset_y,flipoffset_x,flipoffset_y);
}

// avanza la animacion en base al tiempo transcurrido
// tiene en cuenta si debe hacer un loop o finalizar
// ademas devuelve un puntero a la imagen actual de
// la animacion para un uso mas comodo
IntRect &AnimatedBase::Animate(float dt){
	currentFrameElapsed+=dt;
	if(currentFrameElapsed>frameTimes[iframe]){
		currentFrameElapsed-=frameTimes[iframe];
		if(reverse)
		{
			iframe--;
		}
		else
		{
			iframe++;
		}
		if(iframe>=frames.size()){
			if(loop)
				if(reverse)
				{
					iframe = nFrames-1;
				}
				else
				{
					// volvemos al principio
					iframe=0;
				}
			else{
				// la animacion finalizo
				if(reverse)
				{
					iframe++;
				}else
				{
					iframe--;
				}
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
	 currentFrameElapsed=0; end=false;
	if(reverse)
	{
		iframe = nFrames -1;
	}
	else
	{
		iframe=0;
	}
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

void AnimatedBase::Stop(){
	end = true;
}


