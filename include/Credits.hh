#ifndef	_CREDITS_HH_
#define	_CREDITS_HH_

#include "ILayer.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class	Credits : public ILayer
{
public:
	Credits(sf::RenderWindow &);
	virtual ~Credits() {}
	virtual bool update(sf::Event &);
	virtual void draw();
	virtual void run();
private:
	sf::RenderWindow 	&_window;
	sf::Sprite	_sprite;
	sf::Texture	_select;
	sf::Texture _fontText;
	sf::Font		_font;
	sf::Text	_text;
	sf::Music	_music;

	State _state;
};

#endif	// _CREDITS_HH_
