#include <iostream>
#include <math.h>
#include "Controller.hh"

Controller::Controller(GameObject * monk, GameObject * lantern)
  : EventPlayer(monk, lantern)
{
  this->_mapPressButton[0] = &EventPlayer::pressA;
  this->_mapPressButton[1] = &EventPlayer::pressB;
  this->_mapPressButton[2] = &EventPlayer::pressX;
  this->_mapPressButton[3] = &EventPlayer::pressY;
  this->_mapPressButton[7] = &EventPlayer::pressStart;
  this->_mapReleaseButton[0] = &EventPlayer::releaseA;
  this->_mapReleaseButton[1] = &EventPlayer::releaseB;
  this->_mapReleaseButton[2] = &EventPlayer::releaseX;
  this->_mapReleaseButton[3] = &EventPlayer::releaseY;
  this->_mapMove[sf::Joystick::Y] = &Controller::playerVertical;
  this->_mapMove[sf::Joystick::X] = &Controller::playerHorizontal;
  this->_mapMove[sf::Joystick::V] = &Controller::lanternVertical;
  this->_mapMove[sf::Joystick::U] = &Controller::lanternHorizontal;

  this->_mapPress[sf::Keyboard::Up] = &EventPlayer::pressPlayerUp;
  this->_mapPress[sf::Keyboard::Down] = &EventPlayer::pressPlayerDown;
  this->_mapPress[sf::Keyboard::Left] = &EventPlayer::pressPlayerLeft;
  this->_mapPress[sf::Keyboard::Right] = &EventPlayer::pressPlayerRight;
  this->_mapPress[sf::Keyboard::Z] = &EventPlayer::pressLanternRight;
  this->_mapRelease[sf::Keyboard::X] = &EventPlayer::pressA;
  this->_mapRelease[sf::Keyboard::C] = &EventPlayer::pressB;
  this->_mapRelease[sf::Keyboard::V] = &EventPlayer::pressX;
  this->_mapRelease[sf::Keyboard::B] = &EventPlayer::pressY;

  this->_mapRelease[sf::Keyboard::X] = &EventPlayer::releaseA;
  this->_mapRelease[sf::Keyboard::C] = &EventPlayer::releaseB;
  this->_mapRelease[sf::Keyboard::V] = &EventPlayer::releaseX;
  this->_mapRelease[sf::Keyboard::B] = &EventPlayer::releaseY;
  this->_mapRelease[sf::Keyboard::Up] = &EventPlayer::releasePlayerUp;
  this->_mapRelease[sf::Keyboard::Down] = &EventPlayer::releasePlayerDown;
  this->_mapRelease[sf::Keyboard::Left] = &EventPlayer::releasePlayerLeft;
  this->_mapRelease[sf::Keyboard::Right] = &EventPlayer::releasePlayerRight;
  this->_mapRelease[sf::Keyboard::Z] = &EventPlayer::releaseLanternUp;
  this->_mapRelease[sf::Keyboard::S] = &EventPlayer::releaseLanternDown;
  this->_mapRelease[sf::Keyboard::Q] = &EventPlayer::releaseLanternLeft;
  this->_mapRelease[sf::Keyboard::D] = &EventPlayer::releaseLanternRight;
  this->_mapRelease[sf::Keyboard::Escape] = &EventPlayer::pressStart;
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
  if (abs(speed) >= 25 && abs(speed) <= 100)
    {
      if (speed > 0)
	this->pressPlayerDown(speed); // Down
      else
	this->pressPlayerUp(speed); // Up
    }
  else
    this->releasePlayerUp();
}

void	Controller::playerHorizontal(int speed)
{
  if (abs(speed) >= 25 && abs(speed) <= 100)
    {
      if (speed > 0)
	this->pressPlayerRight(speed); // Right
      else
	this->pressPlayerLeft(speed); // Left
    }
  else
    this->releasePlayerLeft();
}

void	Controller::lanternVertical(int speed)
{
  if (abs(speed) >= 25 && abs(speed) <= 100)
    {
      if (speed > 0)
	this->pressLanternDown(speed); // Down
      else
	this->pressLanternUp(speed); // Up
    }
  else
    this->releaseLanternUp();
}

void	Controller::lanternHorizontal(int speed)
{
  if (abs(speed) >= 25 && abs(speed) <= 100)
    {
      if (speed > 0)
	this->pressLanternRight(speed); // Right
      else
	this->pressLanternLeft(speed); // Left
    }
  else
    this->releaseLanternLeft();
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
      std::map<unsigned int, void (EventPlayer::*)()>::iterator      it;

      if ((it = this->_mapPressButton.find(event.joystickButton.button)) != this->_mapPressButton.end())
	(this->*(it->second))();
    }
  if (event.type == sf::Event::JoystickButtonReleased)
    {
      std::map<unsigned int, void (EventPlayer::*)()>::iterator      it;

      if ((it = this->_mapReleaseButton.find(event.joystickButton.button)) != this->_mapReleaseButton.end())
	(this->*(it->second))();
    }
  if (event.type == sf::Event::KeyPressed)
    {
      std::map<sf::Keyboard::Key, void (EventPlayer::*)()>::iterator      it;

      if ((it = this->_mapPress.find(event.key.code)) != this->_mapPress.end())
	(this->*(it->second))();
    }
  if (event.type == sf::Event::KeyReleased)
    {
      std::map<sf::Keyboard::Key, void (EventPlayer::*)()>::iterator      it;

      if ((it = this->_mapRelease.find(event.key.code)) != this->_mapRelease.end())
	(this->*(it->second))();
    }  
}
