#ifndef ARROW_HH_
#define ARROW_HH_

#include "AssetDescriptor.hh"
#include "GameObject.hh"

class Arrow : public GameObject
{
public:
	Arrow(const sf::Vector2f &pos, const sf::Vector2f &dir);
	virtual ~Arrow(){}

private:
	static AssetDescriptor s_assetDesc;
	virtual void			toBackPosition();
	virtual bool			isDead();
public:
	static void		initAsset();
	int		_lifeTime;
	bool	_alive;
};

#endif