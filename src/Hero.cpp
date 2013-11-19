#include "Hero.hh"

AssetDescriptor Hero::s_assetDesc("ressource/textures/monk.png");

void		Hero::initAsset()
{
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
}

Hero::Hero(const sf::Vector2f &pos)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(32, 32))
{
}
