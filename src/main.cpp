#include <SFML/Window.hpp>
#include "sf_tile_engine.h"
#include "Controller.hh"
#include "World.hh"
#include "Game.hh"

int main()
{
  sf::RenderWindow	window(sf::VideoMode(800, 600), "My window");
  /*
  sftile::SfSmartCamera	camera(800, 600);
  World			world;
  sftile::SfTilemap	*tilemap = world.loadTilemap("TileMap", "ressource/map/TileMap.tmx");

  if (!tilemap)
    {
      cout << "Failed to load tilemap" << endl;
      return -1;
    }
  camera.SetTrackMode(sftile::SF_TRACK_KEYS_PRESS);
  tilemap->RegisterCamera(&camera);
  */
  Game game(window);

  window.setJoystickThreshold(15);
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	  //world.handleEvents(event);
	  game.handleEvent(event);
	}
      game.update();
      //world.update();
      window.clear();
      //world.render(window);
      game.draw();
      window.display();
    }
  return (0);
}
