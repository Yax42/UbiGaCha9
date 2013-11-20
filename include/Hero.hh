#ifndef HERO_HH
#define HERO_HH

#include "Scoring.hh"
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
  virtual ~Hero()
  {
    Scoring::sendScore("127.0.0.1", 4242, _score);
  }

  virtual void		update(float dt, size_t frameCount);
  virtual bool		collides(GameObject &obj);
  virtual bool		isDead();
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
	bool			_sound;
  static std::vector<bool>	_listWeapons;
  static std::vector<int>	_listEquip;
  int				_prevWalk;
  unsigned int			_score;
  bool				_die;
};

#endif
