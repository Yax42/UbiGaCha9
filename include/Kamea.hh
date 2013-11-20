#ifndef KAMEA_HH_
#define KAMEA_HH_

#include "AssetDescriptor.hh"
#include "GameObject.hh"

class Kamea : public GameObject
{
public:
	Kamea(const sf::Vector2f &pos);
	virtual ~Kamea(){}
	virtual bool			isDead();

private:
	static AssetDescriptor s_assetDesc;
	virtual void			toBackPosition();
	virtual void		update(float dt, size_t frameCount);
public:
	static void		initAsset();
	int		_lifeTime;
		
};

#endif