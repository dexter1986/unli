#include <iostream>
#include <conio2.h>
#include <ctime>
#include <windows.h>

using namespace std;

class Auto{

private:
	
	int x;
	int y;
	
	// para dibujar 
	
	int anchoM;
	int altoM;
	void borrar();
	int Matriz[3][4];
	int Colores[3][4];
	
public:
	
	
	Auto(int,int,int);
	
	
	//para dibujar
	
	void dibujar();
	void Mover(int);

};


Auto::Auto(int x_,int y_,int color){
	x = x_;
	y = y_;
	anchoM = 3;
	altoM = 4;
	
	Matriz[0][0]=0;  Colores[0][0] = color;
	Matriz[0][1]=61; Colores[0][1] = 8;
	Matriz[0][2]=47; Colores[0][2] = color;
	Matriz[0][3]=61; Colores[0][3] = 8;
	Matriz[1][0]=30; Colores[1][0] = color;
	Matriz[1][1]=61; Colores[1][1] = 8;
	Matriz[1][2]=0;  Colores[1][2] = color;
	Matriz[1][3]=61; Colores[1][3] = 8;
	Matriz[2][0]=0;  Colores[2][0] = color;
	Matriz[2][1]=61; Colores[2][1] = 8;
	Matriz[2][2]=92; Colores[2][2] = color;
	Matriz[2][3]=61; Colores[2][3] = 8;
}

void Auto::Mover(int off){
	
	if (off == -1){x-=1;}
	if (off == 1){x+=1;}
	if (off == 2){y+=1;}
	if (off == -2){y-=1;}


}

void Auto::borrar(){
	
	textcolor(WHITE);
	
	for(int k=0;k<anchoM+2;k++){
		for(int p=0;p<altoM+2;p++){
			putchxy(x+k-1,y+p-1,0);
		}
	}
	
	textcolor(WHITE);
	
	
}




void Auto::dibujar(){

	//enum COLOR = 'BLUE';
	
	borrar();
	
	textcolor(1);
	
	for(int k=0;k<anchoM;k++){
		for(int p=0;p<altoM;p++){
			textcolor(Colores[k][p]);
			putchxy(x+k,y+p,Matriz[k][p]);
			
			
		}
	}
	
	textcolor(WHITE);


}



int main(int argc, char *argv[]) {
	
	Auto A1(4,10,4);
	Auto A2(5,20,2);
	Auto A3(15,20,14);
	
	A1.dibujar();
	A2.dibujar();
	A3.dibujar();
	
	
	
while(true){
	

	
		if(kbhit()) { 
			int tecla=getch();
		switch(tecla)
		{

		case 75:
				A1.Mover(-1);
		break;
			
		case 77:
			A1.Mover(1);
		break;
		
		case 72:
			A1.Mover(-2);
		break;
		
		case 80:
			A1.Mover(2);
		break;
		
		case 'a': return 1;
		}
		
		A1.dibujar();
		
	}
	
	
	
}
	
	
	return 0;
}
