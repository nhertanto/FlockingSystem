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

//Function Prototypes
void render_frame();

//Variables
RenderWindow window;	//Creating the window
RectangleShape target;	//The player's cursor


int main()
{
	//vehicle bird(Vector2f(100.0f, 100.0f));
	vehicleSystem birdSystem;

	//Create the window
	window.create(sf::VideoMode(500, 500), "Flocking!");

	//Setting the clock
	Clock clock;

	//Setting up the target
	target.setSize(Vector2f(5, 5));
	target.setPosition(250, 250);
	target.setFillColor(sf::Color::Blue);

	//Creating the bird system
	birdSystem.createVehicle();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		float dt = clock.restart().asSeconds();

		//Moving the target with W,A,S,D
		Vector2f toMove(5,5);
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			Vector2f targetPosition = target.getPosition();
			targetPosition.y -= toMove.y * dt * 50.0f;
			if (targetPosition.y < 0)
			{
				targetPosition.y = 0.0f;
			}
			target.setPosition(targetPosition);
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			Vector2f targetPosition = target.getPosition();
			targetPosition.y += toMove.y * dt * 50.0f;
			if (targetPosition.y > 490)
			{
				targetPosition.y = 490.0f;
			}
			target.setPosition(targetPosition);
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			Vector2f targetPosition = target.getPosition();
			targetPosition.x -= toMove.x * dt * 50.0f;
			if (targetPosition.x < 0)
			{
				targetPosition.x = 0.0f;
			}
			target.setPosition(targetPosition);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			Vector2f targetPosition = target.getPosition();
			targetPosition.x += toMove.x * dt * 50.0f;
			if (targetPosition.x > 490)
			{
				targetPosition.x = 490.0f;
			}
			target.setPosition(targetPosition);
		}

		render_frame();
		birdSystem.update(dt, target.getPosition());

		for (int i = 0; i < birdSystem.lotsOfBirds.size(); i++)
		{
			window.draw(birdSystem.lotsOfBirds[i].birdSan);
		}
		
		window.display();
	}
	return 0;
}
//Updates the state of the game
void update_state(float dt)
{

}

//Renders each frame of the game
void render_frame()
{
	window.clear(Color(255, 198, 216));
	window.draw(target);
}
