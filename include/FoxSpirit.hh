#ifndef FOXSPIRIT_HH
#define FOXSPIRIT_HH

#include "AssetDescriptor.hh"
#include "GameObject.hh"

class FoxSpirit : public GameObject
{
public:
	FoxSpirit(const sf::Vector2f &pos = sf::Vector2f());
	virtual ~FoxSpirit(){}
	virtual bool			isDead();

private:
	static AssetDescriptor s_assetDesc;
public:
	static void		initAsset();
};

#endif
