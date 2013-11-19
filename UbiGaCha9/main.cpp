#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Scoring.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::IpAddress ip("10.17.73.49");
	unsigned short port = 4242;
	Scoring s(ip, port);
	while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                window.close();
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			s.sendScore();
        }
        window.clear();
        window.display();
    }
	//s.setScoreList();
	return EXIT_SUCCESS;
}