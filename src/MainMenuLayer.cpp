#include "UbiException.hh"
#include "MainMenuLayer.hh"
#include "Game.hh"
#include "Scoring.hh"
#include "Credits.hh"
#include <iostream>

MainMenuLayer::MainMenuLayer(sf::RenderWindow &window)
: _window(window), _whatButton(0), _state(MENU)
{
  std::string	path = "./ressource/font/arial.ttf";
  if (!_font.loadFromFile(path))
    throw UbiException("Error load Font");
  _select.loadFromFile("./ressource/textures/puce.png");
  _noSelect.loadFromFile("./ressource/textures/menu 3.0.png");
}

bool	MainMenuLayer::update(sf::Event & event)
{

  if (event.type == sf::Event::JoystickButtonPressed)
    {
      if (event.joystickButton.button == 7)
	return (false);
    }
  if (event.type == sf::Event::KeyPressed)
  {
	  if (event.key.code == sf::Keyboard::Down && !_pressedDown)
	  {
		  if (_whatButton == 3)
			  _whatButton = 0;
		  else
			  _whatButton++;
		  _pressedDown = true;
	  }
	  if (event.key.code == sf::Keyboard::Up && !_pressedUp)
	  {
		  if (_whatButton == 0)
			  _whatButton = 3;
		  else
			  _whatButton--;
		  _pressedUp = true;
	  }
	  if (event.key.code == sf::Keyboard::Return)
	return (false);
    }
  if (event.type == sf::Event::KeyReleased)
  {
	  if (event.key.code == sf::Keyboard::Down && _pressedDown)
		  _pressedDown = false;
	  if (event.key.code == sf::Keyboard::Up && _pressedUp)
		  _pressedUp = false;
	  return (false);
  }
  return (true);
}

void	MainMenuLayer::draw()
{
	_sprite.setTexture(_noSelect);
	_sprite.setColor(sf::Color::White);
	_sprite.setPosition(0, -10);
	_window.draw(_sprite);

	_sprite.setTexture(_select);
	_sprite.setColor(sf::Color::White);
	if (_whatButton == 0)
		_sprite.setPosition(0, 75);
	if (_whatButton == 1)
		_sprite.setPosition(0, 117);
	if (_whatButton == 2)
		_sprite.setPosition(0, 160);
	if (_whatButton == 3)
		_sprite.setPosition(0, 205);
	_window.draw(_sprite);

}

void	MainMenuLayer::run()
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
				{
					if (_whatButton == 0)
						_state = PLAY;
					if (_whatButton == 1)
						_state = LEADER;
					if (_whatButton == 2)
						_state = WHO;
					if (_whatButton == 3)
						_state = QUIT;
				}
			}
			if (_state == PLAY)
				return;
			if (_state == LEADER)
			{
				sf::IpAddress ip("localhost");
				unsigned short port = 4242;
				Scoring s(ip, port, _window);
				s.run();
				_state = MENU;
			}
			if (_state == WHO)
			{
				Credits  c(_window);
				c.run();
				_state = MENU;
			}
			if (_state == QUIT)
				_window.close();
			this->update(event);
			_window.clear(sf::Color::White);
			this->draw();
			_window.display();
		}
}
