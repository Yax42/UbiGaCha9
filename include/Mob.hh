
#ifndef MOB_HH_
#define MOB_HH_

#include "GameObject.hh"

class Mob : public GameObject
{
public:
  Mob(const sf::Vector2f &pos, AssetDescriptor &assetDesc, float speed);
  virtual ~Mob(){}

public:
	void	Follow();
	static void setAssetDesc(AssetDescriptor &assetDesc);
	virtual void	update(float dt, size_t frameCount);
	virtual bool collides(GameObject &obj);
protected:
	virtual void	updateSprite();
public:
	static void		initAsset();
	bool			_isMad;
};

#endif