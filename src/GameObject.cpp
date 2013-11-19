#include <math.h>
#include <iostream>

#include "GameObject.hh"

GameObject::GameObject(const Asset &asset, const sf::Vector2f &pos,
		       const sf::Vector2f &size, float maxSpeed, bool collide)
  : _asset(asset),
    _box(pos, size),
    _backPos(pos),
    _orientation(DOWN),
    _angle(0.f),
    _collide(collide),
    _maxSpeed(maxSpeed),
	_state(STAND),
	_stateCount(0),
	_weapon(0)
{
}

void	GameObject::update(float ft, size_t frameCount)
{
  _backPos = sf::Vector2f(_box.left, _box.top);
  _box.left += _direction.x * ft * _maxSpeed;
  _box.top += _direction.y * ft * _maxSpeed;
  if ((frameCount % 8) == 0)
    updateSprite();
}

void		GameObject::draw(sf::RenderTexture &window)
{
  _asset.draw(sf::Vector2f(_box.left, _box.top), _angle, window);
}

void	GameObject::toBackPosition()
{
  _box.left = _backPos.x;
  _box.top = _backPos.y;
}

int				GameObject::calculateCurLine()
{
  if (_state == DIE)
	  return (DIE);
  else
    return (_orientation + 4 * _state + _weapon * 12 + 1);
}

void			GameObject::updateSprite()
{
  int		xSign =  (_direction.x > 0) ? 1 : -1;
  int		ySign =  (_direction.y > 0) ? 1 : -1;

  int		xAbs = xSign * _direction.x;
  int		yAbs = ySign * _direction.y;

  if (_stateCount == 0)
  {
	  if (_order > STAND)
	  {
		_state = _order;
		_stateCount = _asset.getCount(calculateCurLine());
	  }
	  else if (xAbs + yAbs > 0)
	  {
		  if (xAbs > yAbs)
			  _orientation = xSign > 0 ? RIGHT : LEFT;
		  else
			  _orientation = ySign > 0 ? DOWN : UP;
		  _state = WALK;
	  }
	  else
		  _state = STAND;
  }
  else
  {
	_order = 0;
	_stateCount--;
  }
  _asset.setCurrentLine(calculateCurLine());
  _asset.update();
}

bool GameObject::collides(const GameObject &obj) const
{
  if (_collide == false || obj._collide == false)
    return (false);
  return (_box.intersects(obj._box));
}

bool	GameObject::isDead()
{
	return (_state == DIE && _stateCount == 0);
}
