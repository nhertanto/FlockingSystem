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
#include "brick.h"

using namespace sf;

ball::ball()
{
}

ball::~ball()
{
}

//Creating the ball
void ball::createBall()
{
	tex.loadFromFile("bomb.png");

	ball1.setRadius(12);
	ball1.setOrigin(12,12);  
	ball1.setFillColor(sf::Color::White);
	ball1.setPosition(250, 430);
	ball1.setTexture(&tex);

	playerLives = 3;
}
//Gets the ball's position
Vector2f ball::getBallPos()
{
	return ball1.getPosition();
}
//Moving the ball with the paddle in the beginning, press start to begin game
void ball::ballWithPaddle(Vector2f& posPaddle, float dt, Clock& timerAI, Time timeAI)
{
	Vector2f pos = ball1.getPosition();
	if (true)
	{
		timerAI.restart();
		if (pos.y < 405)
		{
			pos.y = 405;
		}
		if (posPaddle.x > pos.x && pos.x + 40 < 500)
		{
			pos.x += 200 * dt;
		}
		if (posPaddle.x < pos.x && pos.x > 35)
		{
			pos.x -= 200 * dt;
		}
	}
	ball1.setPosition(pos);
	//After this, start the game by pressing space
}
//Allows the ball to move
void ball::moveBall(float dt, Vector2f& vel, paddle& paddle2, bool check)
{	
	posBall = getBallPos();
	posPaddle = paddle2.getPaddlePos();
	if (check || posBall.y > 400) {
		posBall += vel * dt;
	}

	Clock clock;
	Clock timerAI;
	Time timeAI;
	
	//To get ball to bounce off walls
	if (posBall.y - 12 <= 0 && vel.y < 0)
	{
		vel.y = -vel.y;
		hitWallSound.play();
	}
	if (posBall.x + 12 >= 500 && vel.x > 0)
	{
		vel.x = -vel.x;
		hitWallSound.play();
	}
	if (posBall.x - 12 <= 0 && vel.x < 0)
	{
		vel.x = -vel.x;
		hitWallSound.play();
	}
	
	//If ball hits x walls, that player loses
	if (posBall.y + 12 >= 500 && vel.y > 0)
	{
		//Start the ball & paddle at the center
		posBall.x = 250;
		posBall.y = 430;
		posPaddle.x = 250;
		posPaddle.y = 460;
		playerLives--;
		loseLifeSound.play();
	}

	ball1.setPosition(posBall);
	paddle2.paddle1.setPosition(posPaddle);
}

//Collision with the paddle
bool ball::collisionCheckPaddle(Vector2f& posPaddle, Vector2f& posBall, float dt, bool isPaddle)
{
	//To get ball to bounce off paddle
	if (posBall.x - 12 <= posPaddle.x + 40 && posBall.x + 12 >= posPaddle.x - 40 &&
		posBall.y  <= posPaddle.y + 40     && posBall.y >= posPaddle.y - 40      && isPaddle)
	{
		return true;
	}
	return false;
}
//Collision with the Brick
bool ball::collisionCheckBrick(Vector2f& posBrick, Vector2f& posBall, float dt, bool isBrick)
{
	//To get ball to bounce off paddle
	if (posBall.x - 12 <= posBrick.x + 40 && posBall.x + 12 >= posBrick.x - 40 &&
		posBall.y <= posBrick.y + 40 && posBall.y >= posBrick.y - 40 && isBrick)
	{
		return true;
	}
	return false;
}
//Collision with the Tea House
bool ball::collisionCheckTeaHouse(Vector2f& posTeaHouse, Vector2f& posBall, float dt, bool isTeaHouse)
{
	//To get ball to bounce off paddle
	if (posBall.x - 12 <= posTeaHouse.x + 80 && posBall.x + 12 >= posTeaHouse.x - 80 &&
		posBall.y <= posTeaHouse.y + 55 && posBall.y >= posTeaHouse.y - 55 && isTeaHouse)
	{
		return true;
	}
	return false;
}

