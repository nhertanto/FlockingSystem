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

class vehicleSystem
{
public:

	vector<vehicle> lotsOfBirds;
	RectangleShape target;

	vehicleSystem();
	~vehicleSystem();
	void vehicleSystem::createVehicle();
	void vehicleSystem::createTarget();
	void vehicleSystem::update(float, Vector2f);
};

