#include "Mob0.hh"

AssetDescriptor Mob0::s_assetDesc("ressource/textures/mob0.png");

void		Mob0::initAsset()
{
	//DIE
	s_assetDesc.addLine(32, 32, 8);

	//STAND WEAPON 0
	s_assetDesc.addLine(32, 8, 4);
	s_assetDesc.addLine(32, 8, 4);
	s_assetDesc.addLine(32, 8, 4);
	s_assetDesc.addLine(32, 8, 4);
	//WALK WEAPON 0
	s_assetDesc.addLine(32, 8, 3);
	s_assetDesc.addLine(32, 8, 3);
	s_assetDesc.addLine(32, 8, 3);
	s_assetDesc.addLine(32, 8, 3);
}

Mob0::Mob0(const sf::Vector2f &pos)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(32, 32))
{
	_type = 2;
	_mobType = 0;
}

void			Mob0::updateSprite()
{
  int		xSign =  (_direction.x > 0) ? 1 : -1;
  int		ySign =  (_direction.y > 0) ? 1 : -1;

  int		xAbs = xSign * _direction.x;
  int		yAbs = ySign * _direction.y;
  if (xAbs + yAbs > 0)
	  {
		  if (xAbs > yAbs)
			  _orientation = xSign > 0 ? RIGHT : LEFT;
		  else
			  _orientation = ySign > 0 ? DOWN : UP;
		  _state = WALK;
	  }
	  if (_order > -1)
	  {
		_state = _order;
		_order = -1;
	  }
  if (_state == DIE)
	_asset.setCurrentLine(DIE);
  else
	_asset.setCurrentLine(_orientation + 4 * (_state - 1) + 1);
  _asset.update();
}
