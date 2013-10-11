#include "ParallaxLayer.h"


// Constructor
ParallaxLayer::ParallaxLayer(sf::Image &img, float factor_x, bool repeat_x, float offset_x, float factor_y, bool repeat_y, float offset_y){
	SetImage(img);
	
	// calculamos el ancho y alto de la imagen, esto
	// nos va a servir para evitar desbordes en el desplazamiento
	ancho_img=img.GetWidth();
	alto_img=img.GetHeight();
	
	// inicializamos las variables internas
	despl_x=despl_y=0;
	this->factor_x=factor_x;
	this->factor_y=factor_y;
	this->repeat_x=repeat_x;
	this->repeat_y=repeat_y;
	this->offset_x=offset_x;
	this->offset_y=offset_y;

	// seleccionamos la textura y habilitamos la repeticion
	// segun corresponda
	img.Bind();
	if(repeat_x)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	if(repeat_y)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// ajustamos la posicion de la capa
	Sprite::SetPosition(offset_x, offset_y);
	SetScale(0.5,0.5);
}


// Permite mover la capa segun el desplazamiento del personaje
void ParallaxLayer::Move(float dx, float dy){
	// para x
	if(repeat_x){
		// si debemos desplazar la textura simplemente
		// incrementamos la variable despl_x y la mantenemos
		// limitada para evitar desbordes
		despl_x+=factor_x*dx;
		if(factor_x>0 && despl_x>ancho_img) despl_x-=ancho_img;
		else if(factor_x<0 && despl_x<-ancho_img) despl_x+=ancho_img;
	}else{
		// de lo contrario movemos el sprite
		Sprite::Move(factor_x*dx, 0);
	}
	
	// para y
	if(repeat_y){
		// si debemos desplazar la textura simplemente
		// incrementamos la variable despl_y y la mantenemos
		// limitada para evitar desbordes
		despl_y+=factor_y*dy;
		if(factor_y>0 && despl_y>alto_img) despl_y-=alto_img;
		else if(factor_y<0 && despl_y<-alto_img) despl_y+=alto_img;
	}else{
		// de lo contrario movemos el sprite
		Sprite::Move(0, factor_y*dy);
	}
}


// Permite mover la capa dado un lapso de tiempo dt
void ParallaxLayer::Move(float dt){
	Move(dt, dt);
}


// Dibuja la capa
void ParallaxLayer::Draw(sf::RenderWindow &w){
	// selecciona y guarda la matriz de textura
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	// aplicamos la transformacion y dibujamos
	glLoadIdentity();
	glTranslatef(despl_x,despl_y,0);
	w.Draw(*this);
	// restauramos la matriz de textura
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();	
}


// Permite ajustar la capa a la vista para usar scrolling
void ParallaxLayer::SetPosition(sf::View &v){
	Sprite::SetPosition(offset_x+v.GetRect().Left, offset_y+v.GetRect().Top);	
}
