#ifndef		__WALL_HH__
#define		__WALL_HH__

#include "GameObject.hh"

class Wall : public GameObject
{
public:
  Wall(const sf::Vector2f &pos, const sf::Vector2f &size)
    : GameObject(Asset(_ad), pos, size)
  {
    _type = 0;
  }

  virtual ~Wall() {}

  virtual void		update(float fd, size_t frameCount) {}
  virtual void		draw(sf::RenderTexture &window) {}

private:
  AssetDescriptor	_ad;
};

#endif	//	__WALL_HH__
