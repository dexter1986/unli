#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

sf::Image img;
sf::Sprite sprite;
int main()
{
	img.LoadFromFile("..\\Imagenes\\chessw.png");
	sprite.SetImage(img);

	sf::RenderWindow App(sf::VideoMode(800,600,32),"ventana");
	
	sprite.SetPosition((App.GetWidth()-img.GetWidth())/2,(App.GetHeight()-img.GetHeight())/2);
	
	while(App.IsOpened())
	{
		App.Clear();		
		sprite.Rotate(1);
		App.Draw(sprite);
				
		App.Display();
	}

	return 0;
}