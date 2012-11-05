#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

sf::Image img_r;
sf::Image img_b;
sf::Sprite sprite_r;
sf::Sprite sprite_b;
sf::Event Event;
int main()
{
	img_r.LoadFromFile("..\\Imagenes\\rcircle.png");
	img_b.LoadFromFile("..\\Imagenes\\bcircle.png");
	
	sprite_b.SetImage(img_b);
	sprite_r.SetImage(img_r);

	sf::RenderWindow App(sf::VideoMode(800,600,32),"ventana");
	
	const sf::Input& in = App.GetInput();

	sprite_b.Scale(sprite_r.GetSize().x/sprite_b.GetSize().x,sprite_r.GetSize().y/sprite_b.GetSize().y);

	while(App.IsOpened())
	{

		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();

			if(Event.Type == sf::Event::MouseMoved){
			//	cursor.SetPosition(Event.MouseMove.X,Event.MouseMove.Y);
			}

		}

		if(in.IsKeyDown(sf::Key::Escape))
			App.Close();

		//cursor.SetPosition(in.GetMouseX(),in.GetMouseY());

		App.Clear();
		sprite_r.SetPosition(0,0);
		App.Draw(sprite_r);

		sprite_r.SetPosition(App.GetWidth()-img_r.GetWidth(),0);
		App.Draw(sprite_r);

		sprite_r.SetPosition(0,App.GetHeight()-img_r.GetHeight());
		App.Draw(sprite_r);

		sprite_r.SetPosition(App.GetWidth()-img_r.GetWidth(),App.GetHeight()-img_r.GetHeight());
		App.Draw(sprite_r);
		
		sprite_b.SetPosition((App.GetWidth()-sprite_b.GetSize().x)/2,(App.GetHeight()-sprite_b.GetSize().y)/2);
		App.Draw(sprite_b);
		App.Display();
	}

	return 0;
}