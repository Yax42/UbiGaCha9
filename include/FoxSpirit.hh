#ifndef HERO_HH
#define HERO_HH

#include "AssetDescriptor.hh"
#include "GameObject.hh"

class FoxSpirit : public GameObject
{
public:
	FoxSpirit(sf::Vector2f &pos);
	virtual ~FoxSpirit(){}




private:
	const static AssetDescriptor s_assetDesc;
public:
	static void		initAsset();
};

#endif