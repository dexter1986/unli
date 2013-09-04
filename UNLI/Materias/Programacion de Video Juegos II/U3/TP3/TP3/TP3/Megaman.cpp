#include "Megaman.h"
#include "Disparos.h"

// algunas constantes
float const v0=-256;		// velocidad inicial al comenzar el salto 
float const gravity=512;	// gravedad
float const shoot_time=0.3; // tiempo que dura la secuencia de disparo
float const velmisiles=180; // velocidad de los disparos (pixeles x segundo)
float const vx=60;			// velocidad del movimiento horizontal (constante)


Megaman::Megaman(ManejadorDisparos *d) {
	InicializarAnimaciones();
	estado=PARADO;				// setea el estado inicial
	direccion=1;
	SetCenter(16,16);			// las coordenadas que utilicemos corresponden al centro del sprite
	y0=GetPosition().y;
	vy=0;
	shootTime=shoot_time;
	disparos=d;
}


// carga e inicializa las animaciones con sus cuadros y tiempos
void Megaman::InicializarAnimaciones(){	
	im.Load("../megaman_sprites.png", 3, 4);
	animaciones[PARADO].AddFrame(im[0], 1.2);
	animaciones[PARADO].AddFrame(im[1], 0.1);
	animaciones[CORRIENDO].AddFrame(im[3], 0.2);
	animaciones[CORRIENDO].AddFrame(im[4], 0.2);
	animaciones[CORRIENDO].AddFrame(im[5], 0.2);
	animaciones[CORRIENDO].AddFrame(im[4], 0.2);
	animaciones[DISPARANDO].AddFrame(im[8], 0.2);
	animaciones[SALTANDO].AddFrame(im[6], 2);
	animaciones[DISPARANDO_Y_CORRIENDO].AddFrame(im[9], 0.2);
	animaciones[DISPARANDO_Y_CORRIENDO].AddFrame(im[10], 0.2);
	animaciones[DISPARANDO_Y_CORRIENDO].AddFrame(im[11], 0.2);
	animaciones[DISPARANDO_Y_CORRIENDO].AddFrame(im[10], 0.2);
	animaciones[SALTANDO_Y_MOVIENDOSE].AddFrame(im[6], 2);
	animaciones[SALTANDO_Y_DISPARANDO].AddFrame(im[7], 2);
	animaciones[SALTANDO_MOVIENDOSE_Y_DISPARANDO].AddFrame(im[7], 2);
}


// el cambio de estado resetea el estado de la animacion del proximos estado
// pero en el caso de ciertos cambios de estado, por ejemplo CORRIENDO=>DISPARANDO_Y_CORRIENDO
// es necesario que la nueva animacion empieze en donde la anterior termino (las animaciones
// CORRIENDO y DISPARANDO_Y_CORRIENDO son practicamente identicas, para eso utilizamos el
// flag continueFromCurrent, si esta en verdadero ponemos a la nueva animacion en el mismo
// estado que la anterior
void Megaman::CambiarEstado(Estado nuevoEstado, bool continueFromCurrent){
	int viejoEstado=estado;
	estado=nuevoEstado;
	animaciones[nuevoEstado].Reset();
	if(continueFromCurrent){
		// seteamos el frame de la nueva animacion
		animaciones[nuevoEstado].SetCurrentFrameNum(animaciones[viejoEstado].GetCurrentFrameNum());
		// seteamos el tiempo del frame de la nueva animacion al mismo tiempo que tenia la anterior
		animaciones[nuevoEstado].Animate(animaciones[viejoEstado].GetCurrentFrameElapsedTime());
	}
}


// comienza la secuencia de salto, setea la velocidad en y
// y guarda la coordenada y0 para despues saber cuando volvemos
// a tocar el suelo
void Megaman::Saltar(){
	vy=v0;
	y0=GetPosition().y;
}

// detecta si hubo colision con el suelo y ajusta la coordenada y del sprite
bool Megaman::ColisionaConSuelo(){
	if(GetPosition().y>=y0){
		// si hubo colision con el suelo, puede haber ocurrido
		// interpenetracion, por lo que es necesario ajustar
		// la coordenada y a la del suelo que guardamos antes
		SetY(y0);
		return true;
	}else{
		return false;
	}
}

// para saber si ya expiro el tiempo que dura la secuencia de disparo
bool Megaman::SecuenciaDisparoFinalizada(){
	return shootTime<0;
}


// al disparar reseteamos el contador shootTime (que es decrementado hasta
// que finaliza la secuencia de disparo) y creamos el proyectil especificando
// la posicion de inicio y su velocidad
void Megaman::Disparar(float x, float y){
	shootTime=shoot_time;
	disparos->AgregarDisparo(x, y, velmisiles*direccion);
}


// Esta es la funcion mas importante, realiza los cambios de estado, movimientos
// y animacion del personaje
void Megaman::Mover_y_Animar(Joystick j, float dt){
	// EL SWITCH GRANDE...
	// para cada estado, preguntamos si ocurrio alguno de los eventos que hacen
	// que se pase a otro estado
	switch(estado){
		case PARADO:
			if(j.left){
				CambiarEstado(CORRIENDO);
				direccion=-1;
			}else if(j.right){
				CambiarEstado(CORRIENDO);
				direccion=1;
			}else if(j.a){
				CambiarEstado(DISPARANDO);
				// la posicion del disparo esta calculada a ojo...
				Disparar(GetPosition().x+8*direccion, GetPosition().y);
			}else if(j.b){
				CambiarEstado(SALTANDO);
				Saltar();
			}
		break;
			
		case CORRIENDO:
			if(!j.left && !j.right){
				CambiarEstado(PARADO);
			}else if(j.b){
				CambiarEstado(SALTANDO_Y_MOVIENDOSE);
				Saltar();
			}else if(j.a){
				CambiarEstado(DISPARANDO_Y_CORRIENDO, true);
				Disparar(GetPosition().x+8*direccion, GetPosition().y);
			}
		break;
		
		case SALTANDO:
			if(j.left){
				CambiarEstado(SALTANDO_Y_MOVIENDOSE);
				direccion=-1;
			}else if(j.right){
				CambiarEstado(SALTANDO_Y_MOVIENDOSE);
				direccion=1;
			}else if(j.a){
				CambiarEstado(SALTANDO_Y_DISPARANDO);
				Disparar(GetPosition().x+8*direccion, GetPosition().y-5);
			}else if(ColisionaConSuelo()){
				CambiarEstado(PARADO);
			}
		break;
			
			
		case DISPARANDO:
			if(j.left){
				CambiarEstado(DISPARANDO_Y_CORRIENDO, true);
				direccion=-1;
			}else if(j.right){
				CambiarEstado(DISPARANDO_Y_CORRIENDO, true);
				direccion=1;
			}else if(j.b){
				CambiarEstado(SALTANDO);
				Saltar();
			}else if(SecuenciaDisparoFinalizada()){ // finaliza la secuencia de disparo
				CambiarEstado(PARADO);
			}
		break;
			
			
		case DISPARANDO_Y_CORRIENDO:
			if(j.b){
				CambiarEstado(SALTANDO_Y_MOVIENDOSE);
				Saltar();
			}else if(!j.left && !j.right){
				CambiarEstado(DISPARANDO);
			}else if(SecuenciaDisparoFinalizada()){
				CambiarEstado(CORRIENDO, true);
			}
		break;
			
			
		case SALTANDO_Y_DISPARANDO:
			if(j.left){
				CambiarEstado(SALTANDO_Y_MOVIENDOSE);
				direccion=-1;
			}else if(j.right){
				CambiarEstado(SALTANDO_Y_MOVIENDOSE);
				direccion=1;
			}else if(SecuenciaDisparoFinalizada()){
				CambiarEstado(SALTANDO);
			}else if(ColisionaConSuelo()){
				CambiarEstado(DISPARANDO);
			}
		break;
			
		case SALTANDO_Y_MOVIENDOSE:
			if(j.a){
				CambiarEstado(SALTANDO_MOVIENDOSE_Y_DISPARANDO);
				Disparar(GetPosition().x+8*direccion, GetPosition().y-5);
			}else if(!j.left && !j.right){
				CambiarEstado(SALTANDO);
			}else if(ColisionaConSuelo()){
				CambiarEstado(PARADO);
			}
			
			
		break;
			
		case SALTANDO_MOVIENDOSE_Y_DISPARANDO:
			if(!j.left && !j.right){
				CambiarEstado(SALTANDO_Y_DISPARANDO);
			}else if(SecuenciaDisparoFinalizada()){
				CambiarEstado(SALTANDO_Y_MOVIENDOSE);
			}else if(ColisionaConSuelo()){
				CambiarEstado(DISPARANDO);
			}
		break;
	}
	
	
	// segun el estado, movemos horizontalmente
	if(estado==CORRIENDO || estado==SALTANDO_Y_MOVIENDOSE || estado==DISPARANDO_Y_CORRIENDO || estado==SALTANDO_MOVIENDOSE_Y_DISPARANDO){
		Move(direccion*vx*dt, 0);
	}
	
	// segun el estado, movemos verticalmente
	if(estado==SALTANDO || estado==SALTANDO_Y_MOVIENDOSE || estado==SALTANDO_Y_DISPARANDO || estado==SALTANDO_MOVIENDOSE_Y_DISPARANDO){
		vy+=gravity*dt;
		Move(0, vy*dt);
	}
	

	// segun la direccion le avisamos si debe dibujar el sprite invertido
	FlipX(direccion<0);
	
	// decrementamos tiempo a la secuencia de disparo
	if(!SecuenciaDisparoFinalizada()) shootTime-=dt;
	
	// animamos y ponemos la imagen al sprite
	SetImage(animaciones[estado].Animate(dt));
}


