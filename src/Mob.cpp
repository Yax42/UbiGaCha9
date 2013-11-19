#include "Mob.hh"

Mob::Mob(const sf::Vector2f &pos, AssetDescriptor &assetDesc, float speed)
  : GameObject(Asset(assetDesc), pos, sf::Vector2f(32, 32), speed)
{
	_type = 2;
	_mobType = 0;
}

void			Mob::updateSprite()
{
  int		xSign =  (_direction.x > 0) ? 1 : -1;
  int		ySign =  (_direction.y > 0) ? 1 : -1;

  int		xAbs = xSign * _direction.x;
  int		yAbs = ySign * _direction.y;
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