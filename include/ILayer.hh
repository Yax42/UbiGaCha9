#ifndef	_ILAYER_HH_
#define	_ILAYER_HH_

#include <SFML/Graphics.hpp>

class	ILayer
{
public:
  virtual ~ILayer() {}
  virtual bool update(sf::Event &) = 0;
  virtual void draw() = 0;
private:
};

#endif // _ILAYER_HH_
