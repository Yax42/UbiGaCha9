#ifndef _CONTROLLER_HH_
#define	_CONTROLLER_HH_

#include <map>
#include "EventPlayer.hh"

class Controller : public EventPlayer
{
public:
  Controller(GameObject & monk, GameObject & lantern);
  ~Controller();
  void	playerVertical(int);
  void	playerHorizontal(int);
  void	lanternVertical(int);
  void	lanternHorizontal(int);

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
  void	releasePlayerLeft();
  void	releasePlayerRight();
  void	releasePlayerDown();
  void	releasePlayerUp();
  void	releaseLanternLeft();
  void	releaseLanternRight();
  void	releaseLanternDown();
  void	releaseLanternUp();

  virtual void	handleEvent(sf::Event &);
private:
  std::map<sf::Keyboard::Key, void (Controller::*)()> _mapPress;
  std::map<sf::Keyboard::Key, void (Controller::*)()> _mapRelease;
  std::map<unsigned int, void (Controller::*)()> _mapPressButton;
  std::map<unsigned int, void (Controller::*)()> _mapReleaseButton;
  std::map<sf::Joystick::Axis, void (Controller::*)(int)> _mapMove;
};

#endif	// _CONTROLLER_HH_
