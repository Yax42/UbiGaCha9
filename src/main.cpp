#include <SFML/Window.hpp>
#include "sf_tile_engine.h"
#include "Controller.hh"
#include "World.hh"
#include "Game.hh"
#include "FoxSpirit.hh"
#include "Hero.hh"
#include "MainMenuLayer.hh"
#include "Mob0.hh"
#include "Mob1.hh"
#include "Mob2.hh"
#include "Mob3.hh"
#include "Arrow.hh"
#include "Kamea.hh"
#include "SoundManager.hh"
#include "ItemObject.hh"

int main()
{
  sf::RenderWindow	window(sf::VideoMode(1024, 768), "Ubisoft");

  FoxSpirit::initAsset();
  Hero::initAsset();
  Mob0::initAsset();
  Mob1::initAsset();
  Mob2::initAsset();
  Mob3::initAsset();
  Arrow::initAsset();
  Kamea::initAsset();
  ItemObject::initAsset();
  window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(256, 240))));
  window.setFramerateLimit(30);
  window.setKeyRepeatEnabled(false);
  MainMenuLayer mainMenu(window);
  mainMenu.run();
}
