#include "Hero.hh"

const AssetDescriptor Hero::s_assetDesc("ressource/fox.png");

void		Hero::initAsset()
{
	s_assetDesc.addLine(32, 8, 4);
	s_assetDesc.addLine(32, 8, 4);
	s_assetDesc.addLine(32, 8, 4);
	s_assetDesc.addLine(32, 8, 4);
}

Hero::Hero(const sf::Vector2f &pos)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(32, 32))
{
}
