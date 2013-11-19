#ifndef HERO_HH
#define HERO_HH

#include "GameObject.hh"

class Hero : public GameObject
{
public:
  Hero(const sf::Vector2f &pos);
  virtual ~Hero(){}

private:
	static AssetDescriptor s_assetDesc;
public:
	static void		initAsset();
};

#endif
