#include <constream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cmath>
using namespace conio;
using namespace std;

int main(int argc, char *argv[]) {
	
	const clock_t paso=CLOCKS_PER_SEC/16; //cada cuanto se permite mover la pelotita 16 veces por segundo
	const int bizq=1;  //limites de los bordes
	const int bder=80;
	const int bsup=1;
	const int binf=24;
	const int tam=6; //tama?o de la barra
	
	int x; //coordenada x de posici?n de barra
	int y; //coordenada y de posici?n de barra
	
	char t; //caracter de la tecla
	int px,py; //coordenadas de la pelota
	int pxa,pya; //coordenadas de la pelota anterior posici?n
	int dix,diy; //direcciones de la pelota
	clock_t tempo; //variable para ajustar la velocidad de movimiento de la pelotita

	
	_setcursortype(_NOCURSOR); //se supone que desaparece el cursor
	
	srand(time(NULL));  //se inicializa el azar
	
	py=3; //empezamos con la pelota alta (escala de coordenadas de 8*8)
	px=(rand()%40+20); //variamos un poco el comienzo en x
	
	
	dix=1; //empieza bajando hacia la derecha
	diy=1;
	
	tempo=clock(); //inicializamos tempo con el reloj
	
	x=37;
	y=20;
	
	while(true) //bucle principal de juego
	{
		//impresi?n barra
		cout<<setxy(x,y)<<setbk(LIGHTRED)<<"      "<<setbk(BLACK)<<setxy(200,200); //imprimimos la barra
		if(x>bizq) cout<<setxy(x-1,y)<<" "; //borramos el extremo izquierdo
		if(x<bder-tam+1) cout<<setxy(x+tam,y)<<" "; //borramos el extremo derecho
		
		//Detecci?n del teclado
		//No es necesario usar contador de tiempo porque la detecci?n de tecla sigue la repetici?n del teclado
		//Existen mejores metodos de detecci?n del teclado pero usamos este para ilustrar
		if(kbhit())
		{
			t=getch();
			if(t==75) //nos movemos a la izquierda
			{
				--x;
				if(x<bizq) x=bizq; //no nos pasamos del borde izquierdo de la pantalla
			}
			if(t==77) //nos movemos a la izquierda
			{
				++x;
				if(x>bder-tam+1) x=bder-tam+1; //no nos pasamos del borde derecho de la pantalla
			}
		}
		
		//movimiento de la pelotita
		//hacemos que se mueva cada paso de tiempo
		if(tempo+paso<clock())
		{
			pxa=px; //salvamos la posici?n anterior para poder borrarla
			pya=py;
			px+=dix; //avanzamos la pelotita
			py+=diy;
			if(px>bder) //vemos si llega al borde derecho
			{
				dix=-dix; //rebote en el borde derecho
				px=bder;
			}
			if(px<bizq) //vemos si llega al borde izquierdo
			{
				dix=-dix; //rebote en el borde izquierdo
				px=bizq;
			}
			if(py<bsup) //vemos si llega al borde superior
			{
				diy=-diy; //rebote arriba
				py=bsup;
			}
			if(py>binf) //vemos si llega al borde inferior
			{
				diy=-diy; //rebote abajo
				py=binf;
			}
			
			//rebote en la barra
			//vemos si entra dentro de la barra
			//para eso vamos a comparar las coordenadas de la pelotita con las coordenadas de la barra
			if((px>=x)&&(px<=x+tam)&&(py==y)) //golpea por arriba o por abajo
			{
				
				diy=-diy;
				//devolvemos a la posici?n anterior
				px=pxa;
				py=pya;				
			}
			
			//imprimimos la pelotita
			cout<<setxy(pxa,pya)<<" "; //borramos el extremo derecho
			cout<<setxy(px,py)<<"O"<<setbk(BLACK)<<setxy(200,200); //imprimimos la pelota
			tempo=clock(); // tomamos el tiempo para saber la proxima vez que movemos la pelotita
		}
	}
	return 0;
}

