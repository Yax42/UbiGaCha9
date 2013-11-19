#include <SFML/Window.hpp>
#include "sf_tile_engine.h"
#include "Controller.hh"
#include "World.hh"

int main()
{
  sf::RenderWindow	window(sf::VideoMode(800, 600), "My window");
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
  window.setJoystickThreshold(15);
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	  world.handleEvents(event);
	}
      world.update();
      window.clear();
      world.render(window);
      window.display();
    }
  return (0);
}
