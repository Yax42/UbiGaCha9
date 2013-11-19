#include "Game.hh"
#include "UbiException.hh"
#include "Hero.hh"
#include "FoxSpirit.hh"
#include "Utils.hh"
#include <iostream>

Game::Game(sf::RenderWindow &window)
  : _window(window),
    _worldView(window.getView()),
    _frontView(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getView().getSize().x, window.getView().getSize().y)),
    _foxLight(sf::Vector2f(_window.getView().getCenter().x, _window.getView().getCenter().y), 1),
    _playerLight(sf::Vector2f(_window.getView().getCenter().x, _window.getView().getCenter().y), 1),
    _camera(window.getView().getSize().x, window.getView().getSize().y),
    _lightDia(true),
    _elapsedTime(0.f),
    _world(_camera, _playerLight),
    _time(0.f)
{
  if (!_tHalo.loadFromFile("./ressource/textures/halo.png"))
    throw UbiException("Error load halo");

  _halo.setTexture(_tHalo);
  _sceneTexture.create(_window.getView().getSize().x, _window.getView().getSize().y);
  _lightTexture.create(_window.getView().getSize().x, _window.getView().getSize().y);
  _frontView.setCenter(sf::Vector2f(_window.getView().getCenter().x, _window.getView().getCenter().y));
  _camera.SetTrackMode(sftile::SF_TRACK_KEYS_PRESS);
}

Game::~Game()
{}

void	Game::update()
{
  _foxLight.update();
  _world.update(_elapsedTime);
}

bool	Game::progressiveLight(float ratio)
{
  static int	frameLight = 0;
  static bool	toLight = true;
  static float	modRatio = 0.f;

  frameLight += 1;
  if (toLight && frameLight >= 3)
    {
      _halo.setScale(sf::Vector2f(_foxLight.ratio + modRatio, _foxLight.ratio + modRatio));
      frameLight = 0;
      modRatio += (_tHalo.getSize().x * (_foxLight.ratio + modRatio) / _tHalo.getSize().y * (_foxLight.ratio + modRatio)) * 0.01;
      if (_foxLight.ratio + modRatio >= ratio)
	toLight = false;
    }
  else if (frameLight >= 3)
    {
      _halo.setScale(sf::Vector2f(_foxLight.ratio + modRatio, _foxLight.ratio + modRatio));
      frameLight = 0;
      modRatio -= (_tHalo.getSize().x * (_foxLight.ratio + modRatio) / _tHalo.getSize().y * (_foxLight.ratio + modRatio)) * 0.01;
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
  static bool	lastProgressif = true;

  _lightTexture.clear(sf::Color(0,0,0));
  _lightTexture.setView(_frontView);
  _lightTexture.draw(_halo);


  // Lumiere fox
  _halo.setPosition(_foxLight.position);
  centerOrigin(_halo);
  _halo.setColor(_foxLight.color);
  if (lastProgressif && (_foxLight.getNextRatio() !== _foxLight.ratio))
    {
      lastProgressif = false;
      _foxLight.setRatio(_foxLight.ratio + 0.1);
    }
  else if (_foxLight.getNextRatio() == _foxLight.ratio)
    {
      lastProgressif = true;
      _foxLight.setRatio(_foxLight.ratio - 0.1);
    }
  _lightTexture.draw(_halo);

  // Lumiere perso
  _halo.setPosition(_playerLight.position);
  centerOrigin(_halo);
  _halo.setColor(_playerLight.color);
  _halo.setScale(sf::Vector2f(_playerLight.ratio, _playerLight.ratio));
  _lightTexture.draw(_halo);

  _lightTexture.display();
}

void Game::modifLightPlayer(sf::Vector2f position, float radiusRatio)
{
  _foxLight.position = position;
  _foxLight.ratio = radiusRatio;
}

void	Game::handleEvent(sf::Event & event)
{
  _world.handleEvents(event);
}

void Game::draw()
{
  _window.clear();
  _sceneTexture.clear();
  _sceneTexture.setView(_worldView);
  _world.render(_sceneTexture);
  //drawLights();

  // sf::Sprite prerendering(_lightTexture.getTexture());
  // _sceneTexture.setView(_frontView);
  // _sceneTexture.draw(prerendering, sf::BlendMultiply);
  // _sceneTexture.display();

  sf::Sprite scene(_sceneTexture.getTexture());

  _window.draw(scene);
  //_window.setView(_window.getView());
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
