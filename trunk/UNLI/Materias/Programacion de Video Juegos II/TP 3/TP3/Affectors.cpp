#include "Affectors.h"
#include "ParticleSystem.h"


Gravity::Gravity(float gx, float gy){
	this->gx=gx;
	this->gy=gy;
}

void Gravity::Apply(ParticleSystem &ps, float dt){
	unsigned  cont=0;
	ParticleSystem::Particle *p=ps.particles;
	while(cont<ps.nMaxParticles){
		if(p->life>=0){
			p->vx+=gx*dt;
			p->vy+=gy*dt;
		}
		cont++; p++;
	}
}


Fade::Fade(float time){
	this->time=time;
}

void Fade::Apply(ParticleSystem &ps, float dt){
	unsigned  cont=0;
	ParticleSystem::Particle *p=ps.particles;
	while(cont<ps.nMaxParticles){
		if(p->life>=0 && p->life<=time){
			p->SetColor(sf::Color(255,255,255, int( 255*(p->life/time))));
		}
		cont++; p++;
	}
}



ScreenCollision::ScreenCollision(float left, float top, float right, float bottom){
	this->left=left;
	this->top=top;
	this->right=right;
	this->bottom=bottom;
}

void ScreenCollision::Apply(ParticleSystem &ps, float dt){
	unsigned  cont=0;
	ParticleSystem::Particle *p=ps.particles;
	sf::Vector2f particlePosition;
	while(cont<ps.nMaxParticles){
		if(p->life>=0){
			particlePosition=p->GetPosition();
			if(particlePosition.x<left) {p->SetX(left); p->vx*=-1;}
			if(particlePosition.x>right) {p->SetX(right); p->vx*=-1;}
			if(particlePosition.y<top) {p->SetY(top); p->vy*=-1;}
			if(particlePosition.y>bottom) {p->SetY(bottom); p->vy*=-1;}
		}
		cont++; p++;
	}
}


SeekerGonzalo::SeekerGonzalo(const sf::View &v, float gravity, float dampingRebote, float velAttract){
	sf::FloatRect rv=v.GetRect();
	left=rv.Left;
	right=rv.Right;
	top=rv.Top;
	bottom=rv.Bottom;
	this->gravity=gravity;
	this->dampingRebote=dampingRebote;
	this->velAttract=velAttract;
}

void SeekerGonzalo::Seek(unsigned x, unsigned y){
	seek_x=x; seek_y=y;
}

void SeekerGonzalo::Apply(ParticleSystem &ps, float dt){
	unsigned  cont=0;
	
	ParticleSystem::Particle *p=ps.particles;
	sf::Vector2f particlePosition;
	while(cont<ps.nMaxParticles){
		if(p->life>=0){
			particlePosition=p->GetPosition();
			// si le queda mas de 1 seg de vida, aplica gravedad y rebotes
			if(p->life>1){
					// rebota en los costados, cada rebote le quita velocidad
					if(particlePosition.x<left) {p->SetX(left); p->vx*=-dampingRebote;}
					else if(particlePosition.x>right) {p->SetX(right); p->vx*=-dampingRebote;}
					
					// rebota arriba y abajo, cada rebote le quita velocidad
					if(particlePosition.y<top) {p->SetY(top); p->vy*=-dampingRebote;}
					else if(particlePosition.y>bottom) {p->SetY(bottom); p->vy*=-dampingRebote;}
					else{
						// aplica gravedad
						p->vy+=gravity*dt;
					}
					// cambiamos el angulo segun la vel en y
					p->Rotate(p->vx*dt);
			}else{
				// en su ultimo segundo de vida se mueve
				// hacia la posicion del seeker
				p->Move(-velAttract*(particlePosition.x-seek_x)*dt,-velAttract*(particlePosition.y-seek_y)*dt);
			}
		}
		cont++; p++;
	}
}

