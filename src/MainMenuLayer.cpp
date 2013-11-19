#include "UbiException.hh"
#include "MainMenuLayer.hh"

MainMenuLayer::MainMenuLayer(sf::RenderWindow * window): _window(window)
{
#ifdef _WIN32
  std::string	path = "\\ressource\\font\\arial.ttf";
#else
  std::string	path = "./ressource/font/arial.ttf";
#endif

  if (!_font.loadFromFile(path))
    throw UbiException("Error load Font");
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
      if (event.key.code == sf::Keyboard::Return)
	return (false);
    }
  return (true);
}

void	MainMenuLayer::draw()
{
  //_window->draw(_sprite);

  sf::Text text;

  text.setFont(_font);
  text.setString("Press Start");
  text.setCharacterSize(12);
  text.setColor(sf::Color::Red);
  text.setPosition((_window->getSize().x / 2) - (12 * 3), (_window->getSize().y / 2) - 6);

  _window->draw(text);
}
