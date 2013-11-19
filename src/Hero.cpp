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
	s_assetDesc.addLine(32, 32, 4);
	s_assetDesc.addLine(32, 32, 4);
	s_assetDesc.addLine(32, 24, 4);
	s_assetDesc.addLine(32, 24, 4);

	//STAND WEAPON 1
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	s_assetDesc.addLine(32, 16, 2);
	//WALK WEAPON 1
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	s_assetDesc.addLine(32, 16, 4);
	//ATTACK WEAPON 1
	s_assetDesc.addLine(32, 32, 4);
	s_assetDesc.addLine(32, 32, 4);
	s_assetDesc.addLine(32, 24, 4);
	s_assetDesc.addLine(32, 24, 4);
}

Hero::Hero(const sf::Vector2f &pos)
  : GameObject(Asset(s_assetDesc), pos, sf::Vector2f(32, 32))
{
}
