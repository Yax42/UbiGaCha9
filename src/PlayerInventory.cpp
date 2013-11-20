#include "PlayerInventory.hh"
#include "Hero.hh"
#include "UbiException.hh"

PlayerInventory::PlayerInventory(): _inventoryCursor(0)
{
  if (!(_inventoryTex.loadFromFile("ressource/textures/inventaire.png")))
    throw UbiException("Error load inventaire");
}

void	PlayerInventory::handleEvent(sf::Event & event)
{
  if (event.type == sf::Event::JoystickMoved && event.joystickMove.axis == 6)
    {
      if (event.joystickMove.position == 100)
	{
	  if (_inventoryCursor >= Hero::_listWeapons.size() - 1)
	    _inventoryCursor = 0;
	  else
	    _inventoryCursor += 1;
	}
      else if (event.joystickMove.position == -100)
	{
	  if (_inventoryCursor <= 0)
	    _inventoryCursor = Hero::_listWeapons.size() - 1;
	  else
	    _inventoryCursor -= 1;
	}
    }
  else if (event.type == sf::Event::JoystickButtonPressed)
    {
      if (event.joystickButton.button == 4)
	Hero::_listEquip[0] = _inventoryCursor;// select first weapon
      if (event.joystickButton.button == 5)
	Hero::_listEquip[1] = _inventoryCursor;// select second weapon
    }
  else if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Numpad6)
	{
	  if (_inventoryCursor >= Hero::_listWeapons.size() - 1)
	    _inventoryCursor = 0;
	  else
	    _inventoryCursor += 1;
	}
      else if (event.key.code == sf::Keyboard::Numpad4)
	{
	  if (_inventoryCursor <= 0)
	    _inventoryCursor = Hero::_listWeapons.size() - 1;
	  else
	    _inventoryCursor -= 1;
	}
      else if (event.key.code == sf::Keyboard::Numpad7)
	Hero::_listEquip[0] = _inventoryCursor;// select first weapon
      else if (event.key.code == sf::Keyboard::Numpad9)
	Hero::_listEquip[1] = _inventoryCursor;// select second weapon
    }
}

void	PlayerInventory::draw(sf::RenderTexture & sceneTexture)
{
  int	all = 0;

  sf::Vector2u	sizeTex = _inventoryTex.getSize();
  sf::Vector2f	mult(sizeTex.x / 4, sizeTex.y / 8);
  sf::Sprite tmp(_inventoryTex);

  for (std::vector<bool>::iterator it = Hero::_listWeapons.begin();
       it != Hero::_listWeapons.end(); ++it)
    {
      if ((*it) == true)
	{
	  tmp.setTextureRect(sf::IntRect(all * mult.x, mult.y, mult.x, mult.y));
	  tmp.setPosition(all * mult.x, 0);
	  sceneTexture.draw(tmp);
	}
      else
	{
	  tmp.setTextureRect(sf::IntRect(all * mult.x, 0, mult.x, mult.y));
	  tmp.setPosition(all * mult.x, 0);
	  sceneTexture.draw(tmp);
	}
      all += 1;
    }

  tmp.setTextureRect(sf::IntRect(0, 3 * mult.x, mult.x, mult.y));
  tmp.setPosition(Hero::_listEquip[0] * mult.x, 0);
  sceneTexture.draw(tmp);

  tmp.setTextureRect(sf::IntRect(0, 4 * mult.x, mult.x, mult.y));
  tmp.setPosition(Hero::_listEquip[1] * mult.x, 0);
  sceneTexture.draw(tmp);

  tmp.setTextureRect(sf::IntRect(0, 7 * mult.x, mult.x, mult.y));
  tmp.setPosition(_inventoryCursor * mult.x, 0);
  sceneTexture.draw(tmp);
}
