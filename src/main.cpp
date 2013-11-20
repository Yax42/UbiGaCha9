#include <SFML/Window.hpp>
#include "sf_tile_engine.h"
#include "Controller.hh"
#include "World.hh"
#include "Game.hh"
#include "FoxSpirit.hh"
#include "Hero.hh"
#include "Mob0.hh"
#include "Mob1.hh"
#include "Mob2.hh"
#include "Mob3.hh"

int main()
{
  sf::RenderWindow	window(sf::VideoMode(800, 600), "Ubisoft");

  FoxSpirit::initAsset();
  Hero::initAsset();
  Mob0::initAsset();
  Mob1::initAsset();
  Mob2::initAsset();
  Mob3::initAsset();
  window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(256, 240))));
  window.setFramerateLimit(30);
  Game game(window);
  game.run();
}
