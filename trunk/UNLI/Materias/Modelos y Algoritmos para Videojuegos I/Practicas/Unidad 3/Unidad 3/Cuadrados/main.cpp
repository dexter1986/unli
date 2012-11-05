#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

sf::Image img_b;
sf::Image img_r;
sf::Image img_y;
sf::Image img_g;

sf::Sprite sprite_b;
sf::Sprite sprite_r;
sf::Sprite sprite_y;
sf::Sprite sprite_g;
int main()
{
	img_b.LoadFromFile("..\\Imagenes\\cuad_blue.png");
	img_r.LoadFromFile("..\\Imagenes\\cuad_red.png");
	img_y.LoadFromFile("..\\Imagenes\\cuad_yellow.png");
	img_g.LoadFromFile("..\\Imagenes\\cuad_grey.png");
	
	sprite_b.SetImage(img_b);
	sprite_r.SetImage(img_r);
	sprite_y.SetImage(img_y);
	sprite_g.SetImage(img_g);

	sf::RenderWindow App(sf::VideoMode(800,600,32),"ventana");	

	float s_w =  img_b.GetWidth();
	float s_h =  img_b.GetHeight();

	float c_x = App.GetWidth()/2;
	float c_y = App.GetHeight()/2;
	
	sprite_r.SetScale(s_w/img_r.GetWidth(),s_h/img_r.GetHeight());
	sprite_y.SetScale(s_w/img_y.GetWidth(),s_h/img_y.GetHeight());
	sprite_g.SetScale(s_w/img_g.GetWidth(),s_h/img_g.GetHeight());

	sprite_r.SetPosition(c_x-s_w,c_y-s_h);
	sprite_y.SetPosition(c_x,c_y-s_h);
	sprite_b.SetPosition(c_x-s_w,c_y);
	sprite_g.SetPosition(c_x,c_y);
	

	while(App.IsOpened())
	{
		App.Clear();
				
		App.Draw(sprite_r);
		App.Draw(sprite_y);
		App.Draw(sprite_b);
		App.Draw(sprite_g);
			
		App.Display();
	}

	return 0;
}
