#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>

#define WIDTH 800
#define HEIGTH 600


int main()
{
	
	sf::RenderWindow App(sf::VideoMode(WIDTH,HEIGTH,32),"Atrapado");
	const sf::Input& in = App.GetInput();
	sf::Event Event;

	sf::Image mat,mat2;
	sf::Sprite sprite;
	sf::Vector2f vect;
	
	bool isMat = false;

	mat.LoadFromFile("..\\imagenes\\cuad_blue.png");
	mat2.LoadFromFile("..\\imagenes\\rcircle.png");

	sprite.SetImage(mat);

	sprite.SetPosition((WIDTH - sprite.GetSize().x)/2,(HEIGTH - sprite.GetSize().y)/2);

	while(App.IsOpened())
	{
		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();

			if(Event.Type == sf::Event::KeyPressed)
			{
				if(Event.Key.Code == sf::Key::Space)
				{		
					if(isMat)			
						sprite.SetImage(mat);
					else
						sprite.SetImage(mat2);

					isMat = !isMat;				
				}
			}
		}

		if(in.IsKeyDown(sf::Key::Escape))
			App.Close();

		vect.x = 0;
		vect.y = 0;

		

		if(in.IsKeyDown(sf::Key::Left))
			vect.x = -1;
		if(in.IsKeyDown(sf::Key::Right))
			vect.x = 1;
		if(in.IsKeyDown(sf::Key::Up))
			vect.y = -1;
		if(in.IsKeyDown(sf::Key::Down))
			vect.y = 1;
		
		if(sprite.GetPosition().x + vect.x < 0 || sprite.GetPosition().x + sprite.GetSize().x + vect.x > WIDTH)
			vect.x = 0;
		if(sprite.GetPosition().y + vect.y < 0 || sprite.GetPosition().y + sprite.GetSize().y + vect.y > HEIGTH)
			vect.y = 0;

		sprite.Move(vect);

		App.Clear();

		App.Draw(sprite);

		App.Display();

	}

	return 0;
}