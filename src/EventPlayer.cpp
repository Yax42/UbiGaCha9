#include "EventPlayer.hh"
#include <iostream>

EventPlayer::EventPlayer(GameObject &monk, GameObject &lantern)
  : _monk(monk), _lantern(lantern)
{
}

void	EventPlayer::axisLeftX(int speed)
{
	_monk.dirX(speed / 100.0);
}

void	EventPlayer::axisLeftY(int speed)
{
	_monk.dirY(speed / 100.0);
}

void	EventPlayer::axisRightX(int speed)
{
	_lantern.dirX(speed / 100.0);
}

void	EventPlayer::axisRightY(int speed)
{
	_lantern.dirY(speed / 100.0);
}

void	EventPlayer::pressA()
{
	_monk.giveOrder(GameObject::ATTACK);
}

void	EventPlayer::pressB()
{
	_monk.giveOrder(GameObject::ATTACK2);
}

void	EventPlayer::pressX()
{
//	_monk.weapon(!_monk.weapon());
}

void	EventPlayer::pressY()
{
}

void	EventPlayer::pressStart()
{
}

void	EventPlayer::releaseA()
{
}

void	EventPlayer::releaseB()
{
}

void	EventPlayer::releaseX()
{
}

void	EventPlayer::releaseY()
{
}
