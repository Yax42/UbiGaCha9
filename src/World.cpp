#include "SfTileEngine/sf_tilemap.h"
#include "SfTileEngine/sf_tileset.h"
#include "SfTileEngine/sf_tilemap_loader.h"
#include "World.hh"
#include "Hero.hh"
#include "FoxSpirit.hh"

World::World(sftile::SfSmartCamera &camera, Light &heroLight)
  : _camera(camera),
    _heroLight(heroLight)
{
  _hero = new Hero(sf::Vector2f(40, 40));
  _fox = new FoxSpirit(sf::Vector2f(140, 140));
  _control = new Controller(*_hero, *_fox);
  loadTilemap("tuto", "./ressource/maps/tuto.tmx");
  setMap("tuto");
  _gameObjects.push_back(_hero);
  _gameObjects.push_back(_fox);
  std::cout << "World created" << std::endl;
}

World::~World()
{
  clearWorld();
  unloadTileMaps();
}

void World::setMap(const std::string &mapName)
{
  if (!mapExists(mapName))
    {
      std::cerr << "Error on setMap: " << mapName << " Doesn't exist" << std::endl;
      return ;
    }
  clearWorld();
  _tilemap = _tilemaps.find(mapName)->second;
  for (std::vector<sftile::priv::SfObjectLayer>::const_iterator it = _tilemap->getObjectLayers().begin();
       it != _tilemap->getObjectLayers().end(); ++it)
    {
      std::string name = (*it).GetName();

      if (name == "walls")
	getWalls(*it);
      else if (name == "ennemies")
	getEnnemies(*it);
      else if (name == "objects")
	getObjects(*it);
      else if (name == "playerspawn")
	getPlayerSpawn(*it);
      else if (name == "exit")
	getExit(*it);
    }
}

void World::handleEvents(sf::Event evt)
{
  _control->handleEvent(evt);
  _tilemap->HandleEvents(evt);
}

void World::update(float elapsedTime, size_t frameCount)
{
  _tilemap->Update();
  for (GameObjectVector::iterator it = _gameObjects.begin();
       it != _gameObjects.end(); ++it)
    {
      (*it)->update(elapsedTime, frameCount);
      _quadTree.insert(*it);
    }
  for (GameObjectVector::iterator it = _gameObjects.begin();
       it != _gameObjects.end(); ++it)
    {
      GameObjectVector	returnObjects;

      if (_quadTree.retrieve(returnObjects, *it))
	{
	  for (GameObjectVector::iterator it2 = returnObjects.begin();
	       it2 != returnObjects.end(); ++it2)
	    if ((*it)->collides(**it2))
	      (*it)->toBackPosition();
	}
    }
  _quadTree.clear();
  _heroLight.position = _hero->getPos();
  sf::Vector2f foxPos = _fox->getPos();
  _camera.SetCenterPosition(foxPos.x, foxPos.y);
}

void World::render(sf::RenderTexture &window)
{
  _tilemap->Render(window);
  sf::View view = window.getView();
  view.setCenter(_camera.GetCenterPosition());
  window.setView(view);
  for (GameObjectVector::iterator it = _gameObjects.begin();
       it != _gameObjects.end(); ++it)
    (*it)->draw(window);
}

void World::loadTilemap(const std::string &mapName, const std::string &path)
{
  if (mapExists(mapName))
    {
      std::cerr << "Error: map already exist: " << mapName << std::endl;
      return ;
    }
  sftile::SfTilemap *tilemap = new sftile::SfTilemap;
  if (_loader.LoadTilemap(path, *tilemap))
    {
      tilemap->RegisterCamera(&_camera);
      _tilemaps.emplace(mapName, tilemap);
      std::cout << "Loaded SfTilemap from path: " << path << std::endl;
    }
  else
    {
      std::cerr << "Failed to load SfTilemap from path: " << path << std::endl;
      delete tilemap;
    }
}

void World::clearWorld()
{
  for (GameObjectVector::iterator it = _gameObjects.begin();
       it != _gameObjects.end(); ++it)
    delete *it;
  _gameObjects.clear();
}

void World::unloadTileMaps()
{
  for (std::map<std::string, sftile::SfTilemap*>::iterator it = _tilemaps.begin();
       it != _tilemaps.end(); ++it)
    delete it->second;
  _tilemaps.clear();
}

bool World::mapExists(const std::string &mapName)
{
  return (_tilemaps.find(mapName) != _tilemaps.end());
}

void World::getWalls(const sftile::priv::SfObjectLayer &walls)
{
  std::cout << "getWalls" << std::endl;
}

void World::getEnnemies(const sftile::priv::SfObjectLayer &ennemies)
{
  std::cout << "getEnnemies" << std::endl;
}

void World::getObjects(const sftile::priv::SfObjectLayer &objects)
{
  std::cout << "getObjects" << std::endl;
}

void World::getPlayerSpawn(const sftile::priv::SfObjectLayer &playerSpawn)
{
  std::cout << "getPlayerSpawn" << std::endl;
}

void World::getExit(const sftile::priv::SfObjectLayer &exit)
{
  std::cout << "getExit" << std::endl;
}
