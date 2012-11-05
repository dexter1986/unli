#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<math.h>

using namespace std;

int CalcularAlpha(int x,int y);
int main()
{
	sf::Image img;
	sf::Sprite sprite;
	sf::Event Event;

	img.LoadFromFile("..\\Imagenes\\fondo.jpg");
	sprite.SetImage(img);
	sprite.SetBlendMode(sf::Blend::Mode::Alpha);

	sf::RenderWindow App(sf::VideoMode(800,600,32),"Alpha");
	
	const sf::Input& in = App.GetInput();

	float x =(float) App.GetWidth()/img.GetWidth();
	float y =(float) App.GetHeight()/img.GetHeight();

	sprite.SetScale(x,y);
	

	while(App.IsOpened())
	{
		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();
		}

		if(in.IsKeyDown(sf::Key::Escape))
		{
			App.Close();
		}
				
		App.Clear();
				
		sprite.SetColor(sf::Color(255,255,255,CalcularAlpha(in.GetMouseX(),in.GetMouseY())));
				
		App.Draw(sprite);	

		App.Display();
	}

	return 0;
}

int CalcularAlpha(int x,int y)
{
	int alpha = 255;
	float cent_x = 400.0f;
	float cent_y = 300.0f;

	float d_x = cent_x - x;
	float d_y = cent_y - y;

	float dist = sqrtf(pow(d_x,2)+pow(d_y,2));
	float dist_max = sqrtf(pow(cent_x,2)+pow(cent_y,2));

	alpha = dist * 255 / dist_max;

	return alpha;
}