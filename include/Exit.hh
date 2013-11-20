#ifndef		__EXIT_HH__
#define		__EXIT_HH__

#include <string>
#include "GameObject.hh"

class Exit : public GameObject
{
public:
  Exit(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &name)
    : GameObject(Asset(_ad), pos, size),
      _name(name)
  {
    _type = 3;
  }

  virtual ~Exit() {}

  virtual void		update(float fd, size_t frameCount) {}
  virtual void		draw(sf::RenderTexture &window) {}

  const std::string	&getName() const {return (_name);}

private:
  AssetDescriptor	_ad;
  std::string		_name;
};

#endif	//	__EXIT_HH__
