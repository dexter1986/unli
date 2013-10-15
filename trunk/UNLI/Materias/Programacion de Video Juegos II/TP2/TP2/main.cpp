#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SpriteSheetManager.h"
#include "Animation.h"
#include "Nivel.h"
#include "Personaje.h"
#include "Disparos.h"

using namespace std;

int const resx=800, resy=600;

int main(int argc, char *argv[]) {
	// creamos la ventana y definimos la porcion visible del plano
	sf::RenderWindow w(VideoMode(resx,resy),"TP2");	

	Nivel nivel("../data/level1.lev");

	nivel.InitLevelView(resx, resy,10,8);
	
	//sf::FloatRect viewRect(0,0,300,150);
	View &v = nivel.GetView();
	w.SetView(v);

	w.SetFramerateLimit(30);
	// creamos e inicializamos nuestra estructura joystick
	Joystick j;
	j.up=j.down=j.left=j.right=j.a=j.b=0;
	
	//creamos el manejador para los disparos
	ManejadorDisparos disparos;
		
	Personaje prince;

	Personaje guadias[3];

	guadias[0].Inicializar(&disparos,&nivel);
	guadias[0].SetColor(Color::Red);
	guadias[0].SetPosition(384,32);
	/*guadias[1].Inicializar(&disparos,&nivel);
	guadias[2].Inicializar(&disparos,&nivel);*/


	prince.Inicializar(&disparos,&nivel);
	prince.SetPosition(64,96);
	
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
		
		// actualizamos el estado del personaje y los proyectiles
		prince.Mover_y_Animar(j,clk.GetElapsedTime());
		
		guadias[0].Mover_y_Animar(j,clk.GetElapsedTime());

		nivel.SetViewCenter(prince.GetPosition());

		disparos.MoverDisparos(clk.GetElapsedTime(), v);

		clk.Reset();
		
		// dibujamos
		w.Clear(Color(0,0,0));		
		nivel.Draw(w);
		
		//nivel.DrawGrid(w);
		
		disparos.DibujarDisparos(w);
		
		w.Draw(prince);
		w.Draw(guadias[0]);

		nivel.DrawOverLayer(w);

		/*FloatRect bb=prince.GetAABB();
		w.Draw(sf::Shape::Rectangle(bb.Left, bb.Top, bb.Right, bb.Bottom, sf::Color(0,0,0,0), 1, sf::Color(255,0,0)));*/

		
		w.Display();
	}
	return 0;
}
