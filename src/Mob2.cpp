#include "Mob2.hh"

AssetDescriptor Mob2::s_assetDesc("ressource/textures/mob2.png");

void		Mob2::initAsset()
{
	Mob::setAssetDesc(s_assetDesc);
}

Mob2::Mob2(const sf::Vector2f &pos)
  : Mob(pos, s_assetDesc,  30)
{
	_mobType = 2;
}

