#include "EventPlayer.hh"
#include <iostream>

EventPlayer::EventPlayer(GameObject &monk, GameObject &lantern)
  : _monk(monk), _lantern(lantern)
{
}

void	EventPlayer::axisLeftX(int speed)
{
	_monk.dirX(speed);
}

void	EventPlayer::axisLeftY(int speed)
{
	_monk.dirY(speed);
}

void	EventPlayer::axisRightX(int speed)
{
	_lantern.dirX(speed);
}

void	EventPlayer::axisRightY(int speed)
{
	_lantern.dirY(speed);
}

void	EventPlayer::pressA()
{
  std::cout << "Press A" << std::endl;
}

void	EventPlayer::pressB()
{
  std::cout << "Press B" << std::endl;
}

void	EventPlayer::pressX()
{
  std::cout << "Press X" << std::endl;
}

void	EventPlayer::pressY()
{
  std::cout << "Press Y" << std::endl;
}

void	EventPlayer::pressStart()
{
  std::cout << "Press Start" << std::endl;
}

void	EventPlayer::releaseA()
{
  std::cout << "Release A" << std::endl;
}

void	EventPlayer::releaseB()
{
  std::cout << "Release B" << std::endl;
}

void	EventPlayer::releaseX()
{
  std::cout << "Release X" << std::endl;
}

void	EventPlayer::releaseY()
{
  std::cout << "Release Y" << std::endl;
}

