#ifndef	_MAINMENULAYER_HH_
#define	_MAINMENULAYER_HH_

#include "ILayer.hh"
#include <SFML/Graphics.hpp>

class	MainMenuLayer : public ILayer
{
public:
  MainMenuLayer(sf::RenderWindow &);
  virtual ~MainMenuLayer() {}
  virtual bool update(sf::Event &);
  virtual void draw();
  virtual void run();
private:
  sf::RenderWindow 	&_window;
  std::vector<std::pair<sf::Texture, sf::Texture> > _textures; 
  std::vector<std::pair<size_t, size_t> > _posText;
  std::vector<std::pair<double,double> >_scaleText;
  sf::Sprite	_sprite;
  sf::Texture	_select;
  sf::Texture	_noSelect;
  sf::Font		_font;
  size_t	_whatButton;
  State _state;
  bool	_pressedDown;
  bool _pressedUp;
};

#endif	// _MAINMENULAYER_HH_
