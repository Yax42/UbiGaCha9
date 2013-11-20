#ifndef	_PLAYERINVENTORY_HH_
#define	_PLAYERINVENTORY_HH_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class	PlayerInventory
{
public:
  PlayerInventory();
  ~PlayerInventory() {}
  void	handleEvent(sf::Event &);
  void	draw(sf::RenderTexture &);
private:
  int			_inventoryCursor;
  sf::Texture		_inventoryTex;
  sf::Texture		_inventoryCursorTex;
};

#endif	// _PLAYERINVENTORY_HH_
