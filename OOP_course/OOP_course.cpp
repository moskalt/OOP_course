#include <SFML/Graphics.hpp>
#include <iostream>
#include "shape.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "OOP");
	window.setFramerateLimit(60);
	Star star(&window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		window.clear(sf::Color::Cyan);
		star.aroundRotaion();
		star.centerRotation();
		star.drawStar();
		window.display();
	}

	return 0;
}

