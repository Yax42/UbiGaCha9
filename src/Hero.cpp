#include <iostream>
#include "Arrow.hh"
#include "Kamea.hh"
#include "Hero.hh"

AssetDescriptor Hero::s_assetDesc("ressource/textures/monk.png");

void		Hero::initAsset()
{
	//DIE
	s_assetDesc.addLine(32, 16, 6);

	//STAND WEAPON 0
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	//WALK WEAPON 0
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	//ATTACK WEAPON 0
	s_assetDesc.addLine(32, 24, 4);
	s_assetDesc.addLine(32, 24, 4);
	s_assetDesc.addLine(32, 32, 4);
	s_assetDesc.addLine(32, 32, 4);

	//STAND WEAPON 1
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	//WALK WEAPON 1
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	//ATTACK WEAPON 1
	s_assetDesc.addLine(32, 24, 4);
	s_assetDesc.addLine(32, 24, 4);
	s_assetDesc.addLine(32, 32, 4);
	s_assetDesc.addLine(32, 32, 4);
}

Hero::Hero(const sf::Vector2f &pos)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(16, 32), 75)
{
	_attackBoxState = NO_ATTACK;
	_type = 1;
}

int				Hero::calculateCurLine()
{
  if (_state == DIE)
	  return (DIE);
  else
    return (_orientation + 4 * (_state - 1) + _weapon * 12 + 1);
}

void			Hero::updateSprite()
{
  int		xSign =  (_direction.x > 0) ? 1 : -1;
  int		ySign =  (_direction.y > 0) ? 1 : -1;

  float		xAbs = xSign * _direction.x;
  float		yAbs = ySign * _direction.y;

  if (_stateCount == 0)
  {
	  if (_order > -1)
	  {
		_oldOrient = _orientation;
		_state = _order;
		_stateCount = _asset.getCount(calculateCurLine());
	  }
	  else if (xAbs + yAbs > 0)
	  {

		  if (xAbs > yAbs)
			  _orientation = xSign > 0 ? RIGHT : LEFT;
		  else
			  _orientation = ySign > 0 ? DOWN : UP;
		  _state = WALK;
	  }
	  else
		  _state = STAND;
  }
  if (_stateCount != 0)
  {
	_order = -1;
	_stateCount--;
  }
  _asset.setCurrentLine(calculateCurLine());
  _asset.update();
}

void	Hero::update(float ft, size_t frameCount)
{
  if (_state == ATTACK)
  {
	int signX = (_orientation == LEFT) ? -1 :
			  (_orientation == RIGHT) ? 1 : 0;
	int signY = (_orientation == UP) ? -1 :
			  (_orientation == DOWN) ? 1 : 0;

	  if (_weapon == 0)
	  {
		  _attackBoxState = ATTACK0;
		  _attackBox = sf::FloatRect(0, 0, 64, 64);
		  if ((frameCount % 4) == 0)
			updateSprite();
	  }
	  else if (_weapon == 1)
	  {
		  if (_stateCount == 3)
		  {
			  _attackBoxState = NO_ATTACK;
			  _direction.x = 0;
			  _direction.y = 0;
			if ((frameCount % 4) == 0)
					updateSprite();
		  }
		  else if (_stateCount == 2)
		  {
			  _attackBoxState = NO_ATTACK;
			  _direction.x = -0.4 * signX;
			  _direction.y = -0.4 * signY;
			if ((frameCount % 4) == 0)
					updateSprite();

		  }
		  else if (_stateCount == 1)
		  {
			  _attackBoxState = ATTACK1;
			  _attackBox = sf::FloatRect(signX * 32, signY * 32, 32, 32);
			  _direction.x = 0.4 * signX;
			  _direction.y = 0.4 * signY;
			if ((frameCount % 8) == 0)
					updateSprite();
		  }
		  else
		  {
			  _attackBoxState = ATTACK1;
			  _direction.x = 2 * signX;
			  _direction.y = 2 * signY;
			if ((frameCount % 8) == 0)
			  {
					updateSprite();
					_attackBoxState = NO_ATTACK;
				  _direction.x = 0;
				  _direction.y = 0;
			  }
		  }

	  }
	if (_weapon == 2)
	{
		  _attackBoxState = NO_ATTACK;
		  if ((frameCount % 8) == 0)
		  {
			  if (_stateCount == 0)
			  {
				  new Arrow(getPos(), _direction);
			  }
			updateSprite();
		  }
	  }
  }
  else if ((frameCount % 8) == 0)
    updateSprite();
  _backPos = sf::Vector2f(_box.left, _box.top);
  _box.left += _direction.x * ft * _maxSpeed;
  _box.top += _direction.y * ft * _maxSpeed;
}
