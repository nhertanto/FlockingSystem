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

using namespace sf;

class paddle
{
public:
	RectangleShape paddle1;
	Clock clock;
	float dt;
	Vector2f posPaddle;
	Vector2f ballPos;
	Texture texPlayer;
	Texture texAI;

	paddle::paddle();
	~paddle();
	
	void createPaddle();
	void moveLEFT(float dt);
	void moveRIGHT(float dt);

	Vector2f getPaddlePos();
};


