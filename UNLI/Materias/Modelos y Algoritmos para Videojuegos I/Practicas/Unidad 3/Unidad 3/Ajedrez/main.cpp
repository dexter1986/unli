#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

sf::Image box_b;
sf::Image box_w;

sf::Sprite sprite_b;
sf::Sprite sprite_w;

int main()
{
	box_b.LoadFromFile("..\\Imagenes\\chessb.png");
	sprite_b.SetImage(box_b);

	box_w.LoadFromFile("..\\Imagenes\\chessw.png");
	sprite_w.SetImage(box_w);

	

	sf::RenderWindow App(sf::VideoMode(800,600,32),"ventana");
	
	int count_x = App.GetWidth() / box_b.GetWidth();
	int count_y = App.GetHeight() / box_b.GetHeight();
	bool flag = true;
	bool row_f = false;

	while(App.IsOpened())
	{
		App.Clear(sf::Color(100,100,100,255));
		for(int y=0;y<count_y;y++)
		{

			if(row_f)
				flag = true;
			else
				flag = false;
			row_f = !row_f;

			for(int x=0;x<count_x;x++)
			{	
				if(flag)
				{
					sprite_b.SetPosition(box_b.GetWidth()*x,box_b.GetHeight()*y);
					App.Draw(sprite_b);
				}
				else
				{
					sprite_w.SetPosition(box_w.GetWidth()*x,box_w.GetHeight()*y);
					App.Draw(sprite_w);
				}
				flag = !flag;
			}

		}
		App.Display();
	}

	return 0;
}