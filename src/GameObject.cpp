#include "GameObject.hh"

AGameObject::AGameObject(sf::Vector2f &pos, float size) : 
	_asset(asset), _speed(0, 0), _pos(pos), _hitBoxSize(size)
{
}

virtual void	AGameObject::update(float ft)
{
	asset.update();
	_pos += _speed * ft;
}

void		AGameObject::draw()
{
	asset.draw(_pos, _angle);
}