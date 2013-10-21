#include "Tanque.h"

Tanque::Tanque(double x,double y,ManagerTexture& manager, Avion& avion)
{
	TanqueX=x;
	TanqueY=y;
	Oruga1=0;
	Oruga2=0;
	TanqueAng=0; 
	ArmaAng=0;
	ArmaTamanio=0;	
	managerText = &manager; 
	enemigo = &avion;
	Tanque_Escala=0.25;
	Energia=100;
	direccionAngulo = 0; 
	direccionPaso = 0;
	contadorPasosFSM = 0;
	contadorAnguloFSM = 0;
	contadorDisparosFSM = 0;
	contadorAnguloApuntarFSM = 0;
	velocidadTanque = 5;
	radioAtaque = 400;
	contadorIntervaloDisparo = 0;
	
	isDead = false;

	estadoActual = TanqueFSM::Estados::Parar;	
	
	fx = new EfectoParticulas(TanqueX,TanqueY,0.1,0,0,10,25,80,0,0,0);
	
	fx2 = new EfectoParticulas(TanqueX,TanqueY,0.1,0,0,10,25,80,0,0,0);

	fx->SetColor(0,0,0);
	fx2->SetColor(0,0,0);
	fx->tipoEfecto = EfectoParticulasConfig::EfectoParticulasTypeFX::HuellaVehiculo;
	fx2->tipoEfecto = EfectoParticulasConfig::EfectoParticulasTypeFX::HuellaVehiculo;
}

void Tanque::Update(int dt,float target_x,float target_y)
{
	if(isDead)
	{
		//Mostrar explosion
	}
	else
	{
		//Actualizamos las posiciones de los proyectiles
		list<Bala>::iterator p = proyectil.begin();
		while( p != proyectil.end() ) {
		  //Si esta fuera del mapa o impacta con el enemigo eliminamos el proyectil
		  if( p->Update() )
			p = proyectil.erase(p);
		  else
			p++;
		}

		Mover(dt);

		//Si detecta a el avion dentro del rango visual
		if(estadoActual != TanqueFSM::Estados::Apuntar && CalcularAlcance(target_x,target_y))
		{
			estadoActual = TanqueFSM::Estados::Apuntar;
			contadorPasosFSM = 0;
		}
	
		fx->Actualizar();	
		fx2->Actualizar();
	
		if(fx->GetActivo())
		{
			double ang1=(TanqueAng)*PI/180.0;
			//ang1 += PI/2;
			 fx->SetPosicion(TanqueX+45*cosf(ang1)+65*sinf(ang1)*direccionPaso,TanqueY+45*sinf(ang1)-65*cosf(ang1)*direccionPaso);
			 fx2->SetPosicion(TanqueX-45*cosf(ang1)+65*sinf(ang1)*direccionPaso,TanqueY-45*sinf(ang1)-65*cosf(ang1)*direccionPaso);
		}
	}
}

void Tanque::RecibirImpacto(int energia)
{
	this->Energia -= Energia;
	
	if(this->Energia <= 0)
	{
		isDead = true;
	}
}

void Tanque::DibujarTanque() {
  
  DibujarCuerpo();
  
  // habilita uso de textura y selecciona la textura
  glEnable(GL_TEXTURE_1D);
  glBindTexture(GL_TEXTURE_1D,managerText->texid[Manager::TANQUE1d]);
  glPushMatrix();
  // Posiciona la oruga derecha
  glTranslatef(45.0f,0.0f, 0.0f);
  DibujarOruga(Oruga1);
  glPopMatrix();
  
  glPushMatrix();
  // Posiciona la oruga izquierda
  glTranslatef(-45.0f,0.0f, 0.0f);
  DibujarOruga(Oruga2);
  glPopMatrix();
  glDisable(GL_TEXTURE_1D); // deshabilita uso de textura
  
  glPushMatrix();
  // Posiciona el faro derecho
  glTranslatef(20.0f,70.0f, 0.0f);
  DibujarFaro();
  glPopMatrix();
  
  glPushMatrix();
  // Posiciona el faro izquierdo
  glTranslatef(-35.0f,70.0f, 0.0f);
  DibujarFaro();
  glPopMatrix();  
  
  glPushMatrix();
  // Posiciona y rota la torre 
  glRotated(ArmaAng,0,0,1);
  DibujarTorre();
 
  // Luego de aplicar la traslacion (TanqueX,TanqueY) y la rotacion (TanqueAng) inicial 
  // dibuja un punto en la posición 0,0 (es solo para ayuda)
 /* glColor3f(0.0f,0.0f,0.0f);
  glPointSize(5.0);
  glBegin(GL_POINTS);
  glVertex2d(0,0);
  glEnd();*/
  
   glPopMatrix();
}

//============================================================
// Dibuja el faro
void Tanque::DibujarFaro() {
  glColor3f(0.9f,0.8f,0.05f);
  glBegin(GL_QUADS);
  glVertex2d(0,0);
  glVertex2d(15,0);
  glVertex2d(15,10);
  glVertex2d(0,10);
  glEnd();
  
  glPushMatrix();
  glTranslatef(7.5f,7.5f, 0.0f);  
  double baseRadius=7.5; double startAngle=270; double barridoAngle=180; 
  int lod=30;
  int slices=lod, stacks=lod;  
  GLUquadricObj *q=gluNewQuadric();
  gluQuadricDrawStyle(q,GLU_FILL);
  gluPartialDisk(q,0,baseRadius,slices,stacks,startAngle,barridoAngle);  
  gluDeleteQuadric(q);
  glPopMatrix();
}

// Dibuja el canion
void Tanque::DibujarArma() {
  glPushMatrix();
  glTranslatef(0.0f,0.0f, 0.1f);
  
  glColor3f(0.2f,0.45f,0.0f);
  
  glBegin(GL_QUADS);
  glVertex2d(-6.0,0.0);
  glVertex2d(6.0,0.0);
  glVertex2d(6.0,45.0);
  glVertex2d(-6.0,45.0);
  glEnd();
  glPopMatrix();
}

// Dibuja la torre, que tiene radio 40
void Tanque::DibujarTorre() {
  glColor3f(0.2f,0.4f,0.0f);
  
  double baseRadius=40;
  int lod=30;
  int slices=lod, stacks=lod;  
  GLUquadricObj *q=gluNewQuadric();  
  // GLU_FILL, GLU_LINE, GLU_POINT or GLU_SILHOUETTE
  gluQuadricDrawStyle(q,GLU_FILL);
  gluDisk(q,0,baseRadius,slices,stacks);  
  gluDeleteQuadric(q);
  
  glColor3f(0.0f,0.1f,0.0f); 
  glPointSize(2.0);
  glBegin(GL_POINTS);
  for(double x=0; x<2*PI; x+=0.4) 
    glVertex2d(40.0*0.8*cos(x),40.0*0.8*sin(x));
  glEnd();
  
  glPushMatrix();
  glScaled(1.0,2.0+(ArmaTamanio*0.1),1.0);//glScaled(1.0,2.0,1.0);
  DibujarArma();
  glPopMatrix();
}

// Dibuja la ogura del tanque, que mide 10 x 150
void Tanque::DibujarOruga(float pos) {
  glColor3f(0.4f,0.4f,0.4f);
  glBegin(GL_QUADS);
  glTexCoord1f(pos); glVertex2d(5,75);
  glTexCoord1f(pos); glVertex2d(-5,75);
  glTexCoord1f(10+pos); glVertex2d(-5,-75);
  glTexCoord1f(10+pos); glVertex2d(5,-75);
  glEnd();
}

// Dibuja el cuerpo del tanque, que mide 80 x 140
void Tanque::DibujarCuerpo() {
  glColor3f(0.002f,0.29f,0.001f);
  glBegin(GL_QUADS);
  glVertex2d(40,70);
  glVertex2d(-40,70);
  glVertex2d(-40,-70);
  glVertex2d(40,-70);
  glEnd();
  
  glColor3f(0.001f,0.1f,0.001f);
  glLineWidth(3.0);
  glBegin(GL_LINES);
  glVertex2i(30,-55); glVertex2i(15,-55);
  glVertex2i(30,-60); glVertex2i(15,-60);
  glVertex2i(-15,-55); glVertex2i(-30,-55);
  glVertex2i(-15,-60); glVertex2i(-30,-60);
  glVertex2i(40,70); glVertex2i(-40,70);
  glEnd();  
  glLineWidth(1.0);  
  
  glPushMatrix();
  glTranslatef(-28.0f,30.0f, 0.0f);
  glRotated(90,0,0,1);
  glScaled(10,10,10);
  glColor3f(0.5,0.5,0.5);
  glLineWidth(2);
  YsDrawUglyFont("ARMY",0);
  glPopMatrix(); 


  glPushMatrix();  
  glColor3f(1.0,1.0,1.0);  
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glVertex2i(0,-60);
  glVertex2i(50,-95);
  glEnd(); 
  
  glTranslatef(90.0f,-100.0f, 0.0f);

  stringstream ss;	
  ss << Energia;
  string s;
  s = ss.str();
  s += " %";

  glRotated(-180.0,0.0,0.0,1.0); 		  

	  
  glScaled(10.0,10.0,10.0);

  YsDrawUglyFont(s.c_str(),0);

  glPopMatrix(); 

}

Tanque::~Tanque(void)
{
	delete fx;	
	delete fx2;	
}

void Tanque::Disparar()
{
	double ang1,ang3,ang2;

	ang1=(TanqueAng)*PI/180.0;
    ang3=(TanqueAng+ArmaAng)*PI/180.0;
	ang2=(ArmaAng*PI/180.0);
    //proyectil.push_back( Bala( (VehiculoX), (VehiculoY), 30, 0) );//la bala sale desde el centro del tanque
    //la bala sale desde la base del arma
    //proyectil.push_back( Bala( (TanqueX-20*Tanque_Escala*cos(ang3)), (TanqueY+20*Tanque_Escala*sin(ang3)), 10*cos(ang3), -10*sin(ang3)) );
	
	ang3 += PI/2;

    proyectil.push_back(Bala(TanqueX+cos(ang3)*90, TanqueY+sin(ang3)*90, 15*cos(ang3), 15*sin(ang3),enemigo));//la bala sale desde la base del arma
}

void Tanque::Dibujar()
{	
	if(isDead)
	{
		//Mostrar imagen de la explosion
	}
	else
	{
		fx->Dibujar();	
		fx2->Dibujar();		

		glPushMatrix();
		glTranslated(TanqueX,TanqueY,0.5);	
		glRotated(TanqueAng,0,0,1);  
		DibujarTanque();
		glPopMatrix();
		glPushMatrix();
			//Dibujamos los proyectiles
		  list<Bala>::iterator p=proyectil.begin();
		  glColor3f(0.6f,0.2f,0.0f);
		  glPointSize(10.0*Escala);
		  glBegin(GL_POINTS);
		  while( p != proyectil.end() ) {
			p->Draw();
			p++;
		  }
		  glEnd();
		glPopMatrix();
	}
}

void Tanque::Mover(int dt)
{
	double ang=TanqueAng*PI/180.0;
	
	switch(estadoActual)
	{
		case TanqueFSM::Estados::Mover:

			if(!fx->GetActivo()) 
			{
				fx->ToggleActivo();
				fx2->ToggleActivo();
			}

			if(contadorPasosFSM > 0)
			{
				//Moverse		
				/*if(direccionPaso == 1)
				{
					TanqueX-=velocidadTanque*sin(ang);
					TanqueY+=velocidadTanque*cos(ang);
					Oruga1+=0.15;
					Oruga2+=0.15;
				}
				else
				{
					TanqueX+=velocidadTanque*sin(ang);
					TanqueY-=velocidadTanque*cos(ang);
					Oruga1-=0.15;
					Oruga2-=0.15;
				}*/


				TanqueX+=-velocidadTanque*sin(ang)*direccionPaso;
				TanqueY+=velocidadTanque*cos(ang)*direccionPaso;

				Oruga1+=0.15*direccionPaso;
				Oruga2+=0.15*direccionPaso;

				contadorPasosFSM--;
			}
			else
			{
				CambiarEstado();
			}
			
			if(contadorAnguloFSM > 0)
			{
				//Girar
				if(direccionAngulo == 1)
				{
					TanqueAng+=2;
					Oruga1+=0.1;
					Oruga2-=0.1;
				}
				else
				{
					TanqueAng-=2;
					Oruga1-=0.1;
					Oruga2+=0.1;
				}
				contadorAnguloFSM--;
			}
			else
			{
				CambiarEstado();
			}
			break;
		case TanqueFSM::Estados::Apuntar:	
			if(fx->GetActivo()) 
			{
				fx->ToggleActivo();
				fx2->ToggleActivo();
			}
			if(contadorAnguloApuntarFSM > 0)
			{
				if(direccionApuntar > 0)
				{
					ArmaAng +=5;				
				}
				else if(direccionApuntar < 0)
				{
					ArmaAng -= 5;
				}							

				contadorAnguloApuntarFSM-=5;
				
				if(contadorIntervaloDisparo <= 0)
				{
					contadorIntervaloDisparo = 5;
					contadorDisparosFSM = 1;
					Disparar();	
				}
				contadorIntervaloDisparo--;
			}
			else
			{
				CambiarEstado();					
			}
			break;
		case TanqueFSM::Estados::Disparar:
			if(contadorDisparosFSM > 0)
			{
				Disparar();				
				contadorDisparosFSM--;
			}
			else
			{	
				CambiarEstado();
			}
			break;
		case TanqueFSM::Estados::Parar:
			if(fx->GetActivo()) 
			{
				fx->ToggleActivo();
				fx2->ToggleActivo();
			}
			if(contadorPasosFSM > 0)
			{
				contadorPasosFSM--;
			}else
			{
				CambiarEstado();
			}
			break;
	}
	

	//controlamos que el tanque no se alla salido del mapa
    bool isLimite = false;
	if(TanqueX > wm/2-150)
	{	
		TanqueX=wm/2-150;
		isLimite = true;
	}
    if(TanqueX < -wm/2+150) 
	{
		TanqueX=-wm/2+150;
		isLimite = true;
	}
    if(TanqueY > hm/2-150){
		TanqueY=hm/2-150;
		isLimite = true;
	}
    if(TanqueY < -hm/2+150){
		TanqueY=-hm/2+150;
		isLimite = true;
	}

	if(isLimite)
	{	
		direccionPaso = -direccionPaso;
	}	
}

void Tanque::CambiarEstado()
{
	//Si es menor a 0 se elije una nuevo estado
	if(contadorPasosFSM <= 0)
	{
		direccionAngulo = rand()%2 == 0 ? 1:-1;
		direccionPaso = rand()%2 == 0 ? 1:-1;
		contadorPasosFSM = rand()% 50 + 50;
		contadorAnguloFSM = rand()% 30;
		velocidadTanque =  rand()%10 + 3;
		switch(rand()% 2)
		{
			case 1:
				estadoActual =  TanqueFSM::Estados::Parar;
				contadorPasosFSM = contadorPasosFSM / 2;
				break;
			case 0:
				estadoActual =  TanqueFSM::Estados::Mover;						
				break;
		}		
	}
}

bool Tanque::CalcularAlcance(float target_x,float target_y)
{
	float ang = Helper::CheckVisibility(TanqueX,TanqueY,target_x,target_y,radioAtaque);
	if(ang != 0)
	{
		float current_ang =(TanqueAng+ArmaAng)*PI/180.0;

		float total = fabs(ang+current_ang);

		if(ang > current_ang)
		{
			direccionApuntar = -1; 
		}
		else if(ang < current_ang)
		{
			direccionApuntar = +1;
		}
		else
		{
			direccionApuntar = 0;
		}

		contadorAnguloApuntarFSM = total; //Calcular el angulo con respecto al avion
		return true;
	}
	return false;
}
