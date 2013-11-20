#include "Mob1.hh"

AssetDescriptor Mob1::s_assetDesc("ressource/textures/mob1.png");

void		Mob1::initAsset()
{
	Mob::setAssetDesc(s_assetDesc);
}

Mob1::Mob1(const sf::Vector2f &pos)
  : Mob(pos, s_assetDesc,  5)
{
	_mobType = 1;
}

