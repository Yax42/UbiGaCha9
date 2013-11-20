#include "ItemObject.hh"
#include "World.hh"

AssetDescriptor ItemObject::s_assetDesc[4] =
  {
    AssetDescriptor("ressource/textures/stick.png"),
    AssetDescriptor("ressource/textures/sword.png"),
    AssetDescriptor("ressource/textures/bow.png"),
    AssetDescriptor("ressource/textures/kameha.png")
  };

ItemObject::ItemObject(const sf::Vector2f &pos, int id)
  : GameObject(Asset(s_assetDesc[id]), pos, sf::Vector2f(20, 20)),
    _id(id)
{
}

bool	ItemObject::collides(GameObject &obj)
{
  if (_collide == false || obj._collide == false)
    return (false);
  if (&obj == World::hero)
    {
      giveOrder(DIE);
      World::hero->_listWeapons[_id] = true;
      return (false);
    }
  return (_box.intersects(obj._box));
}

void	ItemObject::initAsset()
{
  s_assetDesc[0].addLine(20, 20, 1);
  s_assetDesc[1].addLine(20, 20, 1);
  s_assetDesc[2].addLine(20, 20, 1);
  s_assetDesc[3].addLine(20, 20, 1);
}
