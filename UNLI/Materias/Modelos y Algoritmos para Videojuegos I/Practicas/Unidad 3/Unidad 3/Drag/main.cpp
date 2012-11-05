#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

sf::Image img_r;
sf::Image img_b;
sf::Sprite sprite_r[4];
sf::Sprite sprite_b;
sf::Event Event;

int main()
{
	img_r.LoadFromFile("..\\Imagenes\\rcircle.png");
	img_b.LoadFromFile("..\\Imagenes\\bcircle.png");
	
	sprite_b.SetImage(img_b);
	sprite_r[0].SetImage(img_r);
	sprite_r[1].SetImage(img_r);
	sprite_r[2].SetImage(img_r);
	sprite_r[3].SetImage(img_r);

	sf::RenderWindow App(sf::VideoMode(800,600,32),"ventana");

	const sf::Input& in = App.GetInput();
	
	sprite_b.Scale(sprite_r[0].GetSize().x/sprite_b.GetSize().x,sprite_r[0].GetSize().y/sprite_b.GetSize().y);
	sprite_r[0].SetPosition(0,0);
	sprite_r[1].SetPosition(App.GetWidth()-img_r.GetWidth(),0);
	sprite_r[2].SetPosition(0,App.GetHeight()-img_r.GetHeight());
	sprite_r[3].SetPosition(App.GetWidth()-img_r.GetWidth(),App.GetHeight()-img_r.GetHeight());
	sprite_b.SetPosition((App.GetWidth()-sprite_b.GetSize().x)/2,(App.GetHeight()-sprite_b.GetSize().y)/2);

	int index = -1;
	int pos_x,pos_y;

	while(App.IsOpened())
	{
		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();
			
			if(index == -1 && Event.Type == sf::Event::MouseButtonPressed)
			{
				int x = Event.MouseButton.X;
				int y = Event.MouseButton.Y;
				int sx,sy;
				int w,h;
				for(int i=0;i<4;i++)
				{
					sx = sprite_r[i].GetPosition().x;
					sy = sprite_r[i].GetPosition().y;
					h = sprite_r[i].GetSize().y;
					w = sprite_r[i].GetSize().x;
					if(sx < x && sx + w > x && sy < y && sy + h > y)
					{
						index = i;
						pos_x = x;
						pos_y = y;
						break;
					}
				}
			}

			if(index > -1 && Event.Type == sf::Event::MouseButtonReleased)
			{
				index = -1;
			}
		}

		if(in.IsKeyDown(sf::Key::Escape))
			App.Close();

		if(index > -1)
		{
		   int off_x = in.GetMouseX() - pos_x;
		   int off_y = in.GetMouseY() - pos_y;
		   pos_x = in.GetMouseX();
		   pos_y = in.GetMouseY();
		   sprite_r[index].Move(off_x,off_y);		   
		}

		App.Clear();
		
		App.Draw(sprite_r[3]);
		App.Draw(sprite_r[2]);		
		App.Draw(sprite_r[1]);
		App.Draw(sprite_r[0]);
		App.Draw(sprite_b);

		App.Display();
	}

	return 0;
}