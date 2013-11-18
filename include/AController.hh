#ifndef	_ACONTROLLER_HH_
#define	_ACONTROLLER_HH_

#include <SFML/Window.hpp>

class	AController
{
public:
  AController() {}
  ~AController() {}
  void	pressLeft(int);
  void	pressLeft();
  void	pressRight(int);
  void	pressRight();
  void	pressUp(int);
  void	pressUp();
  void	pressDown(int);
  void	pressDown();
  void	pressStart();
  void	pressAttack();
  void	releaseLeft();
  void	releaseRight();
  void	releaseDown();
  void	releaseUp();
  void	releaseAttack();
  virtual void	handleEvent(sf::Event &) = 0;
};

#endif	// _ACONTROLLER_HH_
