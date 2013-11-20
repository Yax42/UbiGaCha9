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

	if (!_fontText.loadFromFile("./ressource/textures/credits.png"))
		throw UbiException("Error load credits");
	if (!_select.loadFromFile("./ressource/textures/quit.png"))
			throw UbiException("Error load quit");
	if (!_music.openFromFile("./ressource/sounds/Credits.wav"))
	throw UbiException("Error load Crédits .wav");
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
	sf::Sprite s;
	s.setTexture(_fontText);
	s.setColor(sf::Color::White);
	s.setPosition(0, 0);
	_window.draw(s);

	sf::Sprite tmp;
	tmp.setTexture(_select);
	tmp.setColor(sf::Color::White);
	tmp.setPosition(220, 200);
	tmp.setScale(1, 1);
	_window.draw(tmp);

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
