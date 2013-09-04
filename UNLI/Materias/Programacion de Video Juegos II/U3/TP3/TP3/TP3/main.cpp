#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SpriteSheetManager.h"
#include "Animation.h"
#include "Megaman.h"
#include "Disparos.h"
#include "Prince.h"

using namespace std;

int main(int argc, char *argv[]) {
	// creamos la ventana y definimos la porcion visible del plano
	sf::RenderWindow w(VideoMode(1000,500),"Prince");
	sf::FloatRect viewRect(0,0,300,150);
	sf::View v(viewRect);
	w.SetView(v);
	
	// creamos e inicializamos nuestra estructura joystick
	Joystick j;
	j.up=j.down=j.left=j.right=j.a=j.b=0;
	
	// creamos el manejador para los disparos
	//ManejadorDisparos disparos;
	
	// creamos e inicializamos a megaman
	//Megaman megaman(&disparos);
	//megaman.SetPosition(150,100);
	
	Prince prince;
	prince.Inicializar();
	prince.SetPosition(150,80);
	
	sf::Clock clk;
	sf::Event e;
	
	while(w.IsOpened()) {
		while(w.GetEvent(e)) {
			if(e.Type == e.Closed)
				w.Close();
			
			// actualizamos el estado del joystick segun los eventos
			if (e.Type == sf::Event::KeyPressed){
				switch(e.Key.Code){
					case sf::Key::Up:		j.up=true; break; 
					case sf::Key::Down: 	j.down=true; break; 
					case sf::Key::Left: 	j.left=true; break; 
					case sf::Key::Right: 	j.right=true; break; 
					case sf::Key::A: 		j.a=true; break; 
					case sf::Key::S: 		j.b=true; break;
				}
			}
			
			if (e.Type == sf::Event::KeyReleased){
				switch(e.Key.Code){
					case sf::Key::Up:		j.up=false; break; 
					case sf::Key::Down: 	j.down=false; break; 
					case sf::Key::Left: 	j.left=false; break; 
					case sf::Key::Right: 	j.right=false; break; 
					case sf::Key::A: 		j.a=false; break; 
					case sf::Key::S: 		j.b=false; break;
				}
			}
			
		}
		
		// actualizamos el estado de Megaman y los proyectiles
		//megaman.Mover_y_Animar(j, clk.GetElapsedTime());
		//disparos.MoverDisparos(clk.GetElapsedTime(), viewRect);
		prince.Mover_y_Animar(j,clk.GetElapsedTime());
		clk.Reset();
		
		// dibujamos
		w.Clear(Color(255,255,255));
		//disparos.DibujarDisparos(w);
		//w.Draw(megaman);
		w.Draw(prince);
		w.Display();
	}
	return 0;
}
