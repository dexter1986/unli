#include "AnimatedSprite.h"

// constructor
AnimatedSprite::AnimatedSprite(const std::string &filename, unsigned nCols, unsigned nRows)
	:TiledSprite(filename, nCols, nRows){
	m_frameTime = 0;
	m_currentFrameElapsed = 0;
	m_isPlaying = false;
}

// asigna una animacion al vector
void AnimatedSprite::SetAnimation(const std::vector<unsigned> &frames, float animTime, bool loop, unsigned startFrame, bool resetFrameTime){
	// copia los frames
	m_frames = frames;
	// calcula el tiempo de cada frame (todos duran igual)
	m_frameTime = animTime / frames.size();
	m_loop = loop;
	m_currentFrame = startFrame;
	if (resetFrameTime) m_currentFrameElapsed = 0;
	m_isPlaying = true;
}


void AnimatedSprite::Animate(const float &dt){
	// si la animación está parada, no hacemos nada
	if (!m_isPlaying) return;
	// incrementamos el tiempo transcurrido en el frame actual
	m_currentFrameElapsed+=dt;
	// si es hora de cambiar de frame
	if (m_currentFrameElapsed>=m_frameTime){
		// ajustamos el tiempo transcurrido
		m_currentFrameElapsed-=m_frameTime;
		// incrementamos el numero de frame
		++m_currentFrame;
		// si se han recorrido todos los frames del vector
		if (m_currentFrame >= m_frames.size()){
			// y si debemos hacer loop
			if (m_loop){
				// empezamos nuevamente desde el primer tile
				m_currentFrame = 0;
				SetTileIndex(m_frames[m_currentFrame]);
			}else{
				// si no, paramos la animación
				m_isPlaying = false;
			}
		}else{
			// si no llegamos al final del vector, simplemente seleccionamos el tile correspondiente
			SetTileIndex(m_frames[m_currentFrame]);
		}
	}
}


void AnimatedSprite::Stop(unsigned tileIndex){
	// paramos la animacion
	m_isPlaying = false;
	SetTileIndex(tileIndex);
}


bool AnimatedSprite::IsAnimating() const{
	return m_isPlaying;
}
