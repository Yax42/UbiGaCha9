#ifndef	_MAINMENULAYER_HH_
#define	_MAINMENULAYER_HH_

#include "ILayer.hh"
#include <SFML/Graphics.hpp>

class	MainMenuLayer : public ILayer
{
public:
  MainMenuLayer(sf::RenderWindow *);
  virtual ~MainMenuLayer() {}
  virtual bool update(sf::Event &);
  virtual void draw();
private:
  sf::RenderWindow *	_window;
  //sf::Sprite		_sprite;
  //static sf::Texture	_texture;
  sf::Font		_font;
};

#endif	// _MAINMENULAYER_HH_
