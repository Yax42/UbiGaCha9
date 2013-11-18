#include <SFML/Window.hpp>
#include "include/sf_tile_engine.h"
#include "Controller.hh"

int main()
{
  sf::RenderWindow	window(sf::VideoMode(256, 240), "My window");
  sftile::SfWorld	world;
  sftile::SfSmartCamera	camera(256, 240);

  // Load a tilemap and save it in the world.
  // This also saves a pointer to that tilemap.
  sftile::SfTilemap* tilemap = world.LoadTilemap("testmap", "ressource/map/example.tmx");

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
	  // Handle any events passed into the engine.
	  world.HandleEvents(event);
	  control.handleEvent(event);
	}
      // Update the engine.
      world.Update();
      window.clear();
      // Render the engine.
      world.Render(window);
      window.display();
    }
  return (0);
}
