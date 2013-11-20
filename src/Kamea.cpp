#include "Kamea.hh"

AssetDescriptor Kamea::s_assetDesc("ressource/textures/arrow.png");

void		Kamea::initAsset()
{
	s_assetDesc.addLine(32, 16, 1);
	s_assetDesc.addLine(32, 16, 1);
	s_assetDesc.addLine(32, 16, 1);
	s_assetDesc.addLine(32, 16, 1);
}

Kamea::Kamea(const sf::Vector2f &pos)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(50, 50), 0)
{
	_lifeTime = 20;
	_type = 4;
}

void	Kamea::toBackPosition()
{
}

bool	Kamea::isDead()
{
	return (_lifeTime == 0);
}

void	Kamea::update(float ft, size_t frameCount)
{
	if ((frameCount % 8) == 0)
	{
		updateSprite();
		_lifeTime--;
	}
}