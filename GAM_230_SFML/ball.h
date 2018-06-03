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
#include <string>
#include "paddle.h"

using namespace sf;
using namespace std;

class ball
{
public:
	CircleShape ball1;
	paddle paddle2;
	float dt;
	float ballSpeed = 150.0f;
	int playerLives = 3;
	float increaseSpeed = 1.0f;
	Vector2f vel;
	Vector2f posPaddle;
	Vector2f posBall;
	bool isPaddle;
	Texture tex;
	SoundBuffer soundBuffLoseLife;	
	SoundBuffer soundBuffWall;	
	Sound loseLifeSound;				
	Sound hitWallSound;		


	ball();
	~ball();

	void createBall();
	void moveBall(float dt, Vector2f& vel, paddle& paddle2, bool check);
	void ballWithPaddle(Vector2f& posPaddle, float dt, Clock& timerAI, Time timeAI);
	bool collisionCheckPaddle(Vector2f& posPaddle, Vector2f& posBall, float dt, bool isPaddle);
	bool collisionCheckBrick(Vector2f& posBrick, Vector2f& posBall, float dt, bool isBrick);
	bool collisionCheckTeaHouse(Vector2f& posTeaHouse, Vector2f& posBall, float dt, bool isTeaHouse);

	Vector2f getBallPos();
};

