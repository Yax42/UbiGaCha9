#include "Kamea.hh"

AssetDescriptor Kamea::s_assetDesc("ressource/textures/kamea.png");

void		Kamea::initAsset()
{
	s_assetDesc.addLine(64, 48, 5);
	s_assetDesc.addLine(64, 48, 5);
	s_assetDesc.addLine(48, 64, 6);
	s_assetDesc.addLine(48, 64, 6);
}

Kamea::Kamea(const sf::Vector2f &pos, float orientation)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(2, 2), 130)
{
	_asset.setCurrentLine(orientation);
    _asset.update();
	_lifeTime = 6;
	_type = 5;
	_direction = sf::Vector2f(0, 0);
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