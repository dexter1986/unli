#ifndef HELPER_H
#define HELPER_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <cmath>

using namespace std;

const double PI=4*atan(1.0);
const int wm=10000, hm=10000;
extern float Escala;
class Helper
{
private:
public:

	void static print_text(string cadena, int x, int y, int espacio=10) {
		for(unsigned int i=0; i < cadena.size(); i++) {
			glRasterPos2i( x + i*espacio, y );
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,(int)cadena[i]);//GLUT_BITMAP_9_BY_15//GLUT_BITMAP_TIMES_ROMAN_10
		}
	}

	// Load a PPM Image
	bool static mipmap_ppm(const char *ifile){
	  char dummy; int maxc,wt,ht;
	  ifstream fileinput(ifile, ios::binary);
	  if (!fileinput.is_open()) {cerr<<"Not found"<<endl; return false;}
	  fileinput.get(dummy);
	  if (dummy!='P') {cerr<<"Not P6 PPM file"<<endl; return false;}
	  fileinput.get(dummy);
	  if (dummy!='6') {cerr<<"Not P6 PPM file"<<endl; return false;}
	  fileinput.get(dummy);
	  dummy=fileinput.peek();
	  if (dummy=='#') do {
		fileinput.get(dummy);
	  } while (dummy!=10);
	  fileinput >> wt >> ht;
	  fileinput >> maxc;
	  fileinput.get(dummy);
  
	  unsigned char *img=new unsigned char[3*wt*ht];
	  fileinput.read((char *)img, 3*wt*ht);
	  fileinput.close();
	  //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, wt, ht,  GL_RGB, GL_UNSIGNED_BYTE, img);
	  // conversion a rgba alpha=255-(r+g+b)/3 (blanco=transparente, negro=opaco)
	  unsigned char *imga=new unsigned char[4*wt*ht];
	  unsigned char r,g,b;
	  for (int i=0;i<wt*ht;i++){
		r=imga[4*i+0]=img[3*i+0];
		g=imga[4*i+1]=img[3*i+1];
		b=imga[4*i+2]=img[3*i+2];
		imga[4*i+3]=((r+g+b==765)? 0: 255);
		//imga[4*i+3]=255-(r+g+b)/3;
	  }
	  delete[] img;
	  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, wt, ht,  GL_RGBA, GL_UNSIGNED_BYTE, imga);
	  delete[] imga;
	  return true;
	}

	//Si el objetivo esta en alcance retorna el angulo de separacion en radianes
	float static CheckVisibility(float posicion_x,float posicion_y,float target_x,float target_y,float max_distancia)
	{
		//Calcular distancia
		float d_x = target_x - posicion_x;
		float d_y = target_y - posicion_y;
		float d = sqrtf(powf(d_x,2)+powf(d_y,2));
		
		if(d < max_distancia)
		{
			float phi= atan((target_y - posicion_y)/(target_y - posicion_x));
			if(target_x-posicion_x<0)
			{
			   phi = phi + PI;
			}
			return phi;
		}
		return 0;
	}
};

#endif