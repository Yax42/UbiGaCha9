#ifndef _LIGHT_HH_
#define _LIGHT_HH_

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

struct Light
{
  Light(sf::Vector2f pos, float ratio) :
    position(pos),
    ratio(ratio)
  {

  }

  sf::Vector2f    position;
  sf::Color       color = sf::Color(255,255,255);
  float           ratio;
};

#endif // _LIGHT_HH_
