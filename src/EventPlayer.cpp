#include "EventPlayer.hh"
#include <iostream>

EventPlayer::EventPlayer(GameObject * monk, GameObject * lantern)
  : _monk(monk), _lantern(lantern)
{
}

void	EventPlayer::pressPlayerLeft(int speed)
{
  std::cout << "PressPlayerLeft speed : " << speed << std::endl;
}

void	EventPlayer::pressPlayerRight(int speed)
{
  std::cout << "PressPlayerRight speed : " << speed << std::endl;
}

void	EventPlayer::pressPlayerUp(int speed)
{
  std::cout << "PressPlayerUp speed : " << speed << std::endl;
}

void	EventPlayer::pressPlayerDown(int speed)
{
  std::cout << "PressPlayerDown speed : " << speed << std::endl;
}

void	EventPlayer::pressPlayerLeft()
{
  std::cout << "PressPlayerLeft speed : " << 100 << std::endl;
}

void	EventPlayer::pressPlayerRight()
{
  std::cout << "PressPlayerRight speed : " << 100 << std::endl;
}

void	EventPlayer::pressPlayerUp()
{
  std::cout << "PressPlayerUp speed : " << 100 << std::endl;
}

void	EventPlayer::pressPlayerDown()
{
  std::cout << "PressPlayerDown speed : " << 100 << std::endl;
}

void	EventPlayer::pressLanternLeft(int speed)
{
  std::cout << "PressLanternLeft speed : " << speed << std::endl;
}

void	EventPlayer::pressLanternRight(int speed)
{
  std::cout << "PressLanternRight speed : " << speed << std::endl;
}

void	EventPlayer::pressLanternUp(int speed)
{
  std::cout << "PressLanternUp speed : " << speed << std::endl;
}

void	EventPlayer::pressLanternDown(int speed)
{
  std::cout << "PressLanternDown speed : " << speed << std::endl;
}

void	EventPlayer::pressLanternLeft()
{
  std::cout << "PressLanternLeft speed : " << 100 << std::endl;
}

void	EventPlayer::pressLanternRight()
{
  std::cout << "PressLanternRight speed : " << 100 << std::endl;
}

void	EventPlayer::pressLanternUp()
{
  std::cout << "PressLanternUp speed : " << 100 << std::endl;
}

void	EventPlayer::pressLanternDown()
{
  std::cout << "PressLanternDown speed : " << 100 << std::endl;
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

void	EventPlayer::releasePlayerLeft()
{
  std::cout << "ReleaseLeft speed : " << 100 << std::endl;
}

void	EventPlayer::releasePlayerRight()
{
  std::cout << "ReleaseRight speed : " << 100 << std::endl;
}

void	EventPlayer::releasePlayerUp()
{
  std::cout << "ReleaseUp speed : " << 100 << std::endl;
}

void	EventPlayer::releasePlayerDown()
{
  std::cout << "ReleaseDown speed : " << 100 << std::endl;
}

void	EventPlayer::releaseLanternLeft()
{
  std::cout << "ReleaseLanternLeft speed : " << 100 << std::endl;
}

void	EventPlayer::releaseLanternRight()
{
  std::cout << "ReleaseLanternRight speed : " << 100 << std::endl;
}

void	EventPlayer::releaseLanternUp()
{
  std::cout << "ReleaseLanternUp speed : " << 100 << std::endl;
}

void	EventPlayer::releaseLanternDown()
{
  std::cout << "ReleaseLanternDown speed : " << 100 << std::endl;
}
