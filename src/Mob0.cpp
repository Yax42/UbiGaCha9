#include "Mob0.hh"

AssetDescriptor Mob0::s_assetDesc("ressource/textures/mob0.png");

void		Mob0::initAsset()
{
	Mob::setAssetDesc(s_assetDesc);
}

Mob0::Mob0(const sf::Vector2f &pos)
  : Mob(pos, s_assetDesc,  10)
{
	_mobType = 0;
}

