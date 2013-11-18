#ifndef		__BOX_HH__
#define		__BOX_HH__

#include <SFML/Graphics.hpp>

class		Box
{
public:
  Box(const sf::Vector2f &center = sf::Vector2f(), const sf::Vector2f &halfDimension = sf::Vector2f());
  ~Box();
  bool			contains(const Box &box) const;
  bool			collides(const Box &box) const;
  const sf::Vector2f	&getCenter() const;
  const sf::Vector2f	&getHalfDimension() const;
  void			setCenter(const sf::Vector2f &center);
  void			setSize(float x, float y);
private:
  sf::Vector2f			_center;
  sf::Vector2f			_halfDimension;
};

#endif	//	__BOX_HH__
