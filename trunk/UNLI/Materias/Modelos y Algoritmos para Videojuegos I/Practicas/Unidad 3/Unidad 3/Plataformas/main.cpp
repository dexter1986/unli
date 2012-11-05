#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

sf::Image img;
sf::Sprite sprite;

void Draw_VSprite(int x,int y,sf::Sprite &sprite,sf::RenderWindow &app);
void Draw_HSprite(int x,int y,int count,sf::Sprite &sprite,sf::RenderWindow &app);

int main()
{
	img.LoadFromFile("..\\Imagenes\\plataforma.jpg");
	sprite.SetImage(img);
	sprite.SetScale(0.13,0.13);	

	sf::RenderWindow App(sf::VideoMode(800,600,32),"ventana");

	float s_x = sprite.GetSize().x;
	float s_y = sprite.GetSize().y;
	
	while(App.IsOpened())
	{
		App.Clear();
		
		Draw_VSprite(1,2,sprite,App);
		Draw_VSprite(3,3,sprite,App);
		Draw_VSprite(5,4,sprite,App);
		Draw_VSprite(7,5,sprite,App);
		Draw_VSprite(9,6,sprite,App);
		Draw_VSprite(11,7,sprite,App);
		Draw_VSprite(13,8,sprite,App);
		
		Draw_HSprite(15,8,8,sprite,App);

		App.Display();
	}

	return 0;
}

void Draw_VSprite(int x,int y,sf::Sprite &sprite,sf::RenderWindow &app)
{
	float s_x = sprite.GetSize().x;
	float s_y = sprite.GetSize().y;

	for(int i=0;i<y;i++)
	{
		sprite.SetPosition(s_x*x,app.GetHeight()-s_y*(i+1));		
		app.Draw(sprite);
	}
}

void Draw_HSprite(int x,int y,int count,sf::Sprite &sprite,sf::RenderWindow &app)
{
	float s_x = sprite.GetSize().x;
	float s_y = sprite.GetSize().y;

	for(int i=0;i<count;i++)
	{
		sprite.SetPosition(s_x*(i+x),app.GetHeight()-s_y*y);		
		app.Draw(sprite);
	}
}
