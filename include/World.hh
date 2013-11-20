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
#include "QuadTree.hh"
#include "Light.hh"
#include "Controller.hh"
#include "GameObject.hh"
#include "Hero.hh"

class World
{
public:
  World(sftile::SfSmartCamera &camera, Light &heroLight);
  ~World();

  void			setMap(const std::string &mapName);
  void			handleEvents(sf::Event evt);
  void			update(float elapsedTime, size_t frameCount);
  void			render(sf::RenderTexture &rect);

  static Hero										*hero;
  static std::map<std::string, sftile::SfTilemap*>	tilemaps;
  static GameObjectVector							*gameObjects;

private:
  void loadTilemap(const std::string &mapName, const std::string &path);
  void clearWorld();
  void unloadTileMaps();
  bool mapExists(const std::string &mapName);
  void collideObject(GameObject *obj);

  void getWalls(sftile::priv::SfObjectLayer &walls);
  void getEnnemies(sftile::priv::SfObjectLayer &ennemies);
  void getObjects(sftile::priv::SfObjectLayer &objects);
  void getPlayerSpawn(sftile::priv::SfObjectLayer &playerSpawn);
  void getExit(sftile::priv::SfObjectLayer &playerSpawn);

  sftile::priv::SfTilemapLoader			_loader;
  sftile::SfTilemap				*_tilemap;
  std::string					_currentId;
  QuadTree					_quadTree;
  GameObjectVector				_gameObjects;
  sftile::SfSmartCamera				&_camera;
  Light						&_heroLight;
  GameObject					*_fox;
  Controller					*_control;
};

#endif // __WORLD_HH__
