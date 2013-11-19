#ifndef HERO_HH
#define HERO_HH

#include "GameObject.hh"

class Hero : public GameObject
{
public:
	Hero(sf::Vector2f &pos);
	virtual ~Hero(){}

private:
	const static AssetDescriptor s_assetDesc;
public:
	static void		initAsset();
};

#endif