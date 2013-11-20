#ifndef HERO_HH
#define HERO_HH

#include "GameObject.hh"

class Hero : public GameObject
{
	enum
	{
		NO_ATTACK,
		ATTACK0,
		ATTACK1,
		ATTACK2,
		ATTACK3
	};

public:
  Hero(const sf::Vector2f &pos = sf::Vector2f());
  virtual ~Hero(){}

  virtual void		update(float dt, size_t frameCount);
  virtual bool		collides(GameObject &obj);

private:
	static AssetDescriptor s_assetDesc;
protected:
	virtual void	updateSprite();
	int				calculateCurLine();
public:
	static void		initAsset();
public:
	sf::FloatRect	_attackBox;
	int				_attackBoxState;
	int				_oldOrient;
  static std::vector<bool>	_listWeapons;
  static std::vector<int>	_listEquip;
};

#endif
