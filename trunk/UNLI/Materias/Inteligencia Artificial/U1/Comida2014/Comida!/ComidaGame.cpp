#include "ComidaGame.h"


ComidaGame::ComidaGame(void)
{
	width=600;
	height=600;
	wnd= new RenderWindow(VideoMode(width,height),"Comida!");
	tablero = new Tablero(10,5,6, width, height);
}


ComidaGame::~ComidaGame(void)
{

	delete wnd;

}


bool ComidaGame::ProcessEvents(){

	Event evt;

	while(wnd->pollEvent(evt)){
	
		switch (evt.type){
		case Event::Closed:
			wnd->close();
			return false;
			break;
		
		}
	
	
	}

	return true;
}

void ComidaGame::Loop(){

	wnd->setFramerateLimit(60);

	wnd->setVisible(true);

	while(wnd->isOpen()){
	
		if(!ProcessEvents())
			return;

		//updates
		tablero->Update();


		wnd->clear();

		//draws
		tablero->Draw(wnd);

		wnd->display();
	
	}
}