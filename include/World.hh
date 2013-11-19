#ifndef DIS_IS_THE_WORLD_BITCH
#define DIS_IS_THE_WORLD_BITCH

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "sf_tilemap_loader.h"
#include "sf_dll_macro.h"

class World
{
public:
  explicit SfWorld();


  SfWorld(const SfWorld& _copy);
  SfWorld& operator=(const SfWorld& _copy);

  SfTilemap* LoadTilemap(string _id, string _path);
  SfTilemap* GetTilemap(string _id);
  void HandleEvents(sf::Event _evt);
  void Update();
  void Render(sf::RenderWindow& _window);


private:
  bool LoadFromTMX(std::string _path);
  bool MapExists(std::string _id);
  priv::SfTilemapLoader loader;
  map<std::string, SfTilemap> tilemaps;
  string current_id;
};

#endif // SF_WORLD_H
