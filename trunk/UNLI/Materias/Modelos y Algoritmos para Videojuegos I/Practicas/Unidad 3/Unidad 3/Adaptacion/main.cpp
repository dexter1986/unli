#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>
#include<cstdio>
#include<iostream>

using namespace std;

#define WIDTH 800
#define HEIGHT 600
#define MIN 100

int main()
{
	sf::RenderWindow App(sf::VideoMode(WIDTH,HEIGHT,32),"Adaptacion");
	const sf::Input& in = App.GetInput();
	sf::Event Event;

	while(App.IsOpened())
	{	
	   
		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();

			if(Event.Type == sf::Event::Resized)
			{
				int w  = App.GetWidth();
				int h = App.GetHeight();

				if(w<100)
					w = 100;
				if(h<100)
					h = 100;

				App.SetSize(w,h);
			}
		}	

		App.Clear();
				
		App.Display();

	}

	return 0;
}
