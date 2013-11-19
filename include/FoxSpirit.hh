#ifndef FOXSPIRIT_HH
#define FOXSPIRIT_HH

#include "AssetDescriptor.hh"
#include "GameObject.hh"

class FoxSpirit : public GameObject
{
public:
	FoxSpirit(const sf::Vector2f &pos);
	virtual ~FoxSpirit(){}

private:
	static AssetDescriptor s_assetDesc;
public:
	static void		initAsset();
};

#endif
