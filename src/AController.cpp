#include "AController.hh"
#include <iostream>

void	AController::pressLeft(int speed)
{
  std::cout << "PressLeft speed : " << speed << std::endl;
}

void	AController::pressRight(int speed)
{
  std::cout << "PressRight speed : " << speed << std::endl;
}

void	AController::pressUp(int speed)
{
  std::cout << "PressUp speed : " << speed << std::endl;
}

void	AController::pressDown(int speed)
{
  std::cout << "PressDown speed : " << speed << std::endl;
}

void	AController::pressLeft()
{
  std::cout << "PressLeft speed : " << 100 << std::endl;
}

void	AController::pressRight()
{
  std::cout << "PressRight speed : " << 100 << std::endl;
}

void	AController::pressUp()
{
  std::cout << "PressUp speed : " << 100 << std::endl;
}

void	AController::pressDown()
{
  std::cout << "PressDown speed : " << 100 << std::endl;
}

void	AController::pressAttack()
{
  std::cout << "Press Attack" << std::endl;
}

void	AController::pressStart()
{
  std::cout << "Press Start" << std::endl;
}

void	AController::releaseAttack()
{
  std::cout << "Release Attack" << std::endl;
}

void	AController::releaseLeft()
{
  std::cout << "ReleaseLeft speed : " << 100 << std::endl;
}

void	AController::releaseRight()
{
  std::cout << "ReleaseRight speed : " << 100 << std::endl;
}

void	AController::releaseUp()
{
  std::cout << "ReleaseUp speed : " << 100 << std::endl;
}

void	AController::releaseDown()
{
  std::cout << "ReleaseDown speed : " << 100 << std::endl;
}
