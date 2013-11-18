#include "GameObject.hh"

AGameObject::AGameObject(const Asset &asset, sf::Vector2f &pos, float size, bool collide)
  : _asset(asset),
    _box(pos, sf::Vector2f(size / 2.f, size / 2.f)),
    _angle(0.f),
    _collide(collide)
{
}

void	GameObject::update(float ft)
{
  sf::Vector2f pos = _backPos = _box.getCenter();

  pos.x += _direction.x * ft;
  pos.y += _direction.y * ft;
  _box.setCenter(pos);
  _asset.update();
}

void	AGameObject::toBackPosition()
{
	_box.setCenter(_backPos);
}

void		GameObject::draw()
{
	_asset.draw(_box.getCenter(), _angle);
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
