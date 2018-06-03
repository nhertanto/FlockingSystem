#pragma once
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

class brick
{
public:

	//Invisible brick that can't be destroyed.(acts as a collider for the Tea House)
	RectangleShape teaHouseBrick;
	
	//Invisible bricks that can't be seen by the player.
	RectangleShape invisibleBrick1;
	RectangleShape invisibleBrick2;


	brick();
	~brick();

	void createTeaHouseBrick();
	Vector2f getTeaHousePos();
	
	void createInvisBrick1();
	Vector2f getInvisBrick1();
	void setInvisBrick1();
	
	void createInvisBrick2();
	Vector2f getInvisBrick2();
	void setInvisBrick2();

};

