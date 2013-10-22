#include "ManagerTexture.h"

ManagerTexture::ManagerTexture()
{
	
	
}

ManagerTexture::~ManagerTexture()
{

}

void ManagerTexture::LoadTexture(void)
{	
  
  

  glGenTextures(5,texid);

  //textura 1D
  glBindTexture(GL_TEXTURE_1D, texid[Manager::TANQUE1d]);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  makeStripeImage();  
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);//GL_REPEAT//GL_CLAMP
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);//GL_LINEAR
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);//GL_LINEAR
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_DECAL);//GL_DECAL//GL_REPLACE
  glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  

  glBindTexture(GL_TEXTURE_2D, texid[Manager::AVION]);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  Helper::mipmap_ppm("pista.ppm");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  // textura
  // textura1
  glBindTexture(GL_TEXTURE_2D, texid[Manager::CUBO]);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  Helper::mipmap_ppm("cubo.ppm");  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);  
  
  ////Textura 2
  glBindTexture(GL_TEXTURE_2D, texid[Manager::PASTO]);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  Helper::mipmap_ppm("grass.ppm");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

   ////Textura 2
  glBindTexture(GL_TEXTURE_2D, texid[Manager::TANQUE_BLAST]);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  Helper::mipmap_ppm("Scorch.ppm");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  

}

void ManagerTexture::makeStripeImage(void){
  int j, rojo,verde,azul,alpha;
  for (j = 0; j < stripeImageWidth; j++){
    alpha=255;
    if(j<16) {rojo=64;verde=32;azul=0;}else{rojo=32;verde=16;azul=0;}
    stripeImage[j][0] = (GLubyte) rojo;
    stripeImage[j][1] = (GLubyte) verde;
    stripeImage[j][2] = (GLubyte) azul;
    stripeImage[j][3] = (GLubyte) alpha;
  }
}