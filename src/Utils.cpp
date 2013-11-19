#include "Utils.hh"

void	centerOrigin(sf::Sprite & sprite)
{
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
