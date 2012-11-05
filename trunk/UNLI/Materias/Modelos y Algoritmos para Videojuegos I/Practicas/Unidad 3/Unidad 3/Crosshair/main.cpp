#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>



int main()
{
	sf::Image mat;
	sf::Sprite cursor;
	sf::Event Event;
	
	mat.LoadFromFile("..\\Img_4\\Crosshair.png");
	cursor.SetImage(mat);
	cursor.SetPosition(0,0);

	sf::RenderWindow App(sf::VideoMode(800,600,32),"Crosshair");
	const sf::Input& in = App.GetInput();
	App.ShowMouseCursor(false);
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

		cursor.SetPosition(in.GetMouseX(),in.GetMouseY());

		App.Clear();
		App.Draw(cursor);
		App.Display();
	}
	return 0;
}