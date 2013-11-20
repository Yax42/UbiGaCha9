#include "Arrow.hh"

AssetDescriptor Arrow::s_assetDesc("ressource/textures/arrow.png");

void		Arrow::initAsset()
{
	s_assetDesc.addLine(18, 3, 2);
	s_assetDesc.addLine(18, 3, 2);
	s_assetDesc.addLine(3, 18, 2);
	s_assetDesc.addLine(3, 18, 2);
}

Arrow::Arrow(const sf::Vector2f &pos, float orientation)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(2, 2), 130)
{
	_asset.setCurrentLine(orientation);
    _asset.update();
	_alive = true;
	_type = 4;
	_direction = sf::Vector2f(orientation == RIGHT ? 1 : orientation == LEFT ? -1 : 0,  orientation == DOWN ? 1 : orientation == UP ? -1 : 0);
}

void	Arrow::toBackPosition()
{
	_alive = false;
}

bool	Arrow::isDead()
{
	return (!_alive);
}