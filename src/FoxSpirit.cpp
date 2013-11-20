#include "FoxSpirit.hh"

AssetDescriptor FoxSpirit::s_assetDesc("ressource/textures/fox.png");

FoxSpirit::FoxSpirit(const sf::Vector2f &pos)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(32, 32))
{
	_type = 1;
}

void		FoxSpirit::initAsset()
{
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
}

bool	FoxSpirit::isDead()
{
	return (false);
}
