#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include "ball.h"
#include "brick.h"

using namespace sf;


brick::brick()
{
}


brick::~brick()
{
}

void brick::createTeaHouseBrick()
{
	teaHouseBrick.setSize(Vector2f(160, 110));
	teaHouseBrick.setOrigin(80, 55);
	teaHouseBrick.setPosition(250, 55);
	teaHouseBrick.setFillColor(sf::Color::Transparent);
}

Vector2f brick::getTeaHousePos()
{
	return teaHouseBrick.getPosition();
}

void brick::createInvisBrick1()
{
	invisibleBrick1.setSize(Vector2f(80, 80));
	invisibleBrick1.setOrigin(40, 40);
	invisibleBrick1.setPosition(40, 300);
	invisibleBrick1.setFillColor(sf::Color::Transparent);
}
Vector2f brick::getInvisBrick1()
{
	return invisibleBrick1.getPosition();
}
void brick::setInvisBrick1()
{
	return invisibleBrick1.setPosition(-100, -100);
}
void brick::createInvisBrick2()
{
	invisibleBrick2.setSize(Vector2f(80, 80));
	invisibleBrick2.setOrigin(40, 40);
	invisibleBrick2.setPosition(460, 300);
	invisibleBrick2.setFillColor(sf::Color::Transparent);
}
Vector2f brick::getInvisBrick2()
{
	return invisibleBrick2.getPosition();
}
void brick::setInvisBrick2()
{
	return invisibleBrick2.setPosition(-100, -100);
}