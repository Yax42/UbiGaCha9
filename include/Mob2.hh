#ifndef MOB_2_HH_
#define MOB_2_HH_

#include "Mob.hh"

class Mob2 : public Mob
{
public:
  Mob2(const sf::Vector2f &pos);
  virtual ~Mob2(){}

private:
	static AssetDescriptor s_assetDesc;
public:
	static void		initAsset();
};

#endif