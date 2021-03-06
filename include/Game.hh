#ifndef	_GAME_HH_
#define	_GAME_HH_

#include <list>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "World.hh"
#include "Light.hh"
#include "sf_tile_engine.h"
#include "GameObject.hh"
#include "PlayerInventory.hh"

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
  void	run();
  float	getElapsedTime() const {return _elapsedTime;}
  bool	progressiveLight(float);
  void	drawRain();

  static bool _run;

private:
  sf::RenderWindow	&_window;
  sf::RenderTexture	_sceneTexture;
  sf::RenderTexture	_lightTexture;
  sf::Texture		_tHaloFox;
  sf::Texture		_tHaloMonk;
  sf::Sprite		_halo;
  Light			_playerLight;
  Light			_foxLight;
  sf::View		_worldView;
  sf::View              _frontView;
  sftile::SfSmartCamera	_camera;
  World			_world;
  bool			_lightDia;
  float			_elapsedTime;
  float			_time;
  size_t		_frameCount;
  sf::Image		_imageRain;
  sf::Texture		_texRain;
  sf::Music		_musicFade;
  sf::Music		_music;
  sf::Music		_ambianceFade;
  sf::Music		_ambiance;
  int			_nbMusic;
  PlayerInventory	_inventory;
  bool			_openInventory;
};

#endif // _GAME_HH_
