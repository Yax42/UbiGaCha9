#include "Mob3.hh"

AssetDescriptor Mob3::s_assetDesc("ressource/textures/mob3.png");

void		Mob3::initAsset()
{
	Mob::setAssetDesc(s_assetDesc);
}

Mob3::Mob3(const sf::Vector2f &pos)
  : Mob(pos, s_assetDesc,  20)
{
	_mobType = 3;
}

