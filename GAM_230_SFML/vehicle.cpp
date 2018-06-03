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

vehicle::vehicle(Vector2f location)
{
	//Vehicle's constant variables
	birdSan.setPointCount(3);
	birdSan.setFillColor(Color(10, 25, 30));

	//Vehicle's current locations
	loc = location;

	currentVel = currentVel * 0.0f;
}

vehicle::~vehicle()
{
}

Vector2f vehicle::seek(Vector2f target)
{
	Vector2f desiredVelocity = target - loc;
	
	float length = sqrt(pow(desiredVelocity.x, 2) + pow(desiredVelocity.y, 2));
	if (length != 0)
		desiredVelocity /= length;

	if (length < 100)
	{
		float m = length/100;
		desiredVelocity = desiredVelocity * m;
	}
	else
	{
		desiredVelocity = desiredVelocity * maxSpd;
	}

	//Stay within the walls
	//if (loc.x > 25 && loc.x < 475 && loc.y > 25 && loc.y < 475)
	//{
		Vector2f steerForce = desiredVelocity - currentVel;

		//No bueno stuff
		if (maxForce < steerForce.x)
			steerForce.x = maxForce;
		if (maxForce < steerForce.y)
			steerForce.y = maxForce;
		if (-maxForce > steerForce.x)
			steerForce.x = -maxForce;
		if (-maxForce > steerForce.y)
			steerForce.y = -maxForce;

		return steerForce;
	//}
	
}

void vehicle::applyForce(Vector2f steerForce)
{
	accel = steerForce + accel;
}

void vehicle::update(float dt)
{
	//Adding acceleration by the velocity
	currentVel = currentVel + accel * dt;
	
	//Limit the current velocity by the max speed
	if (maxSpd < currentVel.x)
		currentVel.x = maxSpd;
	if (maxSpd < currentVel.y)
		currentVel.y = maxSpd;
	if (-maxSpd > currentVel.x)
		currentVel.x = -maxSpd;
	if (-maxSpd > currentVel.y)
		currentVel.y = -maxSpd;

	//Limit where vehicles can go
	if (loc.x > 490 || loc.x < 0)
	{
		currentVel.x = -currentVel.x;
	}
	if (loc.y > 490 || loc.y < 0)
	{
		currentVel.y = -currentVel.y;
	}

	//Adding the location by the velocity
	loc = loc + currentVel;

	//Reset acceleration by 0
	accel = accel * 0.0f;

}

void vehicle::display()
{
	birdSan.setPoint(0, sf::Vector2f(loc.x, loc.y));
	birdSan.setPoint(1, sf::Vector2f(radius + loc.x, radius*2 + loc.y));
	birdSan.setPoint(2, sf::Vector2f(-radius + loc.x, radius*2 + loc.y));
	birdSan.setPosition(loc);;
	birdSan.setOrigin(loc.x,loc.y - radius);
}

void vehicle::applyBehaviors(vector<vehicle> lotsOfBirds, Vector2f target)
{
	Vector2f separation = separate(lotsOfBirds);
	Vector2f seek2 = seek(target);

	separation = separation * 1.5f;
	seek2 = seek2 * 0.5f;

	applyForce(separation);
	applyForce(seek2);

}

Vector2f vehicle::separate(vector<vehicle> lotsOfBirds)
{
	float desiredSeparation = radius * 2;
	Vector2f sum;
	float count = 0.0f;
	for (int i = 0; i < lotsOfBirds.size(); i++)
	{
		float d = sqrt((loc.x - lotsOfBirds[i].loc.x)
			+ (loc.y - lotsOfBirds[i].loc.y));
		if ((d > 0.0f) && d < desiredSeparation)
		{
			Vector2f diff = loc - lotsOfBirds[i].loc;
			float magnitude = sqrt(pow(diff.x, 2) + pow(diff.y, 2));
			diff.x = diff.x / magnitude;
			diff.y = diff.y / magnitude;
			sum = sum + diff;
			count++;
		}
	}
	if (count > 0.0f)
	{
		sum.x = sum.x / count;
		sum.y = sum.y / count;
		
		float magnitude = sqrt(pow(sum.x, 2) + pow(sum.y, 2));
		
		sum.x = sum.x / magnitude;
		sum.y = sum.y / magnitude;
		
		sum = sum * maxSpd;
		
		Vector2f steer = sum - currentVel;
		
		//Limit the steer with the max force
		if (maxForce < steer.x)
			steer.x = maxForce;
		if (maxForce < steer.y)
			steer.y = maxForce;
		if (-maxForce > steer.x)
			steer.x = -maxForce;
		if (-maxForce > steer.y)
			steer.y = -maxForce;

		return steer;
	}
	else
	{
		return Vector2f(0.0f, 0.0f);
	}
}

Vector2f vehicle::align(vector<vehicle> lotsOfBirds)
{
	float neighbordist = 50.0f;
	Vector2f sum;
	float count = 0.0f;
	for (int i = 0; i < lotsOfBirds.size(); i++)
	{
		float d = sqrt((loc.x - lotsOfBirds[i].loc.x)
			+ (loc.y - lotsOfBirds[i].loc.y));
		if ((d > 0.0f) && d < neighbordist)
		{
			Vector2f diff = loc - lotsOfBirds[i].loc;
			float magnitude = sqrt(pow(diff.x, 2) + pow(diff.y, 2));
			diff.x = diff.x / magnitude;
			diff.y = diff.y / magnitude;
			sum = sum + diff;
			count++;
		}
	}
	if (count > 0.0f)
	{
		sum.x = sum.x / count;
		sum.y = sum.y / count;

		float magnitude = sqrt(pow(sum.x, 2) + pow(sum.y, 2));

		sum.x = sum.x / magnitude;
		sum.y = sum.y / magnitude;

		sum = sum * maxSpd;

		Vector2f steer = sum - currentVel;

		//Limit the steer with the max force
		if (maxForce < steer.x)
			steer.x = maxForce;
		if (maxForce < steer.y)
			steer.y = maxForce;
		if (-maxForce > steer.x)
			steer.x = -maxForce;
		if (-maxForce > steer.y)
			steer.y = -maxForce;

		return steer;
	}
	else
	{
		return Vector2f(0.0f, 0.0f);
	}
}

Vector2f vehicle::cohesion(vector<vehicle> lotsOfBirds)
{
	float neighbordist = 50.0f;
	Vector2f sum;
	float count = 0.0f;
	for (int i = 0; i < lotsOfBirds.size(); i++)
	{
		float d = sqrt((loc.x - lotsOfBirds[i].loc.x)
			+ (loc.y - lotsOfBirds[i].loc.y));
		if ((d > 0.0f) && d < neighbordist)
		{
			sum = sum + lotsOfBirds[i].loc;
			count++;
		}
	}
	if (count > 0.0f)
	{
		sum.x = sum.x / count;
		sum.y = sum.y / count;

		return seek(sum);
	}
	else
	{
		return Vector2f(0.0f, 0.0f);
	}
}

void vehicle::flock(vector<vehicle> lotsOfBirds)
{
	Vector2f sep = separate(lotsOfBirds);
	Vector2f ali = align(lotsOfBirds);
	Vector2f coh = cohesion(lotsOfBirds);

	sep = sep * 1.5f;
	ali = ali * 1.0f;
	coh = coh * 1.0f;

	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}