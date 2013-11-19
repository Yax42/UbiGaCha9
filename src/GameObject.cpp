#include <math.h>

#include "GameObject.hh"

GameObject::GameObject(const Asset &asset, const sf::Vector2f &pos,
		       const sf::Vector2f &size, float maxSpeed, bool collide)
  : _asset(asset),
    _box(pos, size),
    _backPos(pos),
    _orientation(DOWN),
    _angle(0.f),
    _collide(collide),
    _maxSpeed(maxSpeed)
{
}

void	GameObject::update(float ft, size_t frameCount)
{
  _backPos = sf::Vector2f(_box.left, _box.top);
  _box.left += _direction.x * ft * _maxSpeed;
  _box.top += _direction.y * ft * _maxSpeed;
  if ((frameCount % 4) == 0)
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

void			GameObject::updateSprite()
{
  int		xSign =  (_direction.x > 0) ? 1 : -1;
  int		ySign =  (_direction.y > 0) ? 1 : -1;

  int		xAbs = xSign * _direction.x;
  int		yAbs = ySign * _direction.y;

  if (xAbs + yAbs > 0)
  {
	if (xAbs > yAbs)
		_orientation = xSign ? RIGHT : LEFT;
	else
		_orientation = ySign ? DOWN : UP;
	_asset.setCurrentLine(_orientation);
  }
  else
	_asset.setCurrentLine(_orientation + 4);
  _asset.update();
}

bool GameObject::collides(const GameObject &obj) const
{
  if (_collide == false || obj._collide == false)
    return (false);
  return (_box.intersects(obj._box));
}
