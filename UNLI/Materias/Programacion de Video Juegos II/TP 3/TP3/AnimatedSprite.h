#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "TiledSprite.h"
#include <vector>


class AnimatedSprite : public TiledSprite {	
	public:
	/**
	 * \brief	Construye un sprite animado a partir de un spritesheet
	 * \param	filename nombre del archivo con la spritesheet
	 * \param	nCols cantidad de columnas en el spritesheet
	 * \param	nRows cantidad de filas en el spritesheet
	 */
	AnimatedSprite(const std::string &filename, unsigned nCols, unsigned nRows=1);

		
	/**
	 * \brief	asigna una animación al sprite
	 * \param	frames numeros de los tiles que componen la animacion
	 * \param	animTime tiempo total de la animacion (todos los frames duran lo mismo = animTime/frames.size())
	 * \param	loop indica si la animación debe reiniciarse al terminar o quedar en el último cuadro
	 * \param	startFrame indica el numero de cuadro (dentro del vector frames) con el que la animacion debe comenzar (es util para concatenar animaciones)
	 * \param	resetFrameTime indica si debe tomarse el tiempo transcurrido del frame actual como tiempo transcurrido del primer frame de la nueva animacion (es util para concatenar animaciones)
	 */
	void SetAnimation(const std::vector<unsigned> &frames, float animTime, bool loop = true, unsigned startFrame = 0, bool resetFrameTime = true);

	
	/**
	 * \brief	anima el sprite (siempre que se le ha asignado una animacion con SetAnimation())
	 * \param	dt tiempo transcurrido
	 * \see		SetAnimation
	 */
	void Animate(const float &dt);

	
	/**
	 * \brief	detiene la animación y asigna al sprite el tile indicado
	 * \param	numero del tile con el que se mostrará el sprite de ahora en adelante
	 */
	void Stop(unsigned tileIndex);
	
	
	/**
	 * \brief permite saber si se está reproduciendo alguna animación
	 * \return true si el sprite está siendo animado o false si la animación se ha detenido
	 */
	bool IsAnimating() const;
	
	private:
	float m_frameTime;				///< tiempo que dura cada frame
	float m_currentFrameElapsed;	///< tiempo que ha transcurrido mostrando el frame actual
	unsigned m_currentFrame;		///< posicion ,dentro del vector, del frame actual
	bool m_isPlaying;				///< indica si la animación se esta reproduciendo o se ha detenido
	bool m_loop;					///< indica si la animación debe realizar un bucle
	std::vector<unsigned> m_frames;	///< indices de los tiles que componen la animacion
};

#endif

