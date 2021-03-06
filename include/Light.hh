#ifndef _LIGHT_HH_
#define _LIGHT_HH_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Light
{
public:
  Light(sf::Vector2f pos, float rat) :
    position(pos),
    color(sf::Color::White),
    ratio(rat),
    _nextRatio(rat),
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
    if (_frame >= 8 && ratio > _nextRatio)
      {
	ratio -= (_tex.getSize().x * (ratio) / _tex.getSize().y * (ratio)) * 0.05;
	_frame = 0;
      }
    else if (_frame >= 8 && ratio < _nextRatio)
      {
	ratio += (_tex.getSize().x * (ratio) / _tex.getSize().y * (ratio)) * 0.05;
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
