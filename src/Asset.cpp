#include <iostring>
#include "Asset.h"

Asset::Asset(const &sf::string name) : _curLine(0), _curFrame(0)
{
	if (_textures.loadFromFile(name) == false)
	{
		std::cerr << "Error cannot load " << name << std::endl;
	}
}

void	Asset::setLine(Line &line)
{
	if (lines.size() > 1)
		lines.totalHeight = lines.end().totalHeight + lines.end().height;
	_lines.push_back(line);
}

void	Asset::setCurrentLine(int cur)
{
	_curLine = _lines.size() % cur;
	_curFrame = -1;
	resetSprite();
}

void	Asset::resetSprite()
{
	if (_curFrame < 0)
		_curFrame = 0;
	_sprite.setTextureRect(sf::IntRect(
		_lines[_curLine].width * _curFrame,
		_lines[_curLine].totalHeight,
		_lines[_curLine].width,
		_lines[_curLine].height));
	sprite.setOrigin(_lines[_curLine].width, _lines[_curLine].height);
}

void	Asset::update()
{
	_curFrame++;
	_curFrame %= _lines[_curLine].count;
	resetSprite();
}

void	Asset::draw(const sf::Vector2f &_pos, float _angle)
{
	sprite.setRotation(angle);
	sprite.setPosition(_pos);
}