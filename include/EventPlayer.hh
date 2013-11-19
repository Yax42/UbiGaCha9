#ifndef	_ACONTROLLER_HH_
#define	_ACONTROLLER_HH_

#include <SFML/Window.hpp>
#include "GameObject.hh"

class	EventPlayer
{
public:
  EventPlayer(GameObject * monk, GameObject * lantern);
  virtual ~EventPlayer() {}
  void	pressPlayerLeft(int);
  void	pressPlayerLeft();
  void	pressPlayerRight(int);
  void	pressPlayerRight();
  void	pressPlayerUp(int);
  void	pressPlayerUp();
  void	pressPlayerDown(int);
  void	pressPlayerDown();
  void	pressLanternLeft(int);
  void	pressLanternLeft();
  void	pressLanternRight(int);
  void	pressLanternRight();
  void	pressLanternUp(int);
  void	pressLanternUp();
  void	pressLanternDown(int);
  void	pressLanternDown();
  void	pressStart();
  void	pressA();
  void	pressB();
  void	pressX();
  void	pressY();
  void	releasePlayerLeft();
  void	releasePlayerRight();
  void	releasePlayerDown();
  void	releasePlayerUp();
  void	releaseLanternLeft();
  void	releaseLanternRight();
  void	releaseLanternDown();
  void	releaseLanternUp();
  void	releaseA();
  void	releaseB();
  void	releaseX();
  void	releaseY();
  virtual void handleEvent(sf::Event &) = 0;
private:
  GameObject * _monk;
  GameObject * _lantern;
};

#endif	// _ACONTROLLER_HH_
