#include <iostream>
#include "World.hh"
#include "Arrow.hh"
#include "Kamea.hh"
#include "Hero.hh"
#include "SoundManager.hh"

AssetDescriptor Hero::s_assetDesc("ressource/textures/monk.png");
std::vector<bool> Hero::_listWeapons;
std::vector<int> Hero::_listEquip;

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

	//FILL LISTWEAPON ALL FALSE IN BEGIN TEST WITH TRUE
	_listWeapons.push_back(true);
	_listWeapons.push_back(true);
	_listWeapons.push_back(true);
	_listWeapons.push_back(true);

	_listEquip.push_back(0);
	_listEquip.push_back(0);
}

Hero::Hero(const sf::Vector2f &pos)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(5, 5), 75), _sound(false)
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
	  if (!_sound)
	    {
	      _sound = true;
	      SoundManager::getInstance().getSound("ressource/sounds/staff_vent.wav").play();
	    }
	  _attackBoxState = ATTACK0;
	  _attackBox = sf::FloatRect(_box.left - 15, _box.top - 15, _box.width + 30, _box.height + 30);
	  if ((frameCount % 4) == 0)
	    updateSprite();
	}
      else if (_weapon == 1)
	{
	  if (!_sound)
	    {
	      _sound = true;
	      SoundManager::getInstance().getSound("ressource/sounds/epee_vent.wav").play();
	    }
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
	      _attackBox = sf::FloatRect(_box.left + 30 * signX, _box.top + 30 * signY, 30, 30);
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
      else if (_weapon == 2)
	{
	  if (!_sound)
	    {
	      _sound = true;
	      SoundManager::getInstance().getSound("ressource/sounds/bowGluant1.wav").play();
	    }
	  _attackBoxState = NO_ATTACK;
	  if ((frameCount % 8) == 0)
	    {
	      if (_stateCount == 0)
		{
		  World::gameObjects->push_back(new Arrow(getPos(), _direction));
		}
	      updateSprite();
	    }
	}
    }
  else if ((frameCount % 8) == 0)
    updateSprite();
  else
    _sound = false;
  _backPos = sf::Vector2f(_box.left, _box.top);
  _box.left += _direction.x * ft * _maxSpeed;
  _box.top += _direction.y * ft * _maxSpeed;
}

bool Hero::collides(GameObject &obj)
{
  if (_collide == false || obj._collide == false || obj._type == 4 || obj._type == 5)
    return (false);
  if (obj._type == 2 && _attackBox.intersects(obj._box))
    obj.giveOrder(DIE);
  return (_box.intersects(obj._box));
}
