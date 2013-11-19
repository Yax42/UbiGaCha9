
#ifndef MOB_HH_
#define MOB_HH_

#include "GameObject.hh"

class Mob : public GameObject
{
public:
  Mob(const sf::Vector2f &pos, AssetDescriptor &assetDesc, float speed);
  virtual ~Mob(){}

protected:
	virtual void	updateSprite();
public:
	static void		initAsset();
};

#endif