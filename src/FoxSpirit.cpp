#include "FoxSpirit.hh"

const AssetDescriptor FoxSpirit::s_assetDesc("ressource/FoxSpirit.png");

void		FoxSpirit::initAsset()
{
}

FoxSpirit::FoxSpirit(sf::Vector2f &pos) : 
	GameObject(Asset(s_assetDesc), pos, 32)
{
}

