#include "Hero.hh"

const AssetDescriptor Hero::s_assetDesc("ressource/Hero.png");

void		Hero::initAsset()
{
}

Hero::Hero(sf::Vector2f &pos) : 
	GameObject(Asset(s_assetDesc), pos, 32)
{
}
