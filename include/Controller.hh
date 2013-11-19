#ifndef _CONTROLLER_HH_
#define	_CONTROLLER_HH_

#include <map>
#include "EventPlayer.hh"

class Controller : public EventPlayer
{
public:
  Controller(GameObject * monk, GameObject * lantern);
  ~Controller();
  void	playerVertical(int);
  void	playerHorizontal(int);
  void	lanternVertical(int);
  void	lanternHorizontal(int);
  virtual void	handleEvent(sf::Event &);
private:
  std::map<sf::Keyboard::Key, void (EventPlayer::*)()> _mapPress;
  std::map<sf::Keyboard::Key, void (EventPlayer::*)()> _mapRelease;
  std::map<unsigned int, void (EventPlayer::*)()> _mapPressButton;
  std::map<unsigned int, void (EventPlayer::*)()> _mapReleaseButton;
  std::map<sf::Joystick::Axis, void (Controller::*)(int)> _mapMove;
};

#endif	// _CONTROLLER_HH_
