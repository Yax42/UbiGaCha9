#ifndef _LIGHT_HH_
#define _LIGHT_HH_

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

class Light
{
public:
  Light(sf::Vector2f pos, float ratio) :
    position(pos),
    ratio(ratio),
    color(sf::Color(255,255,255)),
    _nextRation(ratio),
    _frame(0)
  {
  }

  void	setTexture(sf::Texture & tex)
  {
    _tex = tex;
  }

  void	setRatio(int nextRatio)
  {
    _nextRatio = nextRatio;
  }

  float	getNextRatio() const {return (_nextRatio);}

  void	update()
  {
    _frame += 1;
    if (_frame >= 4 && ratio > _nextRatio)
      {
	ratio -= (_tex.getSize().x * (ratio) / _tHalo.getSize().y * (ratio)) * 0.01;
	_frame = 0;
      }
    else if (_frame >= 4 && ratio < _nextRatio)
      {
	ratio += (_tex.getSize().x * (ratio) / _tex.getSize().y * (ratio)) * 0.01;
	_frame = 0;
      }
  }

  sf::Vector2f  position;
  sf::Color     color;
  float         ratio;
private:
  float		_nextRatio;
  int		_frame;
  sf::Texture	_tex;
};

#endif // _LIGHT_HH_
