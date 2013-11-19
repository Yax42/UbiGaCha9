#include <iostream>
#include <math.h>
#include "Controller.hh"

Controller::Controller(GameObject & monk, GameObject & lantern)
  : EventPlayer(monk, lantern)
{
  this->_mapPressButton[0] = &Controller::pressA;
  this->_mapPressButton[1] = &Controller::pressB;
  this->_mapPressButton[2] = &Controller::pressX;
  this->_mapPressButton[3] = &Controller::pressY;
  this->_mapPressButton[7] = &Controller::pressStart;
  this->_mapReleaseButton[0] = &Controller::releaseA;
  this->_mapReleaseButton[1] = &Controller::releaseB;
  this->_mapReleaseButton[2] = &Controller::releaseX;
  this->_mapReleaseButton[3] = &Controller::releaseY;
  this->_mapMove[sf::Joystick::Y] = &Controller::playerVertical;
  this->_mapMove[sf::Joystick::X] = &Controller::playerHorizontal;
  this->_mapMove[sf::Joystick::V] = &Controller::lanternVertical;
  this->_mapMove[sf::Joystick::U] = &Controller::lanternHorizontal;

  this->_mapPress[sf::Keyboard::Up] = &Controller::pressPlayerUp;
  this->_mapPress[sf::Keyboard::Down] = &Controller::pressPlayerDown;
  this->_mapPress[sf::Keyboard::Left] = &Controller::pressPlayerLeft;
  this->_mapPress[sf::Keyboard::Right] = &Controller::pressPlayerRight;
  this->_mapPress[sf::Keyboard::Z] = &Controller::pressLanternUp;
  this->_mapPress[sf::Keyboard::Q] = &Controller::pressLanternLeft;
  this->_mapPress[sf::Keyboard::S] = &Controller::pressLanternDown;
  this->_mapPress[sf::Keyboard::D] = &Controller::pressLanternRight;
  this->_mapPress[sf::Keyboard::X] = &Controller::pressA;
  this->_mapPress[sf::Keyboard::C] = &Controller::pressB;
  this->_mapPress[sf::Keyboard::V] = &Controller::pressX;
  this->_mapPress[sf::Keyboard::B] = &Controller::pressY;

  this->_mapRelease[sf::Keyboard::X] = &Controller::releaseA;
  this->_mapRelease[sf::Keyboard::C] = &Controller::releaseB;
  this->_mapRelease[sf::Keyboard::V] = &Controller::releaseX;
  this->_mapRelease[sf::Keyboard::B] = &Controller::releaseY;
  this->_mapRelease[sf::Keyboard::Up] = &Controller::releasePlayerUp;
  this->_mapRelease[sf::Keyboard::Down] = &Controller::releasePlayerDown;
  this->_mapRelease[sf::Keyboard::Left] = &Controller::releasePlayerLeft;
  this->_mapRelease[sf::Keyboard::Right] = &Controller::releasePlayerRight;
  this->_mapRelease[sf::Keyboard::Z] = &Controller::releaseLanternUp;
  this->_mapRelease[sf::Keyboard::S] = &Controller::releaseLanternDown;
  this->_mapRelease[sf::Keyboard::Q] = &Controller::releaseLanternLeft;
  this->_mapRelease[sf::Keyboard::D] = &Controller::releaseLanternRight;
  this->_mapRelease[sf::Keyboard::Escape] = &Controller::pressStart;
}

Controller::~Controller()
{
  this->_mapMove.clear();
  this->_mapPressButton.clear();
  this->_mapReleaseButton.clear();
  this->_mapPress.clear();
  this->_mapRelease.clear();
}

void	Controller::playerVertical(int speed)
{
	if (speed >= -25 && speed <= 25)
		speed = 0;
	this->axisLeftY(speed);
}

void	Controller::playerHorizontal(int speed)
{
	if (speed >= -25 && speed <= 25)
		speed = 0;
	this->axisLeftX(speed);
}

void	Controller::lanternVertical(int speed)
{
	if (speed >= -25 && speed <= 25)
		speed = 0;
	this->axisRightY(speed);
}

void	Controller::lanternHorizontal(int speed)
{
	if (speed >= -25 && speed <= 25)
	  speed = 0;
	this->axisRightX(speed);
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
      std::map<unsigned int, void (Controller::*)()>::iterator      it;

      if ((it = this->_mapPressButton.find(event.joystickButton.button)) != this->_mapPressButton.end())
	(this->*(it->second))();
    }
  if (event.type == sf::Event::JoystickButtonReleased)
    {
      std::map<unsigned int, void (Controller::*)()>::iterator      it;

      if ((it = this->_mapReleaseButton.find(event.joystickButton.button)) != this->_mapReleaseButton.end())
	(this->*(it->second))();
    }
  if (event.type == sf::Event::KeyPressed)
    {
      std::map<sf::Keyboard::Key, void (Controller::*)()>::iterator      it;

      if ((it = this->_mapPress.find(event.key.code)) != this->_mapPress.end())
	(this->*(it->second))();
    }
  if (event.type == sf::Event::KeyReleased)
    {
      std::map<sf::Keyboard::Key, void (Controller::*)()>::iterator      it;

      if ((it = this->_mapRelease.find(event.key.code)) != this->_mapRelease.end())
	(this->*(it->second))();
    }  
}

void	Controller::pressPlayerLeft(int speed)
{
	this->axisLeftX(speed);
}

void	Controller::pressPlayerRight(int speed)
{
	this->axisLeftX(speed);
}

void	Controller::pressPlayerUp(int speed)
{
	this->axisLeftY(speed);
}

void	Controller::pressPlayerDown(int speed)
{
	this->axisLeftY(speed);
}

void	Controller::pressPlayerLeft()
{
	this->axisLeftX(-100);
}

void	Controller::pressPlayerRight()
{
	this->axisLeftX(100);
}

void	Controller::pressPlayerUp()
{
	this->axisLeftY(-100);
}

void	Controller::pressPlayerDown()
{
	this->axisLeftY(100);
}

void	Controller::pressLanternLeft(int speed)
{
	this->axisRightX(speed);
}

void	Controller::pressLanternRight(int speed)
{
	this->axisRightX(speed);
}

void	Controller::pressLanternUp(int speed)
{
	this->axisRightY(speed);
}

void	Controller::pressLanternDown(int speed)
{
	this->axisRightY(speed);
}

void	Controller::pressLanternLeft()
{
	this->axisRightX(-100);
}

void	Controller::pressLanternRight()
{
	this->axisRightX(100);
}

void	Controller::pressLanternUp()
{
	this->axisRightY(-100);
}

void	Controller::pressLanternDown()
{
	this->axisRightY(100);
}

void	Controller::releasePlayerLeft()
{
	this->axisLeftX(0);
}

void	Controller::releasePlayerRight()
{
	this->axisLeftX(0);
}

void	Controller::releasePlayerUp()
{
	this->axisLeftY(0);
}

void	Controller::releasePlayerDown()
{
	this->axisLeftY(0);
}

void	Controller::releaseLanternLeft()
{
	this->axisRightX(0);
}

void	Controller::releaseLanternRight()
{
	this->axisRightX(0);
}

void	Controller::releaseLanternUp()
{
	this->axisRightY(0);
}

void	Controller::releaseLanternDown()
{
	this->axisRightY(0);
}
