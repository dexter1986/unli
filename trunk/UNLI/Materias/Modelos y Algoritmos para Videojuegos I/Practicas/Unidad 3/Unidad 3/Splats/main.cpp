#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

sf::Image img_r;
sf::Image img_b;
sf::Sprite sprite_r;
sf::Sprite sprite_b;
sf::Event Event;

class Node
{
private:
	sf::Sprite sprite;
	Node *next;
public:
	Node(sf::Image &mat,int x,int y);
	Node* Next();
	void Next(Node *node);
	sf::Sprite Sprite();
	~Node();
};

Node::Node(sf::Image &mat,int x,int y)
{
	sprite.SetImage(mat);
	sprite.SetPosition(x,y);
	next = NULL;	
};

Node::~Node()
{
	if(next != NULL)
		delete next;
}

sf::Sprite Node::Sprite()
{
	return sprite;
};

Node* Node::Next()
{
	return next;
}

void Node::Next(Node *node)
{
	next = node;
};

int main()
{
	img_r.LoadFromFile("..\\Imagenes\\rcircle.png");
	img_b.LoadFromFile("..\\Imagenes\\bcircle.png");
	sprite_b.SetImage(img_b);
	sprite_r.SetImage(img_r);

	sf::RenderWindow App(sf::VideoMode(800,600,32),"ventana");

	const sf::Input& in = App.GetInput();
	Node *current = NULL;
	Node *last = NULL;

	bool onClick = false;	

	while(App.IsOpened())
	{
		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();

		}

		if(in.IsKeyDown(sf::Key::Escape))
			App.Close();

		if(in.IsMouseButtonDown(sf::Mouse::Left))
		{
			
			sprite_r.SetPosition(in.GetMouseX(),in.GetMouseY());
			App.Draw(sprite_r);
			/*
			if(current == NULL)
			{
				current = new Node(img_r,in.GetMouseX(),in.GetMouseY());
				last = current;
			}else
			{
				last->Next(new Node(img_r,in.GetMouseX(),in.GetMouseY()));
				last = last->Next();
			}*/

		}
		if(in.IsMouseButtonDown(sf::Mouse::Right))
		{
			
			
			sprite_b.SetPosition(in.GetMouseX(),in.GetMouseY());
			App.Draw(sprite_b);
			/*
			if(current == NULL)
			{
				current = new Node(img_b,in.GetMouseX(),in.GetMouseY());
				last = current;
			}else
			{
				last->Next(new Node(img_b,in.GetMouseX(),in.GetMouseY()));
				last = last->Next();
			}*/
		}
		
		
		//App.Clear();
		/*
		if(current != NULL)
		{
			Node *index = current;
			while(index->Next() != NULL)
			{
				App.Draw(index->Sprite());
				index = index->Next();
			}
		}
		*/
		App.Display();
	}

	//delete current;

	return 0;
}