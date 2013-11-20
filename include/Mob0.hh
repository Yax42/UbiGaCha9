#ifndef MOB_0_HH_
#define MOB_0_HH_

#include "GameObject.hh"

class Mob0 : public GameObject
{
public:
  Mob0(const sf::Vector2f &pos);
  virtual ~Mob0(){}

private:
	static AssetDescriptor s_assetDesc;
protected:
	virtual void	updateSprite();
public:
	static void		initAsset();
};

#endif