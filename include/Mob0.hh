#ifndef MOB_0_HH_
#define MOB_0_HH_

#include "Mob.hh"

class Mob0 : public Mob
{
public:
  Mob0(const sf::Vector2f &pos);
  virtual ~Mob0(){}

private:
	static AssetDescriptor s_assetDesc;
public:
	static void		initAsset();
};

#endif