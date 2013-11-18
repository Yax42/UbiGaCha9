#include <iostream>
#include <math.h>
#include "Controller.hh"

Controller::Controller()
{
  this->_mapPressButton[0] = &AController::pressAttack;
  this->_mapPressButton[7] = &AController::pressStart;
  this->_mapReleaseButton[0] = &AController::releaseAttack;
  this->_mapMove[sf::Joystick::Y] = &Controller::vertical;
  this->_mapMove[sf::Joystick::X] = &Controller::horizontal;

  this->_mapPress[sf::Keyboard::Space] = &AController::pressAttack;
  this->_mapPress[sf::Keyboard::Up] = &AController::pressUp;
  this->_mapPress[sf::Keyboard::Down] = &AController::pressDown;
  this->_mapPress[sf::Keyboard::Left] = &AController::pressLeft;
  this->_mapPress[sf::Keyboard::Right] = &AController::pressRight;

  this->_mapRelease[sf::Keyboard::Space] = &AController::releaseAttack;
  this->_mapRelease[sf::Keyboard::Up] = &AController::releaseUp;
  this->_mapRelease[sf::Keyboard::Down] = &AController::releaseDown;
  this->_mapRelease[sf::Keyboard::Left] = &AController::releaseLeft;
  this->_mapRelease[sf::Keyboard::Right] = &AController::releaseRight;
  this->_mapRelease[sf::Keyboard::Escape] = &AController::pressStart;
}

Controller::~Controller()
{
  this->_mapMove.clear();
  this->_mapPressButton.clear();
  this->_mapReleaseButton.clear();
  this->_mapPress.clear();
  this->_mapRelease.clear();
}

void	Controller::vertical(int speed)
{
  if (abs(speed) >= 25 && abs(speed) <= 100)
    {
      if (speed > 0)
	this->pressDown(speed); // Down
      else
	this->pressUp(speed); // Up
    }
  else
    this->releaseUp();
}

void	Controller::horizontal(int speed)
{
  if (abs(speed) >= 25 && abs(speed) <= 100)
    {
      if (speed > 0)
	this->pressRight(speed); // Right
      else
	this->pressLeft(speed); // Left
    }
  else
    this->releaseLeft();
}

void	Controller::handleEvent(sf::Event & event)
{
  if (event.type == sf::Event::TextEntered)
    {
      if (event.text.unicode < 128)
	std::cout << static_cast<char>(event.text.unicode) << std::endl;
    }
  if(event.type == sf::Event::JoystickMoved)
    {
      if (event.joystickMove.joystickId > 0)
	{
	  std::map<sf::Joystick::Axis, void (Controller::*)(int)>::iterator      it;

	  if ((it = this->_mapMove.find(event.joystickMove.axis)) != this->_mapMove.end())
	    (this->*(it->second))(event.joystickMove.position);
	}
    }
  if (event.type == sf::Event::JoystickButtonPressed)
    {
      std::map<unsigned int, void (AController::*)()>::iterator      it;

      if ((it = this->_mapPressButton.find(event.joystickButton.button)) != this->_mapPressButton.end())
	(this->*(it->second))();
    }
  if (event.type == sf::Event::JoystickButtonReleased)
    {
      std::map<unsigned int, void (AController::*)()>::iterator      it;

      if ((it = this->_mapReleaseButton.find(event.joystickButton.button)) != this->_mapReleaseButton.end())
	(this->*(it->second))();
    }
  if (event.type == sf::Event::KeyPressed)
    {
      std::map<sf::Keyboard::Key, void (AController::*)()>::iterator      it;

      if ((it = this->_mapPress.find(event.key.code)) != this->_mapPress.end())
	(this->*(it->second))();
    }
  if (event.type == sf::Event::KeyReleased)
    {
      std::map<sf::Keyboard::Key, void (AController::*)()>::iterator      it;

      if ((it = this->_mapRelease.find(event.key.code)) != this->_mapRelease.end())
	(this->*(it->second))();
    }  
}
