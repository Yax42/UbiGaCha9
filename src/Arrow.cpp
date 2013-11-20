#include "Arrow.hh"

AssetDescriptor Arrow::s_assetDesc("ressource/textures/arrow.png");

void		Arrow::initAsset()
{
	s_assetDesc.addLine(18, 3, 2);
	s_assetDesc.addLine(18, 3, 2);
	s_assetDesc.addLine(3, 18, 2);
	s_assetDesc.addLine(3, 18, 2);
}

Arrow::Arrow(const sf::Vector2f &pos, const sf::Vector2f &dir)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(2, 2), 130)
{
	_alive = true;
	_type = 3;
	_direction = dir;
}

void	Arrow::toBackPosition()
{
	_alive = false;
}

bool	Arrow::isDead()
{
	return (!_alive);
}