#include <memory>
#include "SfTileEngine/sf_tilemap.h"
#include "SfTileEngine/sf_tileset.h"
#include "SfTileEngine/sf_tilemap_loader.h"
#include "World.hh"
#include "Hero.hh"
#include "FoxSpirit.hh"
#include "Mob0.hh"
#include "Mob1.hh"
#include "Mob2.hh"
#include "Mob3.hh"
#include "Wall.hh"
#include "Exit.hh"

Hero *World::hero = nullptr;
std::map<std::string, sftile::SfTilemap*> World::tilemaps;
GameObjectVector							*World::gameObjects = nullptr;
World *World::world = nullptr;

World::World(sftile::SfSmartCamera &camera, Light &heroLight)
  : _camera(camera),
    _heroLight(heroLight),
    _fox(nullptr),
    _control(nullptr)
{
  world = this;
  hero = new Hero;
  gameObjects = &_gameObjects;
  _fox = new FoxSpirit;
  _control = new Controller(*hero, *_fox);
  loadTilemap("tuto", "./ressource/maps/tuto.tmx");
  setMap("tuto");
  std::cout << "World created" << std::endl;
}

World::~World()
{
  clearWorld();
  unloadTileMaps();
  delete _control;
  delete _fox;
  delete hero;
}

bool World::setMap(const std::string &mapName)
{
  if (!mapExists(mapName))
    {
      std::cerr << "Error on setMap: " << mapName << " Doesn't exist" << std::endl;
      return (false);
    }
  clearWorld();
  _tilemap = tilemaps.find(mapName)->second;
  for (std::vector<sftile::priv::SfObjectLayer>::iterator it = _tilemap->getObjectLayers().begin();
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
  return (true);
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
  hero->update(elapsedTime, frameCount);
  _quadTree.insert(hero);
  _fox->update(elapsedTime, frameCount);
  _quadTree.insert(_fox);
  for (GameObjectVector::iterator it = _gameObjects.begin();
       it != _gameObjects.end(); ++it)
    collideObject(*it);
  collideObject(hero);
  collideObject(_fox);
  _quadTree.clear();
  _heroLight.position = hero->getPos() + sf::Vector2f(32, 32);
  sf::Vector2f foxPos = _fox->getCenterPos();
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
  hero->draw(window);
  _fox->draw(window);
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
      tilemaps.emplace(mapName, tilemap);
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
  for (std::map<std::string, sftile::SfTilemap*>::iterator it = tilemaps.begin();
       it != tilemaps.end(); ++it)
    delete it->second;
  tilemaps.clear();
}

bool World::mapExists(const std::string &mapName)
{
  return (tilemaps.find(mapName) != tilemaps.end());
}

void World::collideObject(GameObject *obj)
{
  GameObjectVector	returnObjects;

  if (_quadTree.retrieve(returnObjects, obj))
    {
      for (GameObjectVector::iterator it = returnObjects.begin();
	   it != returnObjects.end(); ++it)
	if (obj->collides(**it))
	  obj->toBackPosition();
    }
}

void World::getWalls(sftile::priv::SfObjectLayer &walls)
{
  std::cout << "getWalls" << std::endl;

  for (size_t i = 0; i < walls.getSizeObjects(); ++i)
    {
      sftile::SfObject	*wall = walls.GetObject(i);
      sf::Vector2i	tmpVec = wall->GetPosition();
      sf::Vector2f	wallPos(tmpVec.x, tmpVec.y);
      tmpVec = wall->GetDimensions();
      sf::Vector2f	wallDim(tmpVec.x, tmpVec.y);

      _gameObjects.push_back(new Wall(wallPos, wallDim));
    }
}

void World::getEnnemies(sftile::priv::SfObjectLayer &ennemies)
{
  std::cout << "getEnnemies" << std::endl;

  for (size_t i = 0; i < ennemies.getSizeObjects(); ++i)
    {
      sftile::SfObject	*ennemy = ennemies.GetObject(i);
      sf::Vector2i	tmpPos = ennemy->GetPosition();
      sf::Vector2f	ennemyPos(tmpPos.x, tmpPos.y);

      switch (ennemy->GetId())
	{
	case 0:
	  _gameObjects.push_back(new Mob0(ennemyPos));
	  break;
	case 1:
	  _gameObjects.push_back(new Mob1(ennemyPos));
	  break;
	case 2:
	  _gameObjects.push_back(new Mob2(ennemyPos));
	  break;
	default:
	  _gameObjects.push_back(new Mob3(ennemyPos));
	}
    }
}

void World::getObjects(sftile::priv::SfObjectLayer &objects)
{
  std::cout << "getObjects" << std::endl;

  for (size_t i = 0; i < objects.getSizeObjects(); ++i)
    {
      sftile::SfObject	*object = objects.GetObject(i);

      // _gameObjects.push_back(new ???(object->GetPosition(), object->GetDimensions()));
    }
}

void World::getPlayerSpawn(sftile::priv::SfObjectLayer &playerSpawn)
{
  std::cout << "getPlayerSpawn" << std::endl;

  if (playerSpawn.getSizeObjects() > 0)
    {
      sftile::SfObject	*spawn = playerSpawn.GetObject(0);
      sf::Vector2i	tmp = spawn->GetPosition();
      sf::Vector2f	spawnPos(tmp.x, tmp.y);

      _fox->setPos(spawnPos);
      hero->setPos(spawnPos);
    }
  else
    std::cerr << "No Player Spawn for this map" << std::endl;
}

void World::getExit(sftile::priv::SfObjectLayer &exits)
{
  std::cout << "getExit" << std::endl;

  if (exits.getSizeObjects() > 0)
    {
      sftile::SfObject *exit = exits.GetObject(0);
      sf::Vector2i	tmpVec = exit->GetPosition();
      sf::Vector2f	exitPos(tmpVec.x, tmpVec.y);
      tmpVec = exit->GetDimensions();
      sf::Vector2f	exitDim(tmpVec.x, tmpVec.y);

      _gameObjects.push_back(new Exit(exitPos, exitDim, exit->GetName()));
    }
  else
    std::cerr << "No Exit for this map" << std::endl;
}
