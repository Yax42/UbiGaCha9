#ifndef	_GAME_HH_
#define	_GAME_HH_

#include <list>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Light.hh"

class	Game
{
public:
  Game(sf::RenderWindow &);
  ~Game();
  void	update();
  void	drawLights();
  void	addLight(sf::Vector2f, float);
  void	draw();
private:
  sf::RenderWindow	&_window;
  sf::RenderTexture	_sceneTexture;
  sf::RenderTexture	_lightTexture;
  sf::Texture		_tHalo;
  sf::Sprite		_halo;
  std::list<Light>      _lights;
  sf::View		_worldView;
  sf::View              _frontView;
};

#endif // _GAME_HH_
