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

void		AGameObject::setPos(const sf::Vector2f &pos)
{
	_pos = pos;
}

void		AGameObject::incPos(const sf::Vector2f &pos)
{
	_pos += pos;
}

void	AGameObject::setSpeed(const sf::Vector2f &speed)
{
	_speed = speed;
}

void	AGameObject::incSpeed(const sf::Vector2f &speed)
{
	_speed += speed;
}
