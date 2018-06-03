#pragma once
#include "vehicleSystem.h"
#include "vehicle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <cmath>
#include <string>
#include <ctime>
#include <vector>
#include <memory>

using namespace sf;
using namespace std;

class vehicle
{
public:
	ConvexShape birdSan;
	Vector2f currentVel;
	Vector2f loc;
	Vector2f accel;
	float radius = 5.0f;
	float maxSpd = 10.0f;
	float maxForce = 0.1f;

	void vehicle::display();
	void vehicle::update(float);
	void vehicle::applyForce(Vector2f);
	Vector2f vehicle::seek(Vector2f);
	vehicle(Vector2f);
	Vector2f vehicle::separate(vector<vehicle> lotsOfBirds);
	Vector2f vehicle::align(vector<vehicle> lotsOfBirds);
	Vector2f vehicle::cohesion(vector<vehicle> lotsOfBirds);
	void vehicle::applyBehaviors(vector<vehicle>, Vector2f);
	void vehicle::flock(vector<vehicle> lotsOfBirds);

	~vehicle();
};

