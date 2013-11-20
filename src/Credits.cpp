#include "UbiException.hh"
#include "Credits.hh"
#include "Game.hh"
#include <iostream>

Credits::Credits(sf::RenderWindow &window)
: _window(window), _state(WHO)
{
	std::string	path = "./ressource/font/arial.ttf";
	if (!_font.loadFromFile(path))
		throw UbiException("Error load Font");

	_select.loadFromFile("./ressource/quit.png");
	_music.openFromFile("./ressource/sounds/credits.wav");
	_music.setLoop(true);
	_music.play();
}

bool	Credits::update(sf::Event & event)
{
	if (event.type == sf::Event::JoystickButtonPressed)
	{
		if (event.joystickButton.button == 7)
			return (false);
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Return)
			return (false);
	}
	if (event.type == sf::Event::KeyReleased)
	{
		return (false);
	}
	return (true);
}

void	Credits::draw()
{
	_text.setFont(_font);
	_text.setCharacterSize(10);
	_text.setColor(sf::Color::White);
	_text.setString("Credits:\n\n4 Programmeurs\n\nJean Ludovic\nBenjamin Jean-Sebastien\n\n2 Sound Designers\n\nGuillaume Paul\n\n2 Graphistes\n\nIbrahim Nathanael\n\n3 Game Designer\n\nRaoul Pierre Maxime");
	_text.setPosition(75, 0);
	_window.draw(_text);


	_sprite.setTexture(_select);
	_sprite.setColor(sf::Color::White);
	_sprite.setPosition(220, 200);
	_sprite.setScale(0.2, 0.2);
	_window.draw(_sprite);

}

void	Credits::run()
{
	while (_window.isOpen())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Return)
				_state = MENU;
		}
		if (_state == MENU)
			return;
		this->update(event);
		_window.clear();
		this->draw();
		_window.display();
	}
}
