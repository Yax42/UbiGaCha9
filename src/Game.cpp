#include "Game.hh"
#include "UbiException.hh"
#include <iostream>

Game::Game(sf::RenderWindow &window)
  : _window(window),
    _worldView(window.getDefaultView()),
    _frontView(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize().x, window.getSize().y)),
    _playerLight(sf::Vector2f(_window.getSize().x / 2.f, _window.getSize().y / 2.f), 1),
    _camera(window.getSize().x, window.getSize().y),
    _lightDia(true),
    _elapsedTime(0.f),
    _time(0.f)
{
  std::string path = "./ressource/textures/halo.png";
  if (!_tHalo.loadFromFile(path))
    throw UbiException("Error load halo");
  _halo.setTexture(_tHalo);
  _sceneTexture.create(_window.getSize().x, _window.getSize().y);
  _lightTexture.create(_window.getSize().x, _window.getSize().y);
  _frontView.setCenter(sf::Vector2f(_window.getSize().x / 2.f, _window.getSize().y / 2.f));
  _tilemap = _world.loadTilemap("TileMap", "ressource/maps/tuto.tmx");
  if (!_tilemap)
      throw UbiException("Failed to load tilemap");
  _camera.SetTrackMode(sftile::SF_TRACK_KEYS_PRESS);
  _tilemap->RegisterCamera(&_camera);
}

Game::~Game()
{}

void	Game::update()
{
  _world.update();
}

bool	Game::progressiveLight(float ratio)
{
  static int	frameLight = 0;
  static bool	toLight = true;
  static float	modRatio = 0.f;

  frameLight += 1;
  if (toLight && frameLight >= 3)
    {
      _halo.setScale(sf::Vector2f(_playerLight.ratio + modRatio, _playerLight.ratio + modRatio));
      frameLight = 0;
      modRatio += (_tHalo.getSize().x * (_playerLight.ratio + modRatio) / _tHalo.getSize().y * (_playerLight.ratio + modRatio)) * 0.01;
      if (_playerLight.ratio + modRatio >= ratio)
	toLight = false;
    }
  else if (frameLight >= 3)
    {
      _halo.setScale(sf::Vector2f(_playerLight.ratio + modRatio, _playerLight.ratio + modRatio));
      frameLight = 0;
      modRatio -= (_tHalo.getSize().x * (_playerLight.ratio + modRatio) / _tHalo.getSize().y * (_playerLight.ratio + modRatio)) * 0.01;
      if (modRatio <= 0)
	{
	  toLight = true;
	  return (false);
	}
    }
  return (true);
}

void Game::drawLights()
{
  static bool	lastProgressif = false;

  _lightTexture.clear(sf::Color(0,0,0));
  _lightTexture.setView(_frontView);
  _lightTexture.draw(_halo);

  _halo.setPosition(_playerLight.position);
  centerOrigin(_halo);
  _halo.setColor(_playerLight.color);
  this->progressiveLight(1.1);
  _lightTexture.draw(_halo);

  _lightTexture.display();
}

void Game::modifLightPlayer(sf::Vector2f position, float radiusRatio)
{
  _playerLight.position = position;
  _playerLight.ratio = radiusRatio;
}

void	Game::handleEvent(sf::Event & event)
{
  _world.handleEvents(event);
}

void	Game::centerOrigin(sf::Sprite & sprite)
{
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Game::draw()
{
  _window.clear(sf::Color::Blue);
  _sceneTexture.clear(sf::Color::Black);
  _sceneTexture.setView(_worldView);
  _world.render(_sceneTexture);
  drawLights();

  sf::Sprite prerendering(_lightTexture.getTexture());
  _sceneTexture.setView(_frontView);
  _sceneTexture.draw(prerendering, sf::BlendMultiply);
  _sceneTexture.display();

  sf::Sprite scene(_sceneTexture.getTexture());

  //_window.setView(mFrontView);
  //_window.draw(mTileMap);
  _window.draw(scene);
  _window.setView(_window.getDefaultView());
  //_window.draw(*mSceneLayers[Foreground]);
}

void	Game::run()
{
  sf::Clock	clock;

  while (_window.isOpen())
    {
      clock.restart();
      sf::Event event;
      while (_window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    _window.close();
	  this->handleEvent(event);
	}
      this->update();
      _window.clear();
      this->draw();
      _window.display();
      _elapsedTime = clock.getElapsedTime().asSeconds();
      _time += _elapsedTime;
    }
}
