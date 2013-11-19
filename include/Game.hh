#ifndef	_GAME_HH_
#define	_GAME_HH_

#include <list>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "World.hh"
#include "Light.hh"
#include "sf_tile_engine.h"

class	Game
{
public:
  Game(sf::RenderWindow &);
  ~Game();
  void	update();
  void	drawLights();
  void	modifLightPlayer(sf::Vector2f, float);
  void	draw();
  void	handleEvent(sf::Event &);
private:
  sf::RenderWindow	&_window;
  sf::RenderTexture	_sceneTexture;
  sf::RenderTexture	_lightTexture;
  sf::Texture		_tHalo;
  sf::Sprite		_halo;
  Light			_playerLight;
  sf::View		_worldView;
  sf::View              _frontView;
  sftile::SfSmartCamera	_camera;
  World			_world;
  sftile::SfTilemap	*_tilemap;
};

#endif // _GAME_HH_
