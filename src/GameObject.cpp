#include "GameObject.hh"

GameObject::GameObject(const Asset &asset, const sf::Vector2f &pos,
		       const sf::Vector2f &size, bool collide)
  : _asset(asset),
    _box(pos, size),
    _angle(0.f),
    _collide(collide)
{
}

void	GameObject::update(float ft)
{
  _backPos = sf::Vector2f(_box.left, _box.top);
  _box.left += _direction.x * ft;
  _box.top += _direction.y * ft;
  _asset.update();
}

void		GameObject::draw()
{
  _asset.draw(sf::Vector2f(_box.left, _box.top), _angle);
}

void	GameObject::toBackPosition()
{
  _box.left = _backPos.x;
  _box.top = _backPos.y;
}
