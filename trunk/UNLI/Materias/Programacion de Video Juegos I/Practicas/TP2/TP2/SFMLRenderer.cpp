#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\OpenGL.hpp>

#include "SFMLRenderer.h"

using namespace sf;

SFMLRenderer::SFMLRenderer(RenderWindow *window)
{
	wnd=window;
}


SFMLRenderer::~SFMLRenderer(void)
{
}

void SFMLRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){

	sf::VertexArray lines(sf::LinesStrip, vertexCount+1);
	Color c = box2d2SFMLColor(color);

	for(int i=0;i<vertexCount;i++){
		lines[i].position.x = vertices[i].x;
		lines[i].position.y = vertices[i].y;
		lines[i].color = c;
	}	

	lines[vertexCount].position.x = vertices[0].x;
	lines[vertexCount].position.y = vertices[0].y;
	lines[vertexCount].color = c;

	wnd->draw(lines);		
}

void SFMLRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){

	ConvexShape poligono;
	
	poligono.setPointCount(vertexCount);

	for(int i=0;i<vertexCount;++i){		
		poligono.setPoint(i,Vector2f(vertices[i].x, vertices[i].y));		
	}

	poligono.setFillColor(box2d2SFMLColor(color));
	
	wnd->draw(poligono);

}

void SFMLRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color){

	CircleShape circulo(radius);
		
	circulo.setOutlineColor(box2d2SFMLColor(color));
	circulo.setOutlineThickness(1.0f);

	circulo.setPosition(center.x-radius, center.y-radius);

	wnd->draw(circulo);

}

void SFMLRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){

	CircleShape circulo(radius);		
	circulo.setFillColor(box2d2SFMLColor(color));	
	circulo.setPosition(center.x-radius, center.y-radius);

	wnd->draw(circulo);

}

void SFMLRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){
	
	Color c = box2d2SFMLColor(color);
	sf::VertexArray lines(sf::Lines, 2);
	lines[0].position = sf::Vector2f(p1.x, p1.y);
	lines[0].color = c;
	lines[1].position = sf::Vector2f(p2.x,p2.y);
	lines[1].color = c;
	
	wnd->draw(lines);	
}

void SFMLRenderer::DrawTransform(const b2Transform& xf){

	b2Vec2 p1 = xf.position, p2;
	const float32 k_axisScale = 20.0f;
	p2 = p1 + k_axisScale * xf.R.col1;


	sf::Vertex Point[1]=
	{
		sf::Vector2f(p2.x, p2.y)
	};

	wnd->draw(Point,1,sf::Points);
	 
	
	sf::VertexArray LineX(sf::Lines, 2);
	LineX[0].position = sf::Vector2f(p1.x, p1.y);
	LineX[0].color = Color::Red;
	LineX[1].position = sf::Vector2f(p2.x,p2.y);
	LineX[1].color = Color::Red;

	wnd->draw(LineX);

	p2 = p1 + k_axisScale * xf.R.col2;

	sf::VertexArray LineY(sf::Lines, 2);
	LineY[0].position = sf::Vector2f(p1.x, p1.y);
	LineY[0].color = Color::Green;
	LineY[1].position = sf::Vector2f(p2.x,p2.y);
	LineY[1].color = Color::Green;

	wnd->draw(LineY);
}

Color SFMLRenderer::box2d2SFMLColor(const b2Color& _color){	
	
	Uint8 R,G,B;
	R=(Uint8)(_color.r*255);
	G=(Uint8)(_color.g*255);
	B=(Uint8)(_color.b*255);

	return Color(R,G,B);

}