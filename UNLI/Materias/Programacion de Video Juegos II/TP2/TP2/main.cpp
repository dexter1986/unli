#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SpriteSheetManager.h"
#include "Animation.h"
#include "Nivel.h"
#include "Personaje.h"
#include "Disparos.h"

using namespace std;

int const resx=800, resy=600;

void IntLevel(ManejadorDisparos &disparos,Personaje &prince,string fileLevel,RenderWindow &w, Nivel &nivel);

int main(int argc, char *argv[]) {
	
	// creamos la ventana y definimos la porcion visible del plano
	sf::RenderWindow w(VideoMode(resx,resy),"TP2");	
	w.SetFramerateLimit(60);
	
	// creamos e inicializamos nuestra estructura joystick
	Joystick j;
	j.up=j.down=j.left=j.right=j.a=j.b=0;
	
	//creamos el manejador para los disparos
	ManejadorDisparos disparos;

	Personaje prince;
	
	Personaje guardia;
	

	Nivel nivel;

	IntLevel(disparos,prince,"../data/level1.lev",w,nivel);
	View &v = w.GetDefaultView();
	
	prince.Inicializar(&disparos,&nivel);
	guardia.Inicializar(&disparos,&nivel);
	guardia.SetColor(Color::Red);
	guardia.SetPosition(384,32);

	/*Nivel nivel("../data/level1.lev");*/
	/*nivel.InitLevelView(resx, resy,10,8);*/
	
	//= nivel.GetView();
	//w.SetView(v);
	//prince.Inicializar(&disparos,&nivel);

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
		
		guardia.Mover_y_Animar_NPC(clk.GetElapsedTime());

		nivel.SetViewCenter(prince.GetPosition());

		disparos.MoverDisparos(clk.GetElapsedTime(), v);

		clk.Reset();
		
		// dibujamos
		w.Clear(Color(0,0,0));		
		nivel.Draw(w);
		
		//nivel.DrawGrid(w);
		
		disparos.DibujarDisparos(w);
		
		w.Draw(prince);
		w.Draw(guardia);

		nivel.DrawOverLayer(w);

		/*FloatRect bb=prince.GetAABB();
		w.Draw(sf::Shape::Rectangle(bb.Left, bb.Top, bb.Right, bb.Bottom, sf::Color(0,0,0,0), 1, sf::Color(255,0,0)));*/
				
		w.Display();

		if(nivel.isNeedNextLoadLevel)
		{
			string file = nivel.fileNextLevel;						
			IntLevel(disparos,prince,file,w,nivel);
		}
	}	
	return 0;
}

void IntLevel(ManejadorDisparos &disparos, Personaje &prince, string fileLevel, RenderWindow &w, Nivel &nivel)
{
	disparos.Init();
	nivel.Load(fileLevel);
	nivel.InitLevelView(resx, resy,10,8);
	View &v = nivel.GetView();
	w.SetView(v);
	prince.SetPosition(nivel.vEntryPoint);
}
