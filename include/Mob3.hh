#ifndef MOB_3_HH_
#define MOB_3_HH_

#include "Mob.hh"

class Mob3 : public Mob
{
public:
  Mob3(const sf::Vector2f &pos);
  virtual ~Mob3(){}

private:
	static AssetDescriptor s_assetDesc;
public:
	static void		initAsset();
};

#endif