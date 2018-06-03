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

vehicleSystem::vehicleSystem()
{
}


vehicleSystem::~vehicleSystem()
{
}

//Creating multiple vehicles
void vehicleSystem::createVehicle()
{
	//Set random number seed
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	//Creating 100 vehicles
	for (int i = 0; i < 20; i++)
	{
		Vector2f location;
		location.x = rand() % 475 + 25;
		location.y = rand() % 475 + 25;
		vehicle vehiclePush(location);
		lotsOfBirds.push_back(vehiclePush);
	}
}

void vehicleSystem::createTarget()
{
	target.setSize(Vector2f(5, 5));
	target.setPosition(250, 250);
	target.setFillColor(sf::Color::Blue);
}

void vehicleSystem::update(float dt, Vector2f targetPos)
{
	for (int i = 0; i < lotsOfBirds.size(); i++)
	{
		lotsOfBirds[i].applyBehaviors(lotsOfBirds, targetPos);
		lotsOfBirds[i].flock(lotsOfBirds);
		lotsOfBirds[i].separate(lotsOfBirds);
		lotsOfBirds[i].align(lotsOfBirds);
		lotsOfBirds[i].cohesion(lotsOfBirds);
		lotsOfBirds[i].seek(targetPos);
		lotsOfBirds[i].update(dt);
		lotsOfBirds[i].display();
	}
}

