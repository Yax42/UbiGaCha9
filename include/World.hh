#ifndef __WORLD_HH__
#define __WORLD_HH__

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SfTileEngine/sf_tilemap_loader.h"
#include "SfTileEngine/sf_tilemap.h"
#include "sf_tile_engine.h"

class World
{
public:
  explicit World();


  World(const World &_copy);
  World& operator=(const World &_copy);

  sftile::SfTilemap	*loadTilemap(std::string id, std::string path);
  sftile::SfTilemap	*getTilemap(std::string id);
  void			handleEvents(sf::Event evt);
  void			update();
  void			render(sf::RenderTexture &rect);

private:
  bool loadFromTMX(std::string path);
  bool mapExists(std::string id);
  void getWalls(const sftile::priv::SfObjectLayer &walls);
  void getEnnemies(const sftile::priv::SfObjectLayer &ennemies);
  void getObjects(const sftile::priv::SfObjectLayer &objects);
  void getPlayerSpawn(const sftile::priv::SfObjectLayer &playerSpawn);
  void getExit(const sftile::priv::SfObjectLayer &exit);

  sftile::priv::SfTilemapLoader			loader;
  std::map<std::string, sftile::SfTilemap>	tilemaps;
  std::string					current_id;
};

#endif // __WORLD_HH__
