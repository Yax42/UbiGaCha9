#ifndef MOB_1_HH_
#define MOB_1_HH_

#include "Mob.hh"

class Mob1 : public Mob
{
public:
  Mob1(const sf::Vector2f &pos);
  virtual ~Mob1(){}

private:
	static AssetDescriptor s_assetDesc;
public:
	static void		initAsset();
};

#endif