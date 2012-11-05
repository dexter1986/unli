#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

sf::Image img;
sf::Sprite sprite;
int main()
{
	img.LoadFromFile("..\\Imagenes\\fondo.jpg");
	sprite.SetImage(img);

	sf::RenderWindow App(sf::VideoMode(800,600,32),"ventana");
	
	float x =(float) App.GetWidth()/img.GetWidth();
	float y =(float) App.GetHeight()/img.GetHeight();

	sprite.SetScale(x,y);

	while(App.IsOpened())
	{
		App.Clear();
		
		App.Draw(sprite);	

		App.Display();
	}

	return 0;
}