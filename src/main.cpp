#include <SFML/Window.hpp>

int main()
{
	sf::Window window(sf::VideoMode(256, 240), "Blind ninja of the death doom ever the resurection is back");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.display();
	}
	return (0);
}
