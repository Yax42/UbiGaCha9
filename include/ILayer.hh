#ifndef	_ILAYER_HH_
#define	_ILAYER_HH_

#include <SFML/Graphics.hpp>

typedef enum e_state
{
	MENU,
	PLAY,
	LEADER,
	WHO,
	QUIT
}			State;

class	ILayer
{
public:
  virtual ~ILayer() {}
  virtual bool update(sf::Event &) = 0;
  virtual void draw() = 0;
  virtual void run() = 0;
private:
};

#endif // _ILAYER_HH_
