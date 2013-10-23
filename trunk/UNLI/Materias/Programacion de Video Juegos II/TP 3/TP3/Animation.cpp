#include "Animation.h"

// construye la animacion inicializando todas las variables
Animation::Animation(bool loop){
	this->loop=loop;
	Reset();
}

// agrega un nuevo cuadro con su respectiva duracion
void Animation::AddFrame(Image &i, float frameLenght){
	frames.push_back(&i);
	frameTimes.push_back(frameLenght);
	nFrames++;
}

// avanza la animacion en base al tiempo transcurrido
// tiene en cuenta si debe hacer un loop o finalizar
// ademas devuelve un puntero a la imagen actual de
// la animacion para un uso mas comodo
Image &Animation::Animate(float dt){
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
	return *frames[iframe];
}

// devuelve un puntero a la imagen actual de la animacion
Image &Animation::GetCurrentFrame(){
	return *frames[iframe];
}

// estas 2 funciones permiten controlar si se debe
// o no hacer loop
void Animation::SetLoop(bool loop){
	this->loop=loop;
}

bool Animation::GetLoop(){
	return loop;
}

// permite saber si la animacion termino
// (en caso de que no haga loop)
bool Animation::Ended(){
	return end;
}

// reinicializa la animacion
void Animation::Reset(){
	iframe=0; currentFrameElapsed=0; end=false;
}


// estas funciones permiten un mayor control
// nos van a ser utiles mas adelante
void Animation::SetCurrentFrameNum(int i){
	iframe=i;
}

int Animation::GetCurrentFrameNum(){
	return iframe;
}

float Animation::GetCurrentFrameElapsedTime(){
	return currentFrameElapsed;
}

