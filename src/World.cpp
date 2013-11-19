#include "SfTileEngine/sf_tilemap.h"
#include "SfTileEngine/sf_tileset.h"
#include "SfTileEngine/sf_tilemap_loader.h"
#include "World.hh"

World::World()
  : loader()
  , tilemaps()
  , current_id("null")
{
	cout << "World created" << endl;
}

World::World(const World& copy)
  : loader(copy.loader)
  , tilemaps(copy.tilemaps)
  , current_id(copy.current_id)
{}

World& World::operator=(const World& copy)
{
  if (this != &copy)
  {
    World temp(copy);

    std::swap(loader, temp.loader);
    std::swap(tilemaps, temp.tilemaps);
    std::swap(current_id, temp.current_id);
  }

  return *this;
}

sftile::SfTilemap *World::loadTilemap(std::string id, std::string path)
{
  sftile::SfTilemap tilemap;

  if (!mapExists(id) && !loader.LoadTilemap(path, tilemap))
  {
    cout << "Failed to load SfTilemap from path: " << path << endl;
    return nullptr;
  }

  tilemaps.emplace(id, tilemap);

  cout << "Loaded SfTilemap from path: " << path << endl;

  current_id = id;
  return getTilemap(id);
}

sftile::SfTilemap *World::getTilemap(std::string id)
{
  if (tilemaps.find(id) == tilemaps.end())
  {
    cout << "Failed to find SfTilemap with ID: " << id << endl;
    return nullptr;
  }
  else
    return &tilemaps.at(id);
}

void World::handleEvents(sf::Event evt)
{
  getTilemap(current_id)->HandleEvents(evt);
}

void World::update()
{
  getTilemap(current_id)->Update();
}

void World::render(sf::RenderWindow &window)
{
  getTilemap(current_id)->Render(window);
}

bool World::mapExists(std::string id)
{
  if (tilemaps.find(id) == tilemaps.end())
    return false;
  else
    return true;
}
