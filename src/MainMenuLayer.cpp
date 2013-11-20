#include "UbiException.hh"
#include "MainMenuLayer.hh"
#include "Game.hh"
#include "Scoring.hh"
#include "Credits.hh"
#include "SoundManager.hh"
#include "Game.hh"
#include <iostream>

MainMenuLayer::MainMenuLayer(sf::RenderWindow &window)
: _window(window), _whatButton(0), _state(MENU)
{
  std::string	path = "./ressource/font/arial.ttf";
  if (!_font.loadFromFile(path))
    throw UbiException("Error load Font");
  if (!_select.loadFromFile("./ressource/textures/cloche.png"))
	  throw UbiException("Error load bell");
  if (!_noSelect.loadFromFile("./ressource/textures/menu 4.0.png"))
	  throw UbiException("Error load Menu");
  if (!_music.openFromFile("./ressource/sounds/music lvl1 ou menu .wav"))
	  throw UbiException("Error load Music");
  _music.setLoop(true);
  _music.play();
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
	_sprite.setPosition(0, 0);
	_window.draw(_sprite);

	sf::Sprite tmp;
	tmp.setTexture(_select);
	if (_whatButton == 0)
		tmp.setPosition(50, 75);
	if (_whatButton == 1)
		tmp.setPosition(0, 125);
	if (_whatButton == 2)
		tmp.setPosition(15, 160);
	if (_whatButton == 3)
		tmp.setPosition(100, 205);
	_window.draw(tmp);

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
			{
				_music.stop();
				SoundManager::getInstance().getSound("ressource/sounds/Jingle_Positif_Harp_01.wav").play();
				Game	game(_window);
				game.run();
				_state = MENU;
			}
			if (_state == LEADER)
			{
				_music.pause();
				sf::IpAddress ip("127.0.0.1");
				unsigned short port = 4242;
				Scoring s(ip, port, _window);
				s.run();
				_music.play();
				_state = MENU;
			}
			if (_state == WHO)
			{
				_music.pause();
				Credits  c(_window);
				c.run();
				_music.play();
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
