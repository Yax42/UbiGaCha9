#include "Inventory.hh"

Inventory::Inventory()
{
	sf::Sprite stickSprite;
	if (!stickSprite.load)
	_WeaponUsed.insert(std::pair < std::pair<WeaponID, sf::Sprite>, bool> ((STICK, stickSprite), true);
}

Inventory::~Inventory(){}

void Inventory::addItem(WeaponID id)
{
	_WeaponUsed[id]
}