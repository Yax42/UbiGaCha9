#include <cmath>
#include "Box.hh"

Box::Box(const sf::Vector2f &center, const sf::Vector2f &halfDimension)
  : _center(center),
    _halfDimension(halfDimension)
{
}

Box::~Box()
{
}

bool Box::contains(const Box &box) const
{
  return (box._center.x + box._halfDimension.x < _center.x + _halfDimension.x
	  && box._center.x - box._halfDimension.x > _center.x - _halfDimension.x
	  && box._center.y + box._halfDimension.y < _center.y + _halfDimension.y
	  && box._center.y - box._halfDimension.y > _center.y - _halfDimension.y);
}

bool Box::collides(const Box &box) const
{
  return (!((box._center.x - box._halfDimension.x >= _center.x + _halfDimension.x)
	    || (box._center.x + box._halfDimension.x <= _center.x - _halfDimension.x)
	    || (box._center.y - box._halfDimension.y >= _center.y + _halfDimension.y)
	    || (box._center.y + box._halfDimension.y <= _center.y - _halfDimension.y)));
}

const sf::Vector2f &Box::getCenter() const
{
  return (_center);
}

const sf::Vector2f &Box::getHalfDimension() const
{
  return (_halfDimension);
}

void Box::setCenter(const sf::Vector2f &center)
{
  _center = center;
}

void Box::setSize(float x, float y)
{
  _halfDimension.x = x;
  _halfDimension.y = y;
}
