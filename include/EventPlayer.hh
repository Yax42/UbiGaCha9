#ifndef	_ACONTROLLER_HH_
#define	_ACONTROLLER_HH_

#include <SFML/Window.hpp>
#include "GameObject.hh"

class	EventPlayer
{
public:
  EventPlayer(GameObject &monk, GameObject &lantern);
  virtual ~EventPlayer() {}

  void	axisLeftX(int speed);
  void	axisLeftY(int speed);
  void	axisRightX(int speed);
  void	axisRightY(int speed);
  void	horizontalRight(int speed);
  void	verticalRight(int speed);
  void	pressStart();
  void	pressA();
  void	pressB();
  void	pressX();
  void	pressY();
  void	releaseA();
  void	releaseB();
  void	releaseX();
  void	releaseY();
  virtual void handleEvent(sf::Event &) = 0;
private:
  GameObject	&_monk;
  GameObject	&_lantern;
};

#endif	// _ACONTROLLER_HH_
