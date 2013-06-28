#include <SFML/Graphics.hpp>
#include "imageManager.h"

//DECLARACION DE CONSTANTES
const int POSICION_TERRENO_Y = 500;
const int MAX_ASCENSO_SALTO_Y = 100;


bool teclaSaltoPresionada = false;
bool enAscenso = false;
bool saltoEnProceso = false;

sf::Sprite personaje;

//Se crea la ventana principal del juego
sf::RenderWindow window(sf::VideoMode(800, 600), "Juego");

//DECLARACION DE METODOS
//Verifica y controla las condiciones de salto
void actualizarSalto();

//Declaramos metodo que realiza el dibujo en pantalla de todo lo necesario
void dibujar();



//PUNTO DE ENTRADA
int main(){

	//Se crea una instancia del objeto imageManager
	imageManager img_mgr;

	//Se asigna la carpeta relativa donde se alojan nuestras imágenes
	img_mgr.addResourceDirectory("Recursos/imagenes/" );
	
	personaje.setTexture(img_mgr.getImage("jumper.png"));
	personaje.setPosition(100,POSICION_TERRENO_Y);


	//Detección de eventos de SFML
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
			}

			//La detección de tecla presionada por Evento, solo se justifica para acciones que se ejecutan no tan a menudo.
			//Por ejemplo escuchar una vez, cuando la tecla de salto se presiona, sin importar que quede presionada.
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space ){
				teclaSaltoPresionada = true;
			}else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space ){
				teclaSaltoPresionada = false;
			}


        }

		//Esta es la mejor manera de detectar teclas presionadas para cuando se necesita un movimiento constante y fluido.
		//Como por ejemplo el movimiento de un personaje.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			personaje.setPosition(personaje.getPosition().x - 1, personaje.getPosition().y);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			personaje.setPosition(personaje.getPosition().x + 1, personaje.getPosition().y);
		}


		actualizarSalto();

		//Limpia lo dibujado en ciclo anterior
        window.clear();

		dibujar();

		//Se muestra en ventana,lo nuevo que se ha dibujado con window.draw
        window.display();
    }

    return 0;
}



void actualizarSalto(){

	//Se chequea si se presionó la tecla de salto y si el proceso aún no inicio.
	if(teclaSaltoPresionada && !saltoEnProceso){
		saltoEnProceso = true;
		enAscenso = true;
	}

	//Bloque que maneja el salto y su descenso a través del eje y.
	if(saltoEnProceso){

		//Se controla cuando se llega al maximo de altura de salto
		if(personaje.getPosition().y <= POSICION_TERRENO_Y - MAX_ASCENSO_SALTO_Y){
			enAscenso = false;
		}

		//Se ejecuta el movimiento hacia arriba o abajo en eje y
		if(enAscenso){
			personaje.setPosition(personaje.getPosition().x, personaje.getPosition().y - 1);
		}else{
			personaje.setPosition(personaje.getPosition().x, personaje.getPosition().y + 1);
		}

		//Se controla cuando el personaje vuelve a tocar la eje y del terreno
		if(personaje.getPosition().y >= POSICION_TERRENO_Y){
			saltoEnProceso = false; //Permite que finalize un ciclo de salto y que comienze uno nuevo
			personaje.setPosition(personaje.getPosition().x, POSICION_TERRENO_Y); //Se fuerza la posicion del personaje en la linea de terreno
		}
	}
	
}


void dibujar(){
	window.draw(personaje);	
}