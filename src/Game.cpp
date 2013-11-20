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
      _frameCount(0),
    _nbMusic(0),
    _openInventory(false)
{
  if (!_tHaloFox.loadFromFile("./ressource/textures/haloFox.png"))
    throw UbiException("Failed to load haloFox.png");
  if (!_tHaloMonk.loadFromFile("./ressource/textures/haloMonk.png"))
    throw UbiException("Failed to load haloMonk.png");
  _sceneTexture.create(_window.getView().getSize().x, _window.getView().getSize().y);
  _lightTexture.create(_window.getView().getSize().x, _window.getView().getSize().y);
  _playerLight.setTexture(_tHaloMonk);
  _foxLight.setTexture(_tHaloFox);

  _window.setKeyRepeatEnabled(false);
  if (!_texRain.loadFromFile("./ressource/textures/pluie.png"))
    throw UbiException("Error load Rain");

  if (!_musicFade.openFromFile("./ressource/sounds/Musique_In_Game_Fade_01.wav"))
    throw UbiException("Error load music Fade Game");
  if (!_music.openFromFile("./ressource/sounds/Musique_In_Game_01.wav"))
    throw UbiException("Error load music Game");
  if (!_ambianceFade.openFromFile("./ressource/sounds/Ambiance_Fade_01.wav"))
    throw UbiException("Error load ambiance Fade Game");
  if (!_ambiance.openFromFile("./ressource/sounds/Ambiance_01.wav"))
    throw UbiException("Error load ambiance Game");

  _musicFade.setVolume(100);
  _music.setVolume(100);
  _music.setLoop(true);

  _musicFade.play();
  _ambianceFade.play();
  _ambiance.setLoop(true);
}

Game::~Game()
{
  _window.setKeyRepeatEnabled(true);
}

void	Game::update()
{
  _foxLight.update();
  _world.update(_elapsedTime, _frameCount);
  if (_musicFade.getStatus() == sf::Music::Stopped && _music.getStatus() != sf::Music::Playing)
    _music.play();
  if (_ambianceFade.getStatus() == sf::Music::Stopped && _ambiance.getStatus() != sf::Music::Playing)
    _ambiance.play();
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
  //this->progressiveLight(1.1);
  if (lastProgressif && (_foxLight.getNextRatio() != _foxLight.ratio))
    {
      lastProgressif = false;
      _foxLight.setRatio(_foxLight.ratio + 0.2);
    }
  else if (_foxLight.getNextRatio() == _foxLight.ratio)
    {
      lastProgressif = true;
      _foxLight.setRatio(_foxLight.ratio - 0.2);
    }  _halo.setScale(sf::Vector2f(_foxLight.ratio, _foxLight.ratio));
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

  if (_openInventory)
    _inventory.handleEvent(event);
  if (event.type == sf::Event::JoystickButtonPressed)
    {
      if (event.joystickButton.button == 7)
	{
	  if (_openInventory)
	    _openInventory = false;
	  else
	    _openInventory = true;
	}
    }
  else if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Return)
	{
	  if (_openInventory)
	    _openInventory = false;
	  else
	    _openInventory = true;
	}
    }
}

void	Game::drawRain()
{
  static int	animRain = 0;
  sf::Sprite	tmp(_texRain);
  int		mult = _texRain.getSize().x / 11;

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
  //this->drawRain();
  _sceneTexture.display();
  drawLights();
  _sceneTexture.display();

  sf::Sprite prerendering(_lightTexture.getTexture());
  prerendering.setPosition(_camera.GetPosition());
  _sceneTexture.draw(prerendering, sf::BlendMultiply);
  if (_openInventory)
    _inventory.draw(_sceneTexture);
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
      sf::Joystick::update();
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
