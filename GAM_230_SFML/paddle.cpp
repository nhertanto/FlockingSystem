#include "paddle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <cmath>
#include <ctime>
#include "ball.h"


using namespace sf;

paddle::paddle()
{
}

paddle::~paddle()
{
}

//CREATE PLAYER'S PADDLE
void paddle::createPaddle()
{
	texPlayer.loadFromFile("samurai.png");

	//Creating the player's paddle
	paddle1.setSize(Vector2f(80, 80));
	paddle1.setOrigin(40, 40); 
	paddle1.setPosition(250, 460);
	paddle1.setFillColor(sf::Color::White);
	paddle1.setTexture(&texPlayer);
}
//Gets the paddle's position
Vector2f paddle::getPaddlePos()
{
	return paddle1.getPosition();
}

//Allows paddle to move left
void paddle::moveLEFT(float dt)
{
	Vector2f pos = paddle1.getPosition();
	
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		pos.x -= 200 * dt;
		if (pos.x < 30)
		{
			pos.x = 30;
		}
	}
	paddle1.setPosition(pos);
}
//Allows paddle to move right
void paddle::moveRIGHT(float dt)
{
	Vector2f pos = paddle1.getPosition();

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		pos.x += 200 * dt;
		if (pos.x > 460)
		{
			pos.x = 460;
		}
	}
	paddle1.setPosition(pos);
}



