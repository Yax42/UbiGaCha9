#include <math.h>
#include "Mob.hh"
#include "World.hh"

void Mob::setAssetDesc(AssetDescriptor &assetDesc)
{
	//DIE
	assetDesc.addLine(32, 32, 8);

	//STAND WEAPON 0
	assetDesc.addLine(32, 8, 4);
	assetDesc.addLine(32, 8, 4);
	assetDesc.addLine(32, 8, 4);
	assetDesc.addLine(32, 8, 4);
	//WALK WEAPON 0
	assetDesc.addLine(32, 8, 3);
	assetDesc.addLine(32, 8, 3);
	assetDesc.addLine(32, 8, 3);
	assetDesc.addLine(32, 8, 3);
}

Mob::Mob(const sf::Vector2f &pos, AssetDescriptor &assetDesc, float speed)
  : GameObject(Asset(assetDesc), pos, sf::Vector2f(8, 16), speed)
{
	_isMad = false;
	_type = 2;
}

Mob::~Mob()
{
  World::hero->_score += 100 * _mobType;
}

void			Mob::updateSprite()
{
  int		xSign =  (_direction.x > 0) ? 1 : -1;
  int		ySign =  (_direction.y > 0) ? 1 : -1;

  float		xAbs = xSign * _direction.x;
  float		yAbs = ySign * _direction.y;
  if (xAbs + yAbs > 0)
	  {
		  if (xAbs > yAbs)
			  _orientation = xSign > 0 ? RIGHT : LEFT;
		  else
			  _orientation = ySign > 0 ? DOWN : UP;
		  _state = WALK;
	  }
	  if (_order > -1)
	  {
		_state = _order;
		_order = -1;
	  }
  if (_state == DIE)
	_asset.setCurrentLine(DIE);
  else
	_asset.setCurrentLine(_orientation + 4 * (_state - 1) + 1);
  _asset.update();
}

void	Mob::Follow()
{
	sf::Vector2f		vect = World::hero->getPos() - getPos();

	float	range = sqrt(vect.x * vect.x + vect.y * vect.y);
	if (range < 100)
		_isMad = true;
	else
		_isMad = false;

	if (_isMad)
	{
		_direction.x = vect.x / range;
		_direction.y = vect.y / range;
	}
	else
	{
		_direction.x = 0;
		_direction.y = 0;
	}
}

void	Mob::update(float ft, size_t frameCount)
{
  _backPos = sf::Vector2f(_box.left, _box.top);
  _box.left += _direction.x * ft * _maxSpeed;
  _box.top += _direction.y * ft * _maxSpeed;
  if (frameCount % (16 * _mobType) == 0)
	Follow();
  if ((frameCount % 8) == 0)
    updateSprite();
}

bool Mob::collides(GameObject &obj)
{
	if (obj._type == 2)
	    return (false);

	bool actualResult = _box.intersects(obj._box);

	if (!actualResult)
		return (false);

	if (obj._type == 1)
	{
		if (obj._state == ATTACK && obj._weapon <= 1)
		{
			bool hbResult = _box.intersects((dynamic_cast<Hero *>(&obj))->_attackBox);
			if (hbResult && obj._weapon == 0 && _mobType == 0)
				giveOrder(DIE);
			else if (hbResult && obj._weapon == 1 && _mobType == 1)
				giveOrder(DIE);
		}
	}
	else if (obj._type == 4 && _mobType == 2)
		giveOrder(DIE);
	else if (obj._type == 5 && _mobType == 3)
		giveOrder(DIE);
	return (obj._type == 0);
}
