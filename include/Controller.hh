#ifndef _CONTROLLER_HH_
#define	_CONTROLLER_HH_

#include <map>
#include "AController.hh"

class Controller : public AController
{
public:
  Controller();
  ~Controller();
  void	vertical(int);
  void	horizontal(int);
  virtual void	handleEvent(sf::Event &);
private:
  std::map<sf::Keyboard::Key, void (AController::*)()> _mapPress;
  std::map<sf::Keyboard::Key, void (AController::*)()> _mapRelease;
  std::map<unsigned int, void (AController::*)()> _mapPressButton;
  std::map<unsigned int, void (AController::*)()> _mapReleaseButton;
  std::map<sf::Joystick::Axis, void (Controller::*)(int)> _mapMove;
};

#endif	// _CONTROLLER_HH_
