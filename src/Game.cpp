#include "Game.hh"
#include "UbiException.hh"
#include "Hero.hh"
#include "FoxSpirit.hh"
#include "Utils.hh"
#include <iostream>

Game::Game(sf::RenderWindow &window)
  : _window(window),
    _foxLight(_window.getView().getCenter(), 1),
    _playerLight(_window.getView().getCenter(), 1),
    _camera(window.getView().getSize().x, window.getView().getSize().y),
    _lightDia(true),
    _elapsedTime(0.f),
    _world(_camera, _playerLight),
    _time(0.f),
    _frameCount(0)
{
  if (!_tHaloFox.loadFromFile("./ressource/textures/haloFox.png"))
    throw UbiException("Failed to load haloFox.png");
  if (!_tHaloMonk.loadFromFile("./ressource/textures/haloMonk.png"))
    throw UbiException("Failed to load haloMonk.png");
  _sceneTexture.create(_window.getView().getSize().x, _window.getView().getSize().y);
  _lightTexture.create(_window.getView().getSize().x, _window.getView().getSize().y);
  _playerLight.setTexture(_tHaloMonk);
  _foxLight.setTexture(_tHaloFox);
  if (!_imageRain.loadFromFile("./ressource/textures/animation_pluie.jpg"))
    throw UbiException("Error load Rain");
  _imageRain.createMaskFromColor(sf::Color(0, 0, 0), 100);
  _texRain.loadFromImage(_imageRain);

  _window.setKeyRepeatEnabled(false);
}

Game::~Game()
{
  _window.setKeyRepeatEnabled(true);
}

void	Game::update()
{
  _foxLight.update();
  _world.update(_elapsedTime, _frameCount);
}

void Game::drawLights()
{
  static bool	lastProgressif = true;

  _lightTexture.clear();
  _lightTexture.setView(_window.getView());

  // Lumiere fox
  _halo.setTexture(_tHaloFox);
  _halo.setPosition(_foxLight.position);
  centerOrigin(_halo);
  _halo.setColor(_foxLight.color);
  if (lastProgressif && (_foxLight.getNextRatio() != _foxLight.ratio))
    {
      lastProgressif = false;
      _foxLight.setRatio(_foxLight.ratio + 0.2);
    }
  else if (_foxLight.getNextRatio() == _foxLight.ratio)
    {
      lastProgressif = true;
      _foxLight.setRatio(_foxLight.ratio - 0.2);
    }
  _halo.setScale(sf::Vector2f(_foxLight.ratio, _foxLight.ratio));
  _lightTexture.draw(_halo);

  sf::View view = _window.getView();
  view.setCenter(_camera.GetCenterPosition());
  _lightTexture.setView(view);
  // Lumiere perso
  _halo.setTexture(_tHaloMonk);
  _halo.setPosition(_playerLight.position);
  centerOrigin(_halo);
  _halo.setColor(_playerLight.color);
  _halo.setScale(_playerLight.ratio, _playerLight.ratio);
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

void	Game::drawRain()
{
  static int	animRain = 0;
   sf::Sprite	tmp(_texRain);
   int		mult = _texRain.getSize().x / 7;

   if ((_frameCount % 8) == 0)
     {
       if (animRain >= _texRain.getSize().x - mult)
	 animRain = 0;
       else
	 animRain += mult;
     }
   tmp.setTextureRect(sf::IntRect(animRain, 0, mult, _texRain.getSize().y));
   _sceneTexture.draw(tmp);
   _sceneTexture.display();
}

void Game::draw()
{
  _window.clear();
  _sceneTexture.clear();
  _sceneTexture.setView(_window.getView());
  _world.render(_sceneTexture);
  _sceneTexture.display();
  drawLights();
  _sceneTexture.display();

  sf::Sprite prerendering(_lightTexture.getTexture());
  prerendering.setPosition(_camera.GetPosition());
  _sceneTexture.draw(prerendering, sf::BlendMultiply);
  // drawRain();
  _sceneTexture.display();

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
      ++_frameCount;
    }
}
