#include "Game.hh"
#include "UbiException.hh"
#include <iostream>

Game::Game(sf::RenderWindow &window)
  : _window(window),
    _worldView(window.getDefaultView()),
    _frontView(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize().x, window.getSize().y)),
    _playerLight(sf::Vector2f(_window.getSize().x / 2.f, _window.getSize().y / 2.f), 1),
    _camera(window.getSize().x, window.getSize().y)
{
#ifdef _WIN32
  std::string path = "\\ressource\\textures\\halo.png";  
#else
  std::string path = "./ressource/textures/halo.png";
#endif
  if (!_tHalo.loadFromFile(path))
    throw UbiException("Error load halo");
  _halo.setTexture(_tHalo);
  _sceneTexture.create(_window.getSize().x, _window.getSize().y);
  _lightTexture.create(_window.getSize().x, _window.getSize().y);
  _frontView.setCenter(sf::Vector2f(_window.getSize().x / 2.f, _window.getSize().y / 2.f));
  _tilemap = _world.loadTilemap("TileMap", "ressource/map/TileMap.tmx");
  if (!_tilemap)
    {
      throw UbiException("Failed to load tilemap");
    }
  _camera.SetTrackMode(sftile::SF_TRACK_KEYS_PRESS);
  _tilemap->RegisterCamera(&_camera);
}

Game::~Game()
{}

void	Game::update()
{
  _world.update();
}

void Game::drawLights()
{
  _lightTexture.clear(sf::Color(0,0,0));
  _lightTexture.setView(_frontView);
  _lightTexture.draw(_halo);

  _halo.setPosition(_playerLight.position);
  _halo.setColor(_playerLight.color);
  _halo.setScale(sf::Vector2f(_playerLight.ratio, _playerLight.ratio));
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

void Game::draw()
{
  _window.clear(sf::Color::Blue);
  
  _sceneTexture.clear(sf::Color::Red);
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
