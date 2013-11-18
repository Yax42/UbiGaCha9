#include <iostream>
#include "Asset.hh"

Asset::Asset(const std::string &name) : _curLine(0), _curFrame(0)
{
	if (_texture.loadFromFile(name) == false)
	{
		std::cerr << "Error cannot load " << name << std::endl;
	}
}

void	Asset::setLine(Line &line)
{
	if (_lines.size() > 1)
		line.totalHeight = _lines[_lines.size() - 1].totalHeight + _lines[_lines.size() - 1].height;
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
	sprite.setRotation(_angle);
	sprite.setPosition(_pos);
}