#include "Game.hh"
#include "UbiException.hh"
#include <iostream>

Game::Game(sf::RenderWindow &window)
  : _window(window),
    _worldView(window.getDefaultView()),
    _frontView(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize().x, window.getSize().y))
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
  addLight(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), 1);
}

Game::~Game()
{}

void	Game::update()
{
  // à la pose du moine
}

void Game::drawLights()
{
  _lightTexture.clear(sf::Color(0,0,0));
  _lightTexture.setView(_frontView);
  _lightTexture.draw(_halo);

  for (std::list<Light>::iterator it = _lights.begin(); it != _lights.end(); ++it)
    {
      _halo.setPosition((*it).position);
      _halo.setColor((*it).color);
      _halo.setScale(sf::Vector2f((*it).ratio, (*it).ratio));
      _lightTexture.draw(_halo);
    }
  
  _lightTexture.display();
}

void Game::addLight(sf::Vector2f position, float radiusRatio)
{
  _lights.push_back(Light(position, radiusRatio));
}

void Game::draw()
{
  _window.clear(sf::Color::Blue);
  
  _sceneTexture.clear(sf::Color::Red);
  _sceneTexture.setView(_worldView);
  // _sceneTexture.draw(_tileMap);
  // for(int i = 0; i < Foreground; ++i)
  //   {
  //     mSceneTexture.draw(*mSceneLayers[i]);
  //   }
  // mQuadTree.draw(mSceneTexture);
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
