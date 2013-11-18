#include "GameObject.hh"

AGameObject::AGameObject(const Asset & asset, sf::Vector2f &pos, float size) : 
	_asset(asset), _speed(0, 0), _pos(pos), _hitBoxSize(size)
{
}

void	AGameObject::update(float ft)
{
  _asset.update();
  _pos += _speed * ft;
}

void		AGameObject::draw()
{
  _asset.draw(_pos, _angle);
}
