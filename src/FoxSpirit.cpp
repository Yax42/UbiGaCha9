#include "FoxSpirit.hh"

const AssetDescriptor FoxSpirit::s_assetDesc("ressource/FoxSpirit.png");

FoxSpirit::FoxSpirit(sf::Vector2f &pos)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(32, 32))
{
}

void		FoxSpirit::initAsset()
{
}
