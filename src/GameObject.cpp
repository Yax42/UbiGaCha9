#include "GameObject.hh"

GameObject::GameObject(const Asset & asset, sf::Vector2f &pos, float size) : 
	_asset(asset), _speed(0, 0), _pos(pos), _hitBoxSize(size)
{
}

void	GameObject::update(float ft)
{
  _asset.update();
  _pos += _speed * ft;
}

void		GameObject::draw()
{
  _asset.draw(_pos, _angle);
}

void		GameObject::setPos(const sf::Vector2f &pos)
{
	_pos = pos;
}

void		GameObject::incPos(const sf::Vector2f &pos)
{
	_pos += pos;
}

void	GameObject::setSpeed(const sf::Vector2f &speed)
{
	_speed = speed;
}

void	GameObject::incSpeed(const sf::Vector2f &speed)
{
	_speed += speed;
}