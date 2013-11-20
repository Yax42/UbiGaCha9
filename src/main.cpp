#include <SFML/Window.hpp>
#include "sf_tile_engine.h"
#include "Controller.hh"
#include "World.hh"
#include "Game.hh"
#include "FoxSpirit.hh"
#include "Hero.hh"
#include "MainMenuLayer.hh"

int main()
{
  sf::RenderWindow	window(sf::VideoMode(800, 600), "Ubisoft");

  FoxSpirit::initAsset();
  Hero::initAsset();
  window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(256, 240))));
  window.setFramerateLimit(30);
  window.setKeyRepeatEnabled(false);
  MainMenuLayer mainMenu(window);
  mainMenu.run();
  Game game(window);
  game.run();
}
